#include "player.h"

#include "database.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Player::Player(std::string name, int elo) : name_(name), elo_(elo)
{
    try {
        auto data = Database::connect()->find_person(name);

        if (data.has_value()) {
            auto [id, name, elo] = data.value();
            name_ = name;
            elo_ = elo;
        } else {
            Database::connect()->add_preson(name, elo);
        }
    } catch (std::string e) {
        std::cerr << e << std::endl;
    }

}

Player::~Player()
{
    try {
        Database::connect()->update_person(name_, elo_);
    } catch (std::string e) {
        std::cerr << e << std::endl;
    }
}

void Player::add_game_result(ptr opponent, float result, int color)
{
    last_last_color = last_color;
    last_color = color;
    last_result = result;

    points += result;
    players.push_back(wptr(opponent));
    games.insert({opponent->get_name(), std::tuple{wptr(opponent), result, color, elo_, opponent->get_elo()}});
}

void Player::remove_game_result(ptr opponent)
{
    if (!is_played_with(opponent->get_name())) {
        return;
    }

    auto [_, result, color, old_elo, opponent_elo] = games[opponent->get_name()];

    elo_ -= elo_diff(old_elo, opponent_elo, result);

    points -= result;
    last_color = UNKNOWN;
    games.erase(opponent->get_name());
}

float Player::get_points()
{
    return points;
}

float Player::buchholz(int truncation)
{
    std::sort(players.begin(), players.end(), [](wptr p1, wptr p2){return p1.lock()->get_points() < p1.lock()->get_points() - p1.lock()->get_points() > p1.lock()->get_points();});


    float b = 0;
    for (std::size_t i = truncation; i < players.size(); ++i) {
        b += players[i].lock()->get_points();
    }

    return b;
}

float Player::berger()
{
    float b = 0;
    for (auto x : players) {
        b += x.lock()->get_points() * result_of_game_with(x.lock()->get_name());
    }

    return b;
}

bool Player::is_played_with(std::string opponent_name)
{
    return games.contains(opponent_name);
}

float Player::result_of_game_with(std::string opponent_name)
{
    if (!is_played_with(opponent_name)) {
        return 0;
    }

    return std::get<1>(games[opponent_name]);
}

std::string Player::get_name()
{
    return name_;
}

int Player::get_elo()
{
    return elo_;
}

void Player::update_elo(int opponent_elo, float result)
{
    elo_ += elo_diff(elo_, opponent_elo, result);
}

int Player::elo_diff(int my_elo, int opponent_elo, float result)
{
    enum
    {
        MIN_SENIOR = 2400,
        MIN_MIDDLE = 1800,
        CORRECTION_FACTOR = 400,
        K_FOR_SENIOR = 10,
        K_FOR_MIDDLE = 20,
        K_FOR_JUNIOR = 40
    };


    float expected = 1 / (1 + std::pow(10, (opponent_elo - elo_) / CORRECTION_FACTOR));

    int k;
    if (elo_ >= MIN_SENIOR) {
        k = K_FOR_SENIOR;
    } else if (elo_ >= MIN_MIDDLE) {
        k = K_FOR_MIDDLE;
    } else {
        k = K_FOR_JUNIOR;
    }

    float diff = k * (result - expected);

    return int(diff);
}

int Player::get_last_color()
{
    return last_color;
}

bool Player::can_play(int color, int flags)
{
    if (flags & conditions::NO_TWO_COLORS) {
        return last_color != color;
    }

    if (flags & conditions::NO_THREE_COLORS) {
        return !(last_color == color && last_last_color == color);
    }

    return true;
}

