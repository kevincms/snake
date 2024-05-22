#include <vector>
#include <curses.h>
#include <iostream>

using namespace std;

struct position {
    int x, y;
};

class Snake {
private:
    int go[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
    char direction;
public:
    vector <position> snake_body;
    Snake() {
        position body;
        direction = 'r';
    }

    void set_direction() {
        int ch = getch();
        switch (ch) {
        case KEY_LEFT:
            direction = 'l';
            break;
        case KEY_RIGHT:
            direction = 'r';
            break;
        case KEY_UP:
            direction = 'u';
            break;
        case KEY_DOWN:
            direction = 'd';
            break;
        }
    }

    char get_direction() {
        return direction;
    }
};

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    Snake s1;
    s1.set_direction();
    cout << s1.get_direction();

    endwin();
    return 0;
}