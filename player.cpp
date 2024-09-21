#include "player.h"

#include <algorithm>
#include <cmath>

Player::Player(std::string name, int elo) : name_(name), elo_(elo) {}

void Player::add_game_result(ptr opponent, float result, int color)
{
    last_color = color;
    last_result = result;
    elo_ = calculate_new_elo(opponent, result);
    points += result;
    players.push_back(opponent);
}

float Player::get_points()
{
    return points;
}

float Player::buchholz(int truncation)
{
    std::sort(players.begin(), players.end(), [](ptr p1, ptr p2){return p1->get_points() < p1->get_points() - p1->get_points() > p1->get_points();});


    float b = 0;
    for (std::size_t i = truncation; i < players.size(); ++i) {
        b += players[i]->get_points();
    }

    return b;
}

float Player::berger()
{
    float b = 0;
    for (auto x : players) {
        b += x->get_points() * result_of_game_with(x);
    }

    return b;
}

float Player::result_of_game_with(ptr opponent)
{
    return std::get<1>(games[opponent->get_name()]);
}

std::string Player::get_name()
{
    return name_;
}

int Player::get_elo()
{
    return elo_;
}

int Player::calculate_new_elo(ptr opponent, float result)
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


    float expected = 1 / (1 + std::pow(10, (opponent->get_elo() - elo_) / CORRECTION_FACTOR));

    int k;
    if (elo_ >= MIN_SENIOR) {
        k = K_FOR_SENIOR;
    } else if (elo_ >= MIN_MIDDLE) {
        k = K_FOR_MIDDLE;
    } else {
        k = K_FOR_JUNIOR;
    }

    float new_elo = elo_ + k * (result - expected);

    return int(new_elo);
}
