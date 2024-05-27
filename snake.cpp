#include <vector>
#include <curses.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "snake.h"

using namespace std;


Snake::Snake() {
    cnt_growth = 0;
    cnt_poison = 0;
    cnt_gate = 0;
    prev = { 0, 0 };
    snake_body = { {11,11}, {10,11}, {9,11} };
    direction = 'r'; // default direction
}

void Snake::set_direction() // set direction from keyboard
{
    while (true) {
        static const auto tickDuration = std::chrono::milliseconds(1000);

        std::this_thread::sleep_for(tickDuration);

        int ch = getch();
        if (ch == ERR) break;
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
}

void Snake::move()
{
    // save tail position
    prev = snake_body.back();
    // move snake body
    for (int i = snake_body.size() - 1; i > 0; i--) snake_body[i] = snake_body[i - 1];
    // move snake head
    switch (direction) {
    case 'l':
        snake_body[0].x--;
        break;
    case 'r':
        snake_body[0].x++;
        break;
    case 'u':
        snake_body[0].y++;
        break;
    case 'd':
        snake_body[0].y--;
        break;
    }
}

void Snake::eat_growth(const Position item) // ���� ������ ������ �Ǻ�, �۵�
{
    if (snake_body[0].x == item.x && snake_body[0].y == item.y) {
        snake_body.push_back(prev);
        cnt_growth++;
    }
}

void Snake::eat_poison(const Position item) // �� ������ ������ �Ǻ�, �۵�
{
    if (snake_body[0].x == item.x && snake_body[0].y == item.y) {
        snake_body.pop_back();
        cnt_poison++;
    }
}

bool Snake::go_gate(const Gate_Position gate1, const Gate_Position gate2) // ����Ʈ ���������? �Ǻ� + �̵�
{
    bool in_gate1{ false }, in_gate2{ false };

    for (int i = 0; i < snake_body.size(); i++) {
        if (snake_body[i].x == gate1.x && snake_body[i].y == gate1.y) {
            if (i == 0) cnt_gate++; // when head in gate, cnt++
            in_gate1 = true;
            snake_body[i].x = gate2.x;
            snake_body[i].y = gate2.y;
        }
        else if (snake_body[i].x == gate2.x && snake_body[i].y == gate2.y) {
            if (i == 0) cnt_gate++; // when head in gate, cnt++
            in_gate2 = true;
            snake_body[i].x = gate1.x;
            snake_body[i].y = gate1.y;
        }

        if (in_gate1) {
            if (direction == 'r') { // when direction right
                if (gate2.r) {
                    snake_body[i].x++;
                    break;
                }
                else if (gate2.d) {
                    snake_body[i].y--;
                    break;
                }
                else if (gate2.u) {
                    snake_body[i].y++;
                    break;
                }
                else if (gate2.l) {
                    snake_body[i].x--;
                    break;
                }
            }
            else if (direction == 'l') { // when direction left
                if (gate2.l) {
                    snake_body[i].x--;
                    break;
                }
                else if (gate2.u) {
                    snake_body[i].y++;
                    break;
                }
                else if (gate2.d) {
                    snake_body[i].y--;
                    break;
                }
                else if (gate2.r) {
                    snake_body[i].x++;
                    break;
                }
            }
            else if (direction == 'u') { // when direction up
                if (gate2.u) {
                    snake_body[i].y++;
                    break;
                }
                else if (gate2.r) {
                    snake_body[i].x++;
                    break;
                }
                else if (gate2.l) {
                    snake_body[i].x--;
                    break;
                }
                else if (gate2.d) {
                    snake_body[i].y--;
                    break;
                }
            }
            else if (direction == 'd') { // when direction down
                if (gate2.d) {
                    snake_body[i].y--;
                    break;
                }
                else if (gate2.l) {
                    snake_body[i].x--;
                    break;
                }
                else if (gate2.r) {
                    snake_body[i].x++;
                    break;
                }
                else if (gate2.u) {
                    snake_body[i].y++;
                    break;
                }
            }
        }

        else if (in_gate2) {
            if (direction == 'r') { // when direction right
                if (gate1.r) {
                    snake_body[i].x++;
                    break;
                }
                else if (gate1.d) {
                    snake_body[i].y--;
                    break;
                }
                else if (gate1.u) {
                    snake_body[i].y++;
                    break;
                }
                else if (gate1.l) {
                    snake_body[i].x--;
                    break;
                }
            }
            else if (direction == 'l') { // when direction left
                if (gate1.l) {
                    snake_body[i].x--;
                    break;
                }
                else if (gate1.u) {
                    snake_body[i].y++;
                    break;
                }
                else if (gate1.d) {
                    snake_body[i].y--;
                    break;
                }
                else if (gate1.r) {
                    snake_body[i].x++;
                    break;
                }
            }
            else if (direction == 'u') { // when direction up
                if (gate1.u) {
                    snake_body[i].y++;
                    break;
                }
                else if (gate1.r) {
                    snake_body[i].x++;
                    break;
                }
                else if (gate1.l) {
                    snake_body[i].x--;
                    break;
                }
                else if (gate1.d) {
                    snake_body[i].y--;
                    break;
                }
            }
            else if (direction == 'd') { // when direction down
                if (gate1.d) {
                    snake_body[i].y--;
                    break;
                }
                else if (gate1.l) {
                    snake_body[i].x--;
                    break;
                }
                else if (gate1.r) {
                    snake_body[i].x++;
                    break;
                }
                else if (gate1.u) {
                    snake_body[i].y++;
                    break;
                }
            }
        }
    }
    if (in_gate1 || in_gate2) return true;
    else return false;
}

char Snake::get_direction() {
    return direction;
}

int Snake::get_cnt_growth() const {
    return cnt_growth;
}

int Snake::get_cnt_poison() const {
    return cnt_poison;
}

int Snake::get_cnt_gate() const {
    return cnt_gate;
}

