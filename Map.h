#include <string>
#include <random>
using namespace std;

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
    void display_map();
    void display_map2();
    void map_to_string(string &map_string);
    void debug_print(string &debug_str);

    Position create_grow_item();
    Position create_poison_item();
    Position create_gate();
    bool check_map_Pos(int x, int y);
    Gate_Position find_gate_direction(Gate_Position gate);
};
