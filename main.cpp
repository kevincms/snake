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
    Position grow, poison;
    Gate_Position gate1, gate2;
    string temp_debug;

    grow=Map.create_grow_item();
    Map.grow_item_to_map(grow);
    poison=Map.create_poison_item();
    Map.poison_item_to_map(poison);

    gate1=Map.create_gate();
    gate1=Map.find_gate_direction(gate1);
    Map.gate_to_map(gate1);
    gate2=Map.create_gate();
    gate2=Map.find_gate_direction(gate2);
    Map.gate_to_map(gate2);

    Map.snake_to_map(snake);

    GM.display(Map);
    GM.display_debug(Map,snake);
    getch(); // 아무키 입력시 게임 시작
    while(!snake.quit){
        // 0.3초 동안 방향키 입력받기. 입력이 여러 개일 경우 마지막 입력 사용. 아무 입력이 없으면 기존 방향대로. 처음 방향은 ->
        snake.set_direction();
        snake.move(); // 입력받은 방향대로 이동

        // snake head가 벽을 만나거나 snake 몸체를 만나면 종료
        if(GM.is_gameover(Map,snake)) break;
        if(GM.is_stage_clear()){
            GM.stage++;
            Map.reset_map(GM.stage);
            GM.display(Map);
            getch();
            continue;
        }
        snake.eat_growth(grow);
        snake.eat_poison(poison);
        snake.go_gate(gate1,gate2);
        

        // 5. map reload(새로고침)
        Map.reset_map(GM.stage);
        Map.snake_to_map(snake);
        if(GM.is_eat_grow_item(grow,snake)) grow=Map.create_grow_item();
        Map.grow_item_to_map(grow);
        if(GM.is_eat_poison_item(poison,snake)) poison=Map.create_poison_item();
        Map.poison_item_to_map(poison);

        Map.gate_to_map(gate1);
        Map.gate_to_map(gate2);

        GM.display(Map);
        temp_debug="gate1 : "+to_string(gate1.u)+" "+to_string(gate1.d)+" "+to_string(gate1.r)+" "+to_string(gate1.l)+", gate2 : "+to_string(gate2.u)+" "+to_string(gate2.d)+" "+to_string(gate2.r)+" "+to_string(gate2.l);
        GM.display_debug(Map,snake,true,temp_debug);
           
    }

    // map 삭제(동적할당 해제)
    
    endwin(); // 끝
}