#ifndef CHESSTOURNAMENT_H
#define CHESSTOURNAMENT_H

#include "player.h"
#include "view.h"

#include <vector>

class ChessTournament
{
protected:
    IView::ptr view_;
    std::vector<Player::ptr> players_;
    int total_rounds_;
    int round{};
public:
    ChessTournament(IView::ptr view, std::vector<Player::ptr> players, int total_rounds);
    virtual ~ChessTournament() = default;

    virtual void add_player(Player::ptr player);
    virtual void remove_player(Player::ptr player);

    virtual void make_pairs() = 0;
    virtual void standings() = 0;
};

class SwissTournament : public ChessTournament
{
public:
    SwissTournament(IView::ptr view, std::vector<Player::ptr> players, int total_rounds);
    SwissTournament(IView::ptr view, std::vector<Player::ptr> players);

    void make_pairs() override;
    void standings() override;
};

class RoundTournament : public ChessTournament
{
public:
    RoundTournament(IView::ptr view, std::vector<Player::ptr> players);

    void add_player(Player::ptr player) override;
    void remove_player(Player::ptr player) override;
    void make_pairs() override;
    void standings() override;
};

#endif // CHESSTOURNAMENT_H
