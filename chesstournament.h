#ifndef CHESSTOURNAMENT_H
#define CHESSTOURNAMENT_H

#include "player.h"
#include "view.h"

#include <vector>
#include <list>

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

    virtual bool make_pairs() = 0;
    virtual void standings();

    virtual void get_players(std::vector<Player::ptr>&);
};

class SwissTournament : public ChessTournament
{
    enum {NUMBER_OF_FAIR_PLACES = 3};
    enum conditions {NO_THREE_COLORS = 0b100, NO_TWO_COLORS = 0b10, DID_NOT_PLAY = 0b1};

    bool auto_rounds;
    std::vector<std::pair<Player::ptr, Player::ptr>> pairs{};
public:
    SwissTournament(IView *view, int total_rounds);
    SwissTournament(IView *view);

    void add_player(Player::ptr player) override;
    void remove_player(Player::ptr player) override;
    bool make_pairs() override;
private:
    void update_rounds();
    void split_into_pairs(std::list<Player::ptr> &group, int condition_flags);
    std::vector<std::list<Player::ptr>> split_into_groups();
    bool is_match(Player::ptr white, Player::ptr black, int condition_flags);
};

class RoundTournament : public ChessTournament
{
public:
    RoundTournament(IView *view);

    void add_player(Player::ptr player) override;
    void remove_player(Player::ptr player) override;
    bool make_pairs() override;
};

#endif // CHESSTOURNAMENT_H
