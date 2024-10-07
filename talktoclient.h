#ifndef TALKTOCLIENT_H
#define TALKTOCLIENT_H

#include <boost/noncopyable.hpp>

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <memory>

class TalkToClient : public std::enable_shared_from_this<TalkToClient>, boost::noncopyable
{
    boost::asio::ip::tcp::socket sock_;
    const std::string write_buffer;
    bool started{0};

    TalkToClient(boost::asio::io_service &service, const std::string page);

public:
    typedef std::shared_ptr<TalkToClient> ptr;
    static ptr create(boost::asio::io_service &service, const std::string page);

    void start();
    void stop();
    boost::asio::ip::tcp::socket &sock();

    void do_write();
    void on_write(const boost::system::error_code &err, size_t bytes);
};

#endif // TALKTOCLIENT_H
