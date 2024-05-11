#include <iostream>
#include <ncurses.h>
#include "Map.h"

using namespace std;

extern int **map;

int main(){
    initscr(); // 시작
    create_map(); // map 생성(동적할당)
    display_map(); // map display
    // 1. 방향키 아무거나 입력하면 시작
    // while(1){
    //     // 2. 0.5동안 방향키 입력받기. 입력이 여러 개일 경우 마지막 입력 사용. 아무 입력이 없으면 기존 방향대로. 처음 방향은 ->
    //     // 3. 입력받은 방향대로 이동
    //     // 4. 현재 위치가 범위 밖이면 gameover
    //     // 5. map reload(새로고침)
    // }

    // map 삭제(동적할당 해제)
    delete_map();
    endwin(); // 끝
}