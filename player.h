#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <tuple>

class Player
{   
public:
    typedef std::shared_ptr<Player> ptr;
    enum {BLACK, WHITE};

    Player(std::string name, int elo = 1000);

    void add_game_result(ptr opponent, float result, int color);
    float result_of_game_with(ptr opponent);
    float buchholz(int truncation);
    float berger();

    std::string get_name();
    float get_points();
    int get_elo();
private:
    int calculate_new_elo(ptr opponent);
private:
    std::string name_;
    int elo_;
    float points{};
    float last_result;
    int last_color;

    std::vector<ptr> players;
    std::map<std::string, std::tuple<ptr, float, int>> games; // <name, <Player, result, color>>
};

#endif // PLAYER_H
