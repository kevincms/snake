#include <iostream>
#include <curses.h>
#include <string>
#include "Gamemanger.h"

using namespace std;

Gamemanger::Gamemanger(){
    initial_setting();
}

Gamemanger::~Gamemanger(){
    
}

void Gamemanger::initial_setting(){
    // 0 : 빈공간, 1 : 벽, 2 끼인 벽, 
    // 10 : grow_item, 11 : poison_item, 12 : gate
    
    start_color(); // 터미널 색상 사용 선언

    // https://magmatart.dev/development/2017/06/15/ncurses4.html

    // init_color(num,r,g,b)
    init_color(0, 0, 0, 0); // 검은색
    init_color(1, 1000, 1000, 1000); // 흰색
    init_color(2, 900, 900, 900); // 라이트 그레이

    init_color(10, 0, 1000, 0); // 초록색
    init_color(12, 1000, 0, 0); // 보라색
    init_color(12, 1000, 0, 1000); // 보라색

    // 출력은 모두 문자를 사용하지 않고 배경색을 사용함.
    // init_pair(num, 문자색, 배경색)
    init_pair(0,0,0); // 빈공간
    init_pair(1,0,1); // 벽
    init_pair(2,0,2); // 끼인 벽
    init_pair(10,0,10); // grow_item
    init_pair(11,0,11); // poison_item
    init_pair(12,0,12); // gate
}

bool Gamemanger::is_gameover(Map &Map){

}
void Gamemanger::display(){

}