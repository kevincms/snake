#include <string>
#include <random>
using namespace std;

struct Position{
    int x, y;
};

struct Gate_Position:Position{
    bool u{false}, d{false}, r{false}, l{false};
    bool gate_d[4]={0,};
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
    void map_to_string(string &map_string);
    void debug_print(string &debug_str);

    Position create_grow_item();
    // Position create_poison_item();
    // Position create_gate();
};
