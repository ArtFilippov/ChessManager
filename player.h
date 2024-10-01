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
    typedef std::weak_ptr<Player> wptr;
    enum {BLACK, WHITE, UNKNOWN};

    Player(std::string name, int elo = 1000);

    void add_game_result(ptr opponent, float result, int color);
    void remove_game_result(ptr opponent);
    float result_of_game_with(ptr opponent);
    bool is_played_with(ptr opponent);
    float buchholz(int truncation);
    float berger();

    std::string get_name();
    float get_points();
    int get_elo();
private:
    int calculate_new_elo(ptr opponent, float result);
private:
    std::string name_;
    int elo_;
    float points{};
    float last_result{};
    int last_color{UNKNOWN};

    std::vector<wptr> players;
    std::map<std::string, std::tuple<wptr, float, int>> games; // <name, <Player, result, color>>
};

#endif // PLAYER_H
