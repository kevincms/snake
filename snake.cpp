#include <vector>
#include <curses.h>
#include <iostream>
#include <Windows.h> // ������ ���� �������

using namespace std;

struct Position // ��ǥ ���� ����ü
{
    int x, y;
};

class Snake {
private:
    Position prev; // ������ �̵��� �־��� ��ǥ
    char direction; // ����
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

    void set_direction() // ���� �Է¹ޱ�
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

    void move() // ������ũ ��ü �����̱�
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
            snake_body[0].y--;
            break;
        case 'd':
            snake_body[0].y++;
            break;
        }
    }

    void eat_growth(const int x, const int y) // ���� ������ ������ �Ǻ�, �۵�
    {
        if (snake_body[0].x == x && snake_body[0].y == y) snake_body.push_back(prev);
    }

    void eat_poison(const int x, const int y) // �� ������ ������ �Ǻ�, �۵�
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
    keypad(stdscr, TRUE); // Ư��Ű �Է� Ȱ��ȭ
    nodelay(stdscr, true);  // �Է� ��� ���� �ٷ� ��ȯ

    Snake s1;
    Sleep(1000); // �ð� 1��(1000ms)����
    s1.set_direction();
    s1.display();
    s1.move();
    s1.eat_poison(2, 2);
    s1.display();


    endwin();
    return 0;
}