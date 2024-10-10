#include "chesstournament.h"

#include <algorithm>
#include <exception>
#include <cmath>
#include <iterator>

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

void ChessTournament::get_players(std::vector<Player::ptr>& players)
{
    players = players_;
}

void ChessTournament::standings()
{
    auto stand(players_);

    std::sort(stand.begin(), stand.end(), [](Player::ptr a, Player::ptr b){
        if (a->get_points() != b->get_points()) return a->get_points() > b->get_points();
        if (a->is_played_with(b->get_name()) && a->result_of_game_with(b->get_name()) != b->result_of_game_with(a->get_name())) return a->result_of_game_with(b->get_name()) > b->result_of_game_with(a->get_name());
        return a->berger() > b->berger();
    });
    std::vector<std::pair<Player::ptr, float>> player_and_coeff;
    for (std::size_t i = 0; i < stand.size(); ++i) {
        player_and_coeff.push_back(std::pair<Player::ptr, float>{stand[i], stand[i]->berger()});
    }

    view_->show_standings(player_and_coeff, round, total_rounds_);
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

bool RoundTournament::make_pairs()
{
    if (round >= total_rounds_) {
        return 1;
    }

    if (players_.size() % 2 != 0) {
        players_.push_back(Player::ptr(new Player("pass", 1000)));
    }

    int boards = players_.size() / 2;
    if (!boards) {
        throw std::string("too few participants\n");
    }

    int last = boards * 2 - 1;

    std::vector<std::pair<Player::ptr, Player::ptr>> pairs(boards);
    if (round % 2 == 0) {
        pairs[0].first = players_[round];
        pairs[0].second = players_[last];
    } else {
        pairs[0].second = players_[round];
        pairs[0].first = players_[last];
    }


    for (int i = 1; i < boards; ++i) {
        int ifirst = (i + round) % last;
        int isecond = (2 * round - ifirst + last) % last;

        if (i % 2 == 0) {
            pairs[i].first = players_[ifirst];
            pairs[i].second = players_[isecond];
        } else {
            pairs[i].second = players_[ifirst];
            pairs[i].first = players_[isecond];
        }
    }

    ++round;

    view_->show_pairs(pairs, round, total_rounds_);

    if (players_.back()->get_name() == "pass") {
        players_.pop_back();
    }

    return 0;
}

//SwissTournament
SwissTournament::SwissTournament(IView *view) : ChessTournament(view, 0), auto_rounds{1} {}

SwissTournament::SwissTournament(IView *view, int total_rounds) : ChessTournament(view, total_rounds), auto_rounds{0} {}

void SwissTournament::add_player(Player::ptr player)
{
    ChessTournament::add_player(player);
    update_rounds();
}

void SwissTournament::remove_player(Player::ptr player)
{
    ChessTournament::remove_player(player);
    update_rounds();
}

bool SwissTournament::make_pairs()
{
    if (round >= total_rounds_) {
        return 1;
    }

    if (players_.size() % 2 != 0) {
        players_.push_back(Player::ptr(new Player("pass", 1000)));
    }

    pairs.clear();

    auto groups = split_into_groups();

    if (groups.empty()) {
        return 1;
    }

    for (int i = 0; i < (int)groups.size() - 1; ++i) {
        split_into_pairs(groups[i], conditions::DID_NOT_PLAY | conditions::NO_TWO_COLORS);
        if (!groups[i].empty()) {
            split_into_pairs(groups[i], conditions::DID_NOT_PLAY | conditions::NO_THREE_COLORS);
        }
        if (!groups[i].empty()) {
            groups[i + 1].splice(groups[i + 1].begin(), groups[i]);
        }
    }



    split_into_pairs(groups.back(), conditions::DID_NOT_PLAY | conditions::NO_THREE_COLORS);
    if (!groups.back().empty()) {
        split_into_pairs(groups.back(), conditions::DID_NOT_PLAY);
        if (!groups.back().empty()) {
            split_into_pairs(groups.back(), 0);
        }
    }

    ++round;
    view_->show_pairs(pairs, round, total_rounds_);

    if (players_.back()->get_name() == "pass") {
        players_.pop_back();
    }

    return 0;
}

std::vector<std::list<Player::ptr>> SwissTournament::split_into_groups()
{
    std::list<Player::ptr> players{};
    for (auto p : players_) {
        players.push_back(p);
    }

    players.sort([](Player::ptr a, Player::ptr b){
        if (a->get_points() != b->get_points()) return a->get_points() > b->get_points();
        if (a->is_played_with(b->get_name()) && a->result_of_game_with(b->get_name()) != b->result_of_game_with(a->get_name())) return a->result_of_game_with(b->get_name()) > b->result_of_game_with(a->get_name());
        return a->berger() > b->berger();
    });

    std::vector<std::list<Player::ptr>> groups{};
    std::list<Player::ptr> fg{};
    fg.splice(fg.begin(), players, players.begin());

    for (auto p = players.front(); !players.empty(); players.pop_front(), p = players.front()) {
        if (fg.back()->get_points() == p->get_points()) {
            fg.push_back(p);
        } else {
            groups.push_back(fg);
            fg.clear();
            fg.push_back(p);
        }
    }

    groups.push_back(fg);

    return groups;
}

void SwissTournament::split_into_pairs(std::list<Player::ptr> &group, int condition_flags)
{
    if (group.size() <= 1) {
        return;
    }

    group.sort([](Player::ptr a, Player::ptr b){
        if (a->get_last_color() != b->get_last_color()) {
            return a->get_last_color() < b->get_last_color();
        }
        if (a->get_points() != b->get_points()) return a->get_points() > b->get_points();
        if (a->is_played_with(b->get_name()) && a->result_of_game_with(b->get_name()) != b->result_of_game_with(a->get_name())) return a->result_of_game_with(b->get_name()) > b->result_of_game_with(a->get_name());
        return a->berger() > b->berger();
    });

    std::list<Player::ptr> white{};

    auto end = group.begin();
    std::advance(end, std::distance(group.begin(), group.end()) / 2);
    white.splice(white.begin(), group, group.begin(),  end);

    auto p1 = white.begin();
    while (p1 != white.end()) {
        bool done = false;
        auto p2 = group.begin();
        while (p2 != group.end()) {
            if (is_match(*p1, *p2, condition_flags)) {
                pairs.push_back({*p1, *p2});
                auto pred1 = p1++;
                auto pred2 = p2++;
                white.erase(pred1);
                group.erase(pred2);
                done = true;
                break;
            } else if (is_match(*p2, *p1, condition_flags)) {
                pairs.push_back({*p2, *p1});
                auto pred1 = p1++;
                auto pred2 = p2++;
                white.erase(pred1);
                group.erase(pred2);
                done = true;
                break;
            }

            ++p2;
        }

        if (!done) {
            ++p1;
        }
    }

    split_into_pairs(white, condition_flags);
    split_into_pairs(group, condition_flags);

    group.splice(group.begin(), white);
}

bool SwissTournament::is_match(Player::ptr white, Player::ptr black, int condition_flags)
{
    bool result = true;
    if (condition_flags & conditions::DID_NOT_PLAY) {
        result = result && !white->is_played_with(black->get_name());
    }

    if (condition_flags & conditions::NO_TWO_COLORS) {
        result = result && white->can_play(Player::WHITE, Player::conditions::NO_TWO_COLORS) && black->can_play(Player::BLACK, Player::conditions::NO_TWO_COLORS);
    }

    if (condition_flags & conditions::NO_THREE_COLORS) {
        result = result && white->can_play(Player::WHITE, Player::conditions::NO_THREE_COLORS) && black->can_play(Player::BLACK, Player::conditions::NO_THREE_COLORS);
    }

    return result;
}

void SwissTournament::update_rounds()
{
    if (auto_rounds) {
        total_rounds_ = std::round(std::log2(players_.size()) + std::round(std::log2(static_cast<double>(NUMBER_OF_FAIR_PLACES))));
    }
}
