#include <iostream>
#include <curses.h>
#include "Map.h"
#include "Gamemanger.h"
#include "snake.h"

using namespace std;

int main(){
    initscr(); // 시작
    
    Map Map;
    Gamemanger GM;
    Snake snake;

    Map.snake_to_map(snake);

    Position test;
    test=Map.create_grow_item();
    Map.map[test.x][test.y]=10;
    test=Map.create_poison_item();
    Map.map[test.x][test.y]=11;
    test=Map.create_gate();
    Map.map[test.x][test.y]=12;
    test=Map.create_gate();
    Map.map[test.x][test.y]=12;

    GM.display(Map);
    GM.display_debug(Map,snake);
    getch();
    // 1. 3초 뒤에 시작
    while(!snake.quit){
        // 2. 0.5동안 방향키 입력받기. 입력이 여러 개일 경우 마지막 입력 사용. 아무 입력이 없으면 기존 방향대로. 처음 방향은 ->
        snake.set_direction(Map,snake,GM);
        // 3. 입력받은 방향대로 이동
        snake.move();

        // 4. 현재 위치가 범위 밖이면 gameover

        // 5. map reload(새로고침)
        Map.snake_to_map(snake);
        GM.display(Map);
        GM.display_debug(Map,snake);
           
    }

    // map 삭제(동적할당 해제)
    
    endwin(); // 끝
}