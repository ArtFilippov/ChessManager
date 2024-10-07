#include "serverview.h"

#include <format>
#include <iostream>

#include <QNetworkInterface>

IServerView::IServerView()
{
    QList<QHostAddress> adresses = QNetworkInterface::allAddresses();
    for (int i = 0; i < adresses.count(); ++i) {
        if (!adresses[i].isLoopback() && adresses[i].protocol() == QAbstractSocket::IPv4Protocol) {
            ip = adresses[i].toString().toStdString();
            break;
        }
    }
    port = 3456;
    server = Server::create(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port));

    view = new QLabel(QString::fromStdString(std::format("http://{}:{}", ip, port)));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    this->setLayout(layout);
}

QWidget* IServerView::widget()
{
    return dynamic_cast<QWidget*>(this);
}

// ServerView
ServerView::ServerView() : IServerView() {}

void ServerView::show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>> &pairs)
{
    std::string page = "";
    for (size_t i = 0; i < pairs.size(); ++i) {
        page += std::format("{:3} {:50} {:50}\n", i + 1, pairs[i].first->get_name(), pairs[i].second->get_name());
    }

    if (!server->new_page(page)) {
        std::cerr << "page is not updated" << std::endl;
    }
}

void ServerView::show_standings(std::vector<std::pair<Player::ptr, float>> &player_and_coeff, int round, int total_rounds)
{
    std::string page = std::format("Standings {}/{}\n", round, total_rounds);
    for (size_t i = 0; i < player_and_coeff.size(); ++i) {
        page += std::format("{:3} {:50} {:50}\n", i + 1, player_and_coeff[i].first->get_name(), player_and_coeff[i].second);
    }

    if (!server->new_page(page)) {
        std::cerr << "page is not updated" << std::endl;
    }
}
