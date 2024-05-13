#include <iostream>
#include <curses.h>
#include "Map.h"

using namespace std;

extern int **map;

int main(){
    initscr(); // 시작
    Map Map;
    Map.display_map();
    string temp=to_string(Map.map[1][1]);
    Map.debug_print(temp); // debug를 할 수가 없어서 임시로 만듦.
    // 1. 3초 뒤에 시작
    // while(1){
    //     // 2. 0.5동안 방향키 입력받기. 입력이 여러 개일 경우 마지막 입력 사용. 아무 입력이 없으면 기존 방향대로. 처음 방향은 ->
    //     // 3. 입력받은 방향대로 이동
    //     // 4. 현재 위치가 범위 밖이면 gameover
    //     // 5. map reload(새로고침)
    // }

    // map 삭제(동적할당 해제)
    
    endwin(); // 끝
}