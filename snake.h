#include <vector>
#include <curses.h>
#include <Windows.h> // 지연능 위한 헤더파일

using namespace std;

struct Position // 좌표 저장 구조체
{
    int x, y;
};

class Snake {
private:
    Position prev; // 꼬리가 이동전 있었던 좌표
    char direction; // 방향
    int cnt_growth{ 0 }, cnt_poison{ 0 }, cnt_gate{ 0 };
public:
    vector <Position> snake_body;
    Snake();
    void set_direction();
    void move();
    void eat_growth(const int x, const int y);
    void eat_poison(const int x, const int y);
    bool go_gate(const int gate1[], const int gate2[]);
    char get_direction();
    int get_cnt_growth();
    int get_cnt_poison();
    int get_cnt_gate();
    void display();
};