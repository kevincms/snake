#include <vector>
#include <curses.h>
#include <chrono>
#include <thread>
#include "Map.h"
#include "Gamemanger.h"

using namespace std;

class Snake {
private:
    Position prev; // ������ �̵��� �־��� ��ǥ
    char direction; // ����
    int cnt_growth, cnt_poison, cnt_gate;
public:
    bool quit=false;
    vector <Position> snake_body;
    Snake();

    // void set_direction();
    void set_direction(Map &Map, Snake &snake, Gamemanger &GM);

    void move();
    void eat_growth(const Position item);
    void eat_poison(const Position item);
    bool go_gate(const Gate_Position gate1, const Gate_Position gate2);
    char get_direction();
    int get_cnt_growth() const;
    int get_cnt_poison() const;
    int get_cnt_gate() const;
    void display();
};