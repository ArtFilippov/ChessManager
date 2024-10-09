#ifndef SERVER_H
#define SERVER_H

#include "talktoclient.h"

#include <boost/noncopyable.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <mutex>
#include <thread>

class Server : public std::enable_shared_from_this<Server>, boost::noncopyable
{
    boost::asio::io_service service{};
    boost::asio::ip::tcp::acceptor acc;

    std::string page_{"<html><body><h1>Hello World</h1><p>This is a web server in c++</p></body></html>"};
    std::timed_mutex m{};
    std::thread t;

    Server(boost::asio::ip::tcp::endpoint ep);
public:
    typedef std::shared_ptr<Server> ptr;
    static ptr create(boost::asio::ip::tcp::endpoint ep);
    ~Server();

    bool new_page(std::string page);
    void handle_accept(TalkToClient::ptr client, const boost::system::error_code &err);
    void run();
private:
    void run_thread();
    std::string response();
};

#endif // SERVER_H
