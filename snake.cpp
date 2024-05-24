#include <vector>
#include <curses.h>
#include <iostream>
#include <Windows.h> // ������ ���� �������
#include "snake.h"

using namespace std;


Snake::Snake() {
    prev = { 0, 0 };
    Position body; // default snake_body position 
    body = { 1, 2 };
    snake_body.push_back(body);
    body = { 2, 3 };
    snake_body.push_back(body);
    body = { 3, 4 };
    snake_body.push_back(body);
    direction = 'r'; // default direction
}

void Snake::set_direction() // ���� �Է¹ޱ�
{
    Sleep(5000);
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

void Snake::move() // ������ũ ��ü �����̱�
{
    // ���� ������ ��ǥ ����
    prev = snake_body.back();
    // ���� �����̱�
    for (int i = snake_body.size() - 1; i > 0; i--) snake_body[i] = snake_body[i - 1];
    // �Ӹ� �����̱�
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

void Snake::eat_growth(const int x, const int y) // ���� ������ ������ �Ǻ�, �۵�
{
    if (snake_body[0].x == x && snake_body[0].y == y) {
        snake_body.push_back(prev);
        cnt_growth++;
    }
}

void Snake::eat_poison(const int x, const int y) // �� ������ ������ �Ǻ�, �۵�
{
    if (snake_body[0].x == x && snake_body[0].y == y) {
        snake_body.pop_back();
        cnt_poison++;
    }
}

// bool go_gate(const int gate1[], const int gate2[]) // ����Ʈ ��������� �Ǻ� + �̵�
// {

// }

char Snake::get_direction() {
    return direction;
}

int Snake::get_cnt_growth() {
    return cnt_growth;
}

int Snake::get_cnt_poison() {
    return cnt_poison;
}

int Snake::get_cnt_gate() {
    return cnt_gate;
}
// void display() {
//     for (int i = 0; i < snake_body.size(); i++) cout << "(" << snake_body[i].x << "," << snake_body[i].y << ") ";
//     cout << endl;
// }