#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include "Gamemanger.h"

using namespace std;

Gamemanger::Gamemanger(){
    initial_setting();
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
    score_board.Current_len=3;

}

Gamemanger::~Gamemanger(){
    
}

void Gamemanger::initial_setting(){
    // 0 : 빈공간, 1 : 벽, 2 끼인 벽, 
    // 10 : grow_item, 11 : poison_item, 12 : gate
    // 20: snake 머리, 21 : snake 몸

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
    init_pair(20,0,20); // snake 머리
    init_pair(21,0,21); // snake 몸
}

bool Gamemanger::is_gameover(Map &Map){

}

void Gamemanger::check_misson(){
    if(score_board.Max_len>=mission_board.B) mission_board.check_string[0]="O";
    else mission_board.check_string[0]="X";

    if(score_board.plus>=mission_board.plus) mission_board.check_string[1]="O";
    else mission_board.check_string[0]="X";

    if(score_board.minus>=mission_board.minus) mission_board.check_string[0]="O";
    else mission_board.check_string[0]="X";

    if(score_board.gate_count>=mission_board.gate_count) mission_board.check_string[0]="O";
    else mission_board.check_string[0]="X";
}

void Gamemanger::display(Map &Map){
    display_map(Map);
    display_score(Map);
    check_misson();
    display_misssion(Map);
    
    
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
    
    vector<string> score_string={"Score Board","B : ","+ : ","- : ","G : "};
    score_string[1]+="("+to_string(score_board.Current_len)+") / ("+to_string(score_board.Max_len)+")";
    score_string[2]+="("+to_string(score_board.plus)+")";
    score_string[3]+="("+to_string(score_board.minus)+")";
    score_string[4]+="("+to_string(score_board.gate_count)+")";
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