#include <string>
#include "Map.h"
using namespace std;

class Gamemanger
{
private:
    /* data */
public:
    Gamemanger();
    ~Gamemanger();
    void initial_setting();
    bool is_gameover(Map &Map);
    void display();
};
