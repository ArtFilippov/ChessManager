#include "serverview.h"

#include <format>
#include <iostream>

#include <QNetworkInterface>

IServerView::IServerView(QWidget *parent) : QWidget(parent)
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
    dynamic_cast<QLabel*>(view)->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    this->setLayout(layout);
}

QWidget* IServerView::widget()
{
    return dynamic_cast<QWidget*>(this);
}

// ServerView
ServerView::ServerView(QWidget *parent) : IServerView(parent) {}

void ServerView::show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>> &pairs)
{
    std::string page = "<html><body>";
    for (size_t i = 0; i < pairs.size(); ++i) {
        page += std::format("<p>{:3} {:50} {:50}</p>", i + 1, pairs[i].first->get_name(), pairs[i].second->get_name());
    }

    page += "</body></html>";

    server->new_page(page);
}

void ServerView::show_standings(std::vector<std::pair<Player::ptr, float>> &player_and_coeff, int round, int total_rounds)
{
    std::string page = std::format("<html><body><h1>Standings {}/{}</h1>", round, total_rounds);
    for (size_t i = 0; i < player_and_coeff.size(); ++i) {
        page += std::format("<p>{:3} {:50} {:50}</p>", i + 1, player_and_coeff[i].first->get_name(), player_and_coeff[i].second);
    }

    page += "</body></html>";

    server->new_page(page);
}
