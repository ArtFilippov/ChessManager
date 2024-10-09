#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include "server.h"
#include "player.h"

#include <QtWidgets>

class IServerView : public QWidget
{
protected:
    std::string ip{};
    int port{};
    Server::ptr server{};

    QWidget *view;
public:
    IServerView(QWidget *parent);
    virtual ~IServerView() = default;

    QWidget* widget();

    virtual void show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>> &pairs, int round, int total_rounds) = 0;
    virtual void show_standings(std::vector<std::pair<Player::ptr, float>> &player_and_coeff, int round, int total_rounds) = 0;
};

class ServerView : public IServerView
{
public:
    ServerView(QWidget *parent);
    virtual ~ServerView() = default;

    void show_pairs(std::vector<std::pair<Player::ptr, Player::ptr>> &pairs, int round, int total_rounds) override;
    void show_standings(std::vector<std::pair<Player::ptr, float>> &player_and_coeff, int round, int total_rounds) override;
};

#endif // SERVERVIEW_H
