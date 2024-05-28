#include <string>
#include <random>
using namespace std;


#ifndef _CODE_Map_
#define _CODE_Map_
class Snake;

struct Position{
    int x, y;
};

struct Gate_Position:Position{
    bool u{false}, d{false}, r{false}, l{false};
    bool gate_d[4]={0,};
    int count=0;
};

class Map
{
private:
    random_device rd;
    /* data */
public:
    int** map;
    int map_size{};

    Map(int map_size=21);
    ~Map();
    void reset_map(int stage=0);
    
    void snake_to_map(Snake &snake);
    void grow_item_to_map(Position grow);
    void poison_item_to_map(Position poison);
    void gate_to_map(Gate_Position gate);

    Position create_grow_item();
    Position create_poison_item();
    Gate_Position create_gate();
    bool check_map_Pos(int x, int y);
    Gate_Position reset_gate_direction(Gate_Position gate);
    Gate_Position find_gate_direction(Gate_Position gate);
};
#endif