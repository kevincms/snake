#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include <chrono>
#include "Gamemanger.h"
#include "snake.h"

using namespace std;

Gamemanger::Gamemanger(){
    initial_setting();
    reset_mission_by_stage();
    // reset_mission_by_stage(true);
}

Gamemanger::~Gamemanger(){
    
}

void Gamemanger::get_game_start_time(){
    start=chrono::system_clock::now();
}

double Gamemanger::get_game_progress_time(){
    chrono::duration<double>sec = chrono::system_clock::now() - start;
    return sec.count();
}

void Gamemanger::reset_mission_by_stage(bool test){
    if(test){
        mission_board.B=3;
        score_board.Max_len=mission_board.B;
        mission_board.plus=1;
        mission_board.minus=0;
        mission_board.gate_count=0;
    }
    else{
        if(stage==0){ // 스테이지 별 난이도
            mission_board.B=4;
            score_board.Max_len=mission_board.B;
            mission_board.plus=1;
            mission_board.minus=0;
            mission_board.gate_count=1;
        }
        else if(stage==1){
            mission_board.B=5;
            score_board.Max_len=mission_board.B;

            mission_board.plus=2;
            mission_board.minus=0;
            mission_board.gate_count=2;
        }
        else if(stage==2){
            mission_board.B=6;
            score_board.Max_len=mission_board.B;

            mission_board.plus=4;
            mission_board.minus=1;
            mission_board.gate_count=3;
        }
        else if(stage==3){
            mission_board.B=8;
            score_board.Max_len=mission_board.B;

            mission_board.plus=7;
            mission_board.minus=3;
            mission_board.gate_count=5;
        }
    }
    for (size_t i = 0; i < 4; i++) mission_board.check_string[i]="X";
    score_board.Current_len=3;
}

void Gamemanger::initial_setting(){
    // 0 : 빈공간, 1 : 벽, 2 끼인 벽, 
    // 10 : grow_item, 11 : poison_item, 12 : gate, 13 : special_item
    // 20: snake 머리, 21 : snake 몸

    raw();
    keypad(stdscr, true);
    noecho();
    nodelay(stdscr, true);
    curs_set(0); // 커서 없애기
    start_color(); // 터미널 색상 사용 선언

    // https://magmatart.dev/development/2017/06/15/ncurses4.html

    // init_color(num,r,g,b)
    init_color(0, 0, 0, 0); // 검은색
    init_color(1, 1000, 1000, 1000); // 흰색
    init_color(2, 900, 900, 900); // 라이트 그레이

    init_color(10, 0, 1000, 0); // 초록색
    init_color(11, 1000, 0, 0); // 빨간색
    init_color(12, 1000, 0, 1000); // 보라색
    init_color(13, 0, 0, 1000); // 파란색

    init_color(20, 1000, 1000, 0); // 노란색
    init_color(21, 1000, 500, 0); // 주황색

    // 출력은 모두 문자를 사용하지 않고 배경색을 사용함.
    // init_pair(num, 문자색, 배경색)
    init_pair(0,0,0); // 빈공간
    init_pair(1,0,1); // 벽
    init_pair(2,0,2); // 끼인 벽
    init_pair(10,0,10); // grow_item
    init_pair(11,0,11); // poison_item
    init_pair(12,0,12); // gate
    init_pair(13,0,13); // special_item
    init_pair(20,0,20); // snake 머리
    init_pair(21,0,21); // snake 몸
}

bool Gamemanger::is_stage_clear(){
    if(score_board.Current_len<mission_board.B) return false;
    if(score_board.plus<mission_board.plus) return false;
    if(score_board.minus<mission_board.minus) return false;
    if(score_board.gate_count<mission_board.gate_count) return false;
    return true;
}

bool Gamemanger::is_gameover(Map &Map, Snake &snake){
    int body_len=snake.snake_body.size();
    Position head, temp;
    head=snake.snake_body[0];
    // 0 : 빈공간, 1 : 벽, 2 끼인 벽, 
    if(score_board.Current_len<=2) return true;
    if(Map.map[head.y][head.x]==1) return true;
    for (size_t i = 1; i < body_len; i++){
        temp=snake.snake_body[i];
        if(temp.x==head.x && temp.y==head.y) return true;
    }
    return false;
}

bool Gamemanger::can_create_grow_item(){
    int time=(int)get_game_progress_time();
    int count=time/15;
    time=time%15;
    if(3<=time && time<=12 && count != grow_create_count){
        grow_create_count=count;
        return true;
    }
    return false;
}

bool Gamemanger::can_create_poison_item(){
    int time=(int)get_game_progress_time();
    int count=time/15;
    time=time%15;
    if(3<=time && time<=12 && count != poison_create_count){
        poison_create_count=count;
        return true;
    }
    return false;
}

bool Gamemanger::can_create_special_item(){
    int time=(int)get_game_progress_time();
    int count=time/15;
    time=time%15;
    if(3<=time && time<=12 && count != special_create_count){
        special_create_count=count;
        return true;
    }
    return false;
}

bool Gamemanger::can_create_gate(){
    int time=(int)get_game_progress_time();
    time=time%10;
    if(2<=time && time<=9) return true;
    return false;
}

bool Gamemanger::can_delete_item(){
    int time=(int)get_game_progress_time();
    time=time%15;
    if(3<=time && time<=12){
        return false;
    }
    return true;
}

bool Gamemanger::can_delete_gate(Snake snake, Gate_Position gate1, Gate_Position gate2){
    int time=(int)get_game_progress_time();
    time=time%10;
    if(2<=time && time<=9) return false;
    if(snake.go_gate(gate1,gate2)) return false;
    return true;
}

bool Gamemanger::is_eat_item(Position item, Snake &snake){
    Position head;
    head=snake.snake_body[0];
    if(head.y==item.y&&head.x==item.x) return true;
    else return false;
}

void Gamemanger::update_score_board(bool grow, bool poison, bool gate){
    if(grow){
        if(score_board.Current_len!=score_board.Max_len) score_board.Current_len++;
        score_board.plus++;
    }
    else if(poison){
        score_board.Current_len--;
        score_board.minus++;
    }
    else if(gate) score_board.gate_count++;
}
void Gamemanger::reset_score_board(){
    score_board.Current_len=3;
    score_board.Max_len=0;
    score_board.plus=0;
    score_board.minus=0;
    score_board.gate_count=0;
    grow_create_count=-1;
    poison_create_count=-1;
    special_create_count=-1;
}

void Gamemanger::check_misson(){
    if(score_board.Current_len>=mission_board.B) mission_board.check_string[0]="O";
    else mission_board.check_string[0]="X";

    if(score_board.plus>=mission_board.plus) mission_board.check_string[1]="O";
    else mission_board.check_string[1]="X";

    if(score_board.minus>=mission_board.minus) mission_board.check_string[2]="O";
    else mission_board.check_string[2]="X";

    if(score_board.gate_count>=mission_board.gate_count) mission_board.check_string[3]="O";
    else mission_board.check_string[3]="X";
}

void Gamemanger::display(Map &Map){
    display_map(Map);
    display_score(Map);
    check_misson();
    display_misssion(Map);
}

void Gamemanger::display_debug(Map &Map, Snake &snake, bool check, string test_string){
    // newwin(height, width, y, x); x y 좌표에 window 생성
    WINDOW *win=newwin(1,Map.map_size*2,Map.map_size+1,0);
    string debug_string;
    Position temp;
    temp=snake.snake_body[0];
    debug_string=to_string(temp.x)+" "+to_string(temp.y);

    if(check) wprintw(win, test_string.c_str());
    else wprintw(win, debug_string.c_str());

    refresh(); // 일반 새로고침 후 
    wrefresh(win); // 윈도우 새로고침
}

void Gamemanger::display_map(Map &Map){
    // newwin(height, width, y, x); x y 좌표에 window 생성
    WINDOW *win=newwin(Map.map_size,Map.map_size,0,0);
    
    int color;
    for (int i = 0; i < Map.map_size; i++){
        for (int j = 0; j < Map.map_size; j++){
            color=Map.map[i][j];
            wattron(win, COLOR_PAIR(color));
            // mvwprintw(win,y,x)
            mvwprintw(win, i, j, " ");
            wattroff(win, COLOR_PAIR(color));
        }
    }
    refresh(); // 일반 새로고침 후 
    wrefresh(win); // 윈도우 새로고침
}

void Gamemanger::display_score(Map &Map){
    // newwin(height, width, y, x); x y 좌표에 window 생성
    WINDOW *win=newwin(Map.map_size/2,Map.map_size,0,Map.map_size+1);
    
    vector<string> score_string={"Score Board","B : ","+ : ","- : ","G : ","Speed : ","Time : "};
    score_string[1]+="("+to_string(score_board.Current_len)+") / ("+to_string(score_board.Max_len)+")";
    score_string[2]+="("+to_string(score_board.plus)+")";
    score_string[3]+="("+to_string(score_board.minus)+")";
    score_string[4]+="("+to_string(score_board.gate_count)+")";
    score_string[5]+=to_string((float)300/tick_time);
    score_string[6]+=to_string((int)get_game_progress_time())+" sec";
    // mvwprintw(win,y,x)
    for (size_t i = 0; i < score_string.size(); i++){
        mvwprintw(win, 2+i, 2, score_string[i].c_str());
    }
    refresh(); // 일반 새로고침 후 
    wrefresh(win); // 윈도우 새로고침
}

void Gamemanger::display_misssion(Map &Map){
    // newwin(height, width, y, x); x y 좌표에 window 생성
    WINDOW *win=newwin(Map.map_size/2,Map.map_size,Map.map_size/2+1,Map.map_size+1);

    vector<string> mission_string={"Mission","B : ","+ : ","- : ","G : "};
    mission_string[1]+=to_string(mission_board.B)+ " ("+mission_board.check_string[0]+")";
    mission_string[2]+=to_string(mission_board.plus)+" ("+mission_board.check_string[1]+")";
    mission_string[3]+=to_string(mission_board.minus)+" ("+mission_board.check_string[2]+")";
    mission_string[4]+=to_string(mission_board.gate_count)+" ("+mission_board.check_string[3]+")";
    // mvwprintw(win,y,x)
    for (size_t i = 0; i < mission_string.size(); i++){
        mvwprintw(win, 2+i, 2, mission_string[i].c_str());
    }
    refresh(); // 일반 새로고침 후 
    wrefresh(win); // 윈도우 새로고침
}