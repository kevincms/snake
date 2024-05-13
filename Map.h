#include <string>
using namespace std;

class Map
{
private:
    /* data */
public:
    int** map;
    int map_size{};
    Map(int map_size=21);
    ~Map();
    void display_map();
    void map_to_string(string &map_string);
    void debug_print(string &debug_str);
};
