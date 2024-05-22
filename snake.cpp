#include <vector>
#include <curses.h>
#include <iostream>
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
public:
    vector <Position> snake_body;
    Snake() {
        Position body; // default snake_body position 
        body = { 1, 2 };
        snake_body.push_back(body);
        body = { 2, 3 };
        snake_body.push_back(body);
        body = { 3, 4 };
        snake_body.push_back(body);
        direction = 'r'; // default direction
    }

    void set_direction() // 방향 입력받기
    {
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

    void move() // 스네이크 전체 움직이기
    {
        // 꼬리 마지막 좌표 저장
        prev = snake_body.back();
        // 몸통 움직이기
        for (int i = snake_body.size() - 1; i > 0; i--) snake_body[i] = snake_body[i - 1];
        // 머리 움직이기
        switch (direction) {
        case 'l':
            snake_body[0].x--;
            break;
        case 'r':
            snake_body[0].x++;
            break;
        case 'u':
            snake_body[0].y--;
            break;
        case 'd':
            snake_body[0].y++;
            break;
        }
    }

    void eat_growth(const int x, const int y) // 성장 아이템 먹은지 판별, 작동
    {
        if (snake_body[0].x == x && snake_body[0].y == y) snake_body.push_back(prev);
    }

    void eat_poison(const int x, const int y) // 독 아이템 먹은지 판별, 작동
    {
        if (snake_body[0].x == x && snake_body[0].y == y) snake_body.pop_back();
    }

    bool go_gate(int gate1[], int gate2[]) {

    }

    char get_direction() {
        return direction;
    }

    void display() {
        for (int i = 0; i < snake_body.size(); i++) cout << "(" << snake_body[i].x << "," << snake_body[i].y << ") ";
        cout << endl;
    }
};

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // 특수키 입력 활성화
    nodelay(stdscr, true);  // 입력 대기 없이 바로 반환

    Snake s1;
    Sleep(1000); // 시간 1초(1000ms)지연
    s1.set_direction();
    s1.display();
    s1.move();
    s1.eat_poison(2, 2);
    s1.display();


    endwin();
    return 0;
}