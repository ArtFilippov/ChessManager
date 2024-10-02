#ifndef CHESSTOURNAMENT_H
#define CHESSTOURNAMENT_H

#include "player.h"
#include "view.h"

#include <vector>

class ChessTournament
{
protected:
    IView *view_;
    std::vector<Player::ptr> players_{};
    int total_rounds_;
    int round{0};
public:
    typedef std::shared_ptr<ChessTournament> ptr;

    ChessTournament(IView *view, int total_rounds);
    virtual ~ChessTournament() = default;

    virtual void add_player(Player::ptr player);
    virtual void remove_player(Player::ptr player);

    virtual void make_pairs() = 0;
    virtual void standings() = 0;

    virtual void get_players(std::vector<Player::ptr>&);
};

class SwissTournament : public ChessTournament
{
public:
    SwissTournament(IView *view, int total_rounds);
    SwissTournament(IView *view);

    void make_pairs() override;
    void standings() override;
};

class RoundTournament : public ChessTournament
{
public:
    RoundTournament(IView *view);

    void add_player(Player::ptr player) override;
    void remove_player(Player::ptr player) override;
    void make_pairs() override;
    void standings() override;
};

#endif // CHESSTOURNAMENT_H
