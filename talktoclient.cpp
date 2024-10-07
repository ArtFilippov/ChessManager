#include "talktoclient.h"


TalkToClient::TalkToClient(boost::asio::io_service &service, const std::string page) : sock_(service), write_buffer(page) {}

TalkToClient::ptr TalkToClient::create(boost::asio::io_service &service, const std::string page)
{
    ptr new_(new TalkToClient(service, page));
    return new_;
}

void TalkToClient::start()
{
    started = true;
    do_write();
}

void TalkToClient::stop()
{
    if (!started) {
        return;
    }

    started = false;
    sock_.close();
}

boost::asio::ip::tcp::socket &TalkToClient::sock()
{
    return sock_;
}

void TalkToClient::do_write()
{
    if (!started) {
        return;
    }

    sock_.async_write_some(boost::asio::buffer(write_buffer),
                           boost::bind(&TalkToClient::on_write, shared_from_this(),
                           boost::placeholders::_1, boost::placeholders::_2));
}

void TalkToClient::on_write(const boost::system::error_code &err, size_t bytes)
{
    if (err) {
        std::cerr << "on_write: " << err.message() << std::endl;
    }
}
