#include <iostream>
#include <curses.h>
#include <string>
#include "Map.h"

using namespace std;

Map::Map(int map_size){
    if(map_size%2==0) map_size++;
    this->map_size=map_size;

    map=new int*[map_size];
    for(int i=0; i<map_size; i++) map[i]=new int[map_size];

    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            if(i==0 or i==map_size-1 or j==0 or j==map_size-1) map[i][j]=1;
        }
    }
}

Map::~Map(){
    for(int i=0; i<map_size; i++) delete[] map[i];
    delete[] map;
}

void Map::display_map(){
    // newwin(height, width, y, x); x y 좌표에 window 생성
    WINDOW *win=newwin(map_size,map_size,0,0); // 윈도우 생성    
    string map_string;
    this->map_to_string(map_string);

    wprintw(win, map_string.c_str()); // 생성한 윈도우에 문자열 출력 가능

    refresh(); // 일반 새로고침 후 
    wrefresh(win); // 윈도우 새로고침
    getch(); // 키보드 입력이 있어야 다음으로 진행됨.
}

void Map::map_to_string(string &map_string){
    int check;
    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            check=map[i][j];
            if(!check) map_string.append(" ");
            else map_string.append("#");
        }
    }
}

void Map::debug_print(string &debug_str){
    WINDOW *temp=newwin(1,100,map_size,0);
    wprintw(temp, debug_str.c_str());

    refresh(); // 일반 새로고침 후 
    wrefresh(temp); // 윈도우 새로고침
    getch(); // 키보드 입력이 있어야 다음으로 진행됨.
}