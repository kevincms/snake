#include <string>
#include <chrono>
#include "Map.h"

using namespace std;

#ifndef _CODE_Gamemanger_
#define _CODE_Gamemanger_
struct Score_Board{
    int Current_len=3, Max_len{0}, plus{0}, minus{0}, gate_count{0};
};

struct Mission_Board{
    int B, plus, minus, gate_count;
    bool check[4]={0,};
    string check_string[4]={"X","X","X","X"};
};

class Snake;

class Gamemanger
{
private:
    int grow_create_count{-1}, poison_create_count{-1}, special_create_count{-1};
public:
    int stage=0;
    Score_Board score_board;
    Mission_Board mission_board;
    chrono::system_clock::time_point start;
    Gamemanger();
    ~Gamemanger();
    void get_game_start_time();
    double get_game_progress_time();
    void initial_setting();
    void reset_mission_by_stage(bool test=false);
    bool is_stage_clear();
    bool is_gameover(Map &Map, Snake &snake);

    bool can_create_grow_item();
    bool can_create_poison_item();
    bool can_create_special_item();
    bool can_create_gate();

    bool can_delete_item();
    bool can_delete_gate(Snake snake, Gate_Position gate1, Gate_Position gate2);

    bool is_eat_item(Position item, Snake &snake);
    void update_score_board(bool grow=false, bool poison=false, bool gate=false);
    void reset_score_board();

    void check_misson();
    void display(Map &Map);

    void display_debug(Map &Map, Snake &snake, bool check=false, string test_string="test");

    void display_map(Map &Map);
    void display_score(Map &Map);
    void display_misssion(Map &Map);
};
#endif