#include "chesstournament.h"

#include <algorithm>
#include <exception>

ChessTournament::ChessTournament(IView *view, int total_rounds) : view_(view), total_rounds_(total_rounds) {}

void ChessTournament::add_player(Player::ptr player)
{
    auto p = std::find_if(players_.begin(), players_.end(), [player](Player::ptr a) { return a->get_name() == player->get_name();});
    if (p != players_.end()) {
        throw std::invalid_argument("this player is already exists");
    }
    players_.push_back(player);
}

void ChessTournament::remove_player(Player::ptr player)
{
    players_.erase(std::find(players_.begin(), players_.end(), player));
}

// RoundTournament
RoundTournament::RoundTournament(IView *view) : ChessTournament(view, 0) {}

void RoundTournament::add_player(Player::ptr player)
{
    ChessTournament::add_player(player);
    int num_of_players = players_.size();
    total_rounds_ = num_of_players - 1 + num_of_players % 2;
}

void RoundTournament::remove_player(Player::ptr player)
{
    ChessTournament::remove_player(player);
    int num_of_players = players_.size();
    total_rounds_ = num_of_players - 1 + num_of_players % 2;
}

void RoundTournament::make_pairs()
{
    if (round >= total_rounds_) {
        return;
    }

    if (!players_.size() % 2) {
        players_.push_back(Player::ptr(nullptr));
    }

    int boards = players_.size() / 2;
    if (!boards) {
        throw std::string("too few participants\n");
    }

    int last = boards * 2 - 1;

    std::vector<std::pair<Player::ptr, Player::ptr>> pairs(boards);
    if (round % 2) {
        pairs[0].first = players_[round];
        pairs[0].second = players_[last];
    } else {
        pairs[0].second = players_[round];
        pairs[0].first = players_[last];
    }


    for (int i = 1; i < boards; ++i) {
        int ifirst = (i + round) % last;
        int isecond = (2 * round - ifirst) % last;
        pairs[i].first = players_[ifirst];
        pairs[i].second = players_[isecond];
    }

    view_->show_pairs(pairs);

    if (!players_.back().get()) {
        players_.pop_back();
    }
}

void RoundTournament::standings()
{
    std::sort(players_.begin(), players_.end(), [](Player::ptr a, Player::ptr b){
        if (a->get_points() != b->get_points()) return a->get_points() > b->get_points();
        if (a->is_played_with(b) && a->result_of_game_with(b) != 0.5) return a->result_of_game_with(b) == 1;
        return a->berger() > b->berger();
    });
    std::vector<std::pair<Player::ptr, float>> player_and_coeff(players_.size());
    for (std::size_t i = 0; i < players_.size(); ++i) {
        player_and_coeff.push_back({players_[i], players_[i]->berger()});
    }

    view_->show_standings(player_and_coeff);
}

//SwissTournament
SwissTournament::SwissTournament(IView *view) : ChessTournament(view, 0) {}

SwissTournament::SwissTournament(IView *view, int total_rounds) : ChessTournament(view, total_rounds) {}

void SwissTournament::make_pairs()
{

}

void SwissTournament::standings()
{

}
