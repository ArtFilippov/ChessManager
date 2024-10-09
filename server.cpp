#include "server.h"

#include <chrono>

Server::Server(boost::asio::ip::tcp::endpoint ep) : acc(service, ep)
{
    run();
}

Server::~Server()
{
    service.stop();
    t.join();
}

Server::ptr Server::create(boost::asio::ip::tcp::endpoint ep)
{
    Server::ptr new_(new Server(ep));
    return new_;
}

void Server::handle_accept(TalkToClient::ptr client, const boost::system::error_code &err)
{
    if (err) {
        std::cerr << err.message() << std::endl;
        exit(1);
    }

    client->start();
    TalkToClient::ptr new_client;
    {
        std::lock_guard lg(m);
        new_client = TalkToClient::create(service, response());
    }
    acc.async_accept(new_client->sock(), boost::bind(&Server::handle_accept, shared_from_this(),
                                                     new_client, boost::placeholders::_1));
}

bool Server::new_page(std::string page)
{
    using namespace std::chrono;
    if (m.try_lock_for(100ms)) {
        page_ = page;
        return true;
    }
    return false;
}

void Server::run()
{
    t = std::thread(&Server::run_thread, this);
}

void Server::run_thread()
{
    TalkToClient::ptr client;
    {
        std::lock_guard lg(m);
        client = TalkToClient::create(service, response());
    }

    acc.async_accept(client->sock(), boost::bind(&Server::handle_accept, shared_from_this(),
                                                 client, boost::placeholders::_1));
    service.run();
}

std::string Server::response()
{
    std::string response = "HTTP/1.1 200 OK\n"
                           "content-type: text/html\n"
                           "content-length: " + std::to_string(page_.length()) + "\n\n";
    response += page_;

    return response;
}
