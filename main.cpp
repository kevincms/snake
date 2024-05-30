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
    bool existence_grow_item{0}, existence_poison_item{0}, existence_gate{0};
    bool use_gate_start{1};

    // 바로 아이템 생성
    // grow=Map.create_grow_item();
    // Map.grow_item_to_map(grow);
    // existence_grow_item=true;

    // 바로 게이트 생성
    // gate1=Map.create_gate();
    // gate1=Map.find_gate_direction(gate1);
    // Map.gate_to_map(gate1);
    // gate2=Map.create_gate();
    // gate2=Map.find_gate_direction(gate2);
    // Map.gate_to_map(gate2);

    Map.snake_to_map(snake);
    GM.display(Map);
    GM.display_debug(Map,snake);
    while (getch()==ERR) // 아무키 입력시 게임 시작
    GM.get_game_start_time();
    while(!snake.quit){
        // 0.3초 동안 방향키 입력받기. 입력이 여러 개일 경우 마지막 입력 사용. 아무 입력이 없으면 기존 방향대로. 처음 방향은 ->
        snake.set_direction();
        snake.move(); // 입력받은 방향대로 이동

        // snake head가 벽을 만나거나 snake 몸체를 만나면 종료
        if(GM.is_gameover(Map,snake)) break;
        // 아이템 생성
        if(GM.can_create_grow_item()){
            if(!existence_grow_item){
                grow=Map.create_grow_item();
                Map.grow_item_to_map(grow);
                existence_grow_item=true;
            }
        }
        if(GM.can_create_poison_item()){
            if(!existence_poison_item){
                poison=Map.create_poison_item();
                Map.poison_item_to_map(poison);
                existence_poison_item=true;
            }
        }
        // gate 생성
        if(GM.can_create_gate()){
            if(!existence_gate){
                gate1=Map.create_gate();
                gate1=Map.find_gate_direction(gate1);
                Map.gate_to_map(gate1);
                gate2=Map.create_gate();
                gate2=Map.find_gate_direction(gate2);
                Map.gate_to_map(gate2);
                existence_gate=true;
            }
        }

        // 아이템 획득 시 action
        if(GM.is_eat_grow_item(grow,snake)){
            snake.eat_growth(grow);
            GM.update_score_board(true,false,false);
        }
        if(GM.is_eat_poison_item(poison,snake)){
            snake.eat_poison(poison);
            GM.update_score_board(false,true,false);
        }
        // gate 통과 시 action
        if(existence_gate){
            if(!snake.go_gate(gate1,gate2)) use_gate_start=true;
            else if(snake.go_gate(gate1,gate2) && use_gate_start){
                GM.update_score_board(false,false,true);
                use_gate_start=false;
            }

        }

        // 스테이지 클리어시 다음 스테이지로
        if(GM.is_stage_clear()){
            GM.stage++;
            if(GM.stage==5) break;
            Map.reset_map(GM.stage);
            GM.reset_score_board();
            GM.reset_mission_by_stage();
            snake.reset();
            Map.snake_to_map(snake);
            GM.display(Map);
            while (getch()==ERR)
            existence_grow_item=false;
            existence_poison_item=false;
            existence_gate=false;
            use_gate_start=true;
            GM.get_game_start_time();
            continue;
        }        

        // Map relaod
        Map.reset_map(GM.stage);
        Map.snake_to_map(snake);

        // if(GM.is_eat_grow_item(grow,snake)) grow=Map.create_grow_item(); // item 먹자마자 바로 생성
        if(GM.is_eat_grow_item(grow,snake) || GM.can_delete_item()) existence_grow_item=false;
        if(existence_grow_item) Map.grow_item_to_map(grow);

        // if(GM.is_eat_poison_item(poison,snake) poison=Map.create_poison_item(); // item 먹자마자 바로 생성
        if(GM.is_eat_poison_item(poison,snake) || GM.can_delete_item()) existence_poison_item=false;
        if(existence_poison_item) Map.poison_item_to_map(poison);
        if(GM.can_delete_gate(snake,gate1,gate2)){
            use_gate_start=true;
            existence_gate=false;
        }
        if(existence_gate){
            Map.gate_to_map(gate1);
            Map.gate_to_map(gate2);    
        }
        
        // 출력하기
        GM.display(Map);
        // temp_debug="gate1 : "+to_string(gate1.u)+" "+to_string(gate1.d)+" "+to_string(gate1.r)+" "+to_string(gate1.l)+", gate2 : "+to_string(gate2.u)+" "+to_string(gate2.d)+" "+to_string(gate2.r)+" "+to_string(gate2.l);
        temp_debug=to_string(GM.get_game_progress_time());
        // temp_debug=to_string(GM.mission_board.B)+" "+to_string(GM.score_board.Current_len)+" "+to_string(GM.score_board.Max_len)+" "+GM.mission_board.check_string[0]+GM.mission_board.check_string[1]+GM.mission_board.check_string[2]+GM.mission_board.check_string[3];
        // temp_debug=to_string(snake.go_gate(gate1,gate2))+" "+to_string(existence_gate)+" "+to_string(GM.can_create_gate());
        GM.display_debug(Map,snake,true,temp_debug);
    }
    
    endwin(); // 끝
}