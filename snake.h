#include <vector>
#include <curses.h>
#include <Windows.h> // ������ ���� �������
#include "map.h"

using namespace std;

class Snake {
private:
    Position prev; // ������ �̵��� �־��� ��ǥ
    char direction; // ����
    int cnt_growth{0}, cnt_poison{0}, cnt_gate{0};
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