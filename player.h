#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <tuple>
#include <optional>

class Player
{   
public:
    typedef std::shared_ptr<Player> ptr;
    typedef std::weak_ptr<Player> wptr;
    enum {WHITE = 0, BLACK = 1 , UNKNOWN = 2};
    enum conditions {NO_THREE_COLORS = 0b100, NO_TWO_COLORS = 0b10};

    Player(std::string name, int elo = 1000);
    ~Player();

    void add_game_result(ptr opponent, float result, int color);
    void remove_game_result(ptr opponent);
    float result_of_game_with(std::string opponent_name);
    bool is_played_with(std::string opponent_name);
    float buchholz(int truncation);
    float berger();
    bool can_play(int color, int flags);

    std::string get_name();
    float get_points();
    int get_elo();
    int get_last_color();
    void update_elo(int opponent_elo, float result);
private:
    int elo_diff(int my_elo, int opponent_elo, float result);
private:
    std::string name_;
    int elo_;
    float points{};
    float last_result{};
    int last_color{UNKNOWN};
    int last_last_color{UNKNOWN};

    std::vector<wptr> players;
    std::map<std::string, std::tuple<wptr, float, int, int, int>> games; // <name, <Player, result, color, old_elo, opponent_elo>>
};

#endif // PLAYER_H
