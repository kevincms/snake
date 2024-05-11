#include <iostream>
#include <ncurses.h>
#include <string>

using namespace std;

int** map;

void create_map(int map_size){
    if(map_size%2==0) map_size++;

    map=new int*[map_size];
    for(int i=0; i<map_size; i++) map[i]=new int[map_size];

    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            if(i==0 or i==map_size-1 or j==0 or j==map_size-1) map[i][j]=1;
        }
    }
}

void delete_map(int map_size=21){
    if(map_size%2==0) map_size++;

    for(int i=0; i<map_size; i++) delete[] map[i];
    delete[] map;
}

void map_to_string(string &map_string, int map_size=21){
    if(map_size%2==0) map_size++;
    int check;
    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            check=map[i][j];
            if(!check) map_string.append(" ");
            else map_string.append("#");
        }
    }
}

void display_map(int map_size=21){
    if(map_size%2==0) map_size++;

    // newwin(height, width, x, y); x y 좌표에 window 생성
    WINDOW *win=newwin(map_size,map_size,0,0); // 윈도우 생성    
    string map_string;
    map_to_string(map_string,map_size);

    wprintw(win, map_string.c_str()); // 생성한 윈도우에 문자열 출력 가능

    refresh(); // 일반 새로고침 후 
    wrefresh(win); // 윈도우 새로고침
    getch();
}