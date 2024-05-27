#include <string>
#include "Map.h"

using namespace std;

#ifndef _CODE_Gamemanger_
#define _CODE_Gamemanger_
struct Score_Board{
    int Current_len, Max_len{0}, plus{0}, minus{0}, gate_count{0};
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
    int stage=0;
public:
    Score_Board score_board;
    Mission_Board mission_board;
    Gamemanger();
    ~Gamemanger();
    void initial_setting();
    bool is_gameover(Map &Map);
    void check_misson();
    void display(Map &Map);

    void display_debug(Map &Map, Snake &snake, bool check=false, string test_string="test");

    void display_map(Map &Map);
    void display_score(Map &Map);
    void display_misssion(Map &Map);
};
#endif