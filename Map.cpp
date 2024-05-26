#include <iostream>
#include <curses.h>
#include <string>
#include <random>
#include "Map.h"

using namespace std;

Map::Map(int map_size){
    // 0 : 빈공간, 1 : 벽, 2 끼인 벽, 
    // 10 : grow_item, 11 : poison_item, 12 : gate
    if(map_size%2==0) map_size++;
    this->map_size=map_size;

    map=new int*[map_size];
    for(int i=0; i<map_size; i++) map[i]=new int[map_size];

    for (int i = 0; i < map_size; i++){
        for (int j = 0; j < map_size; j++){
            if(i==0 or i==map_size-1 or j==0 or j==map_size-1) map[i][j]=1;
            else map[i][j]=0;
        }
    }
    map[0][0]=2;
    map[0][map_size-1]=2;
    map[map_size-1][0]=2;
    map[map_size-1][map_size-1]=2;
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

void Map::display_map2(){
    for (size_t i = 0; i < map_size; i++){
        for (size_t j = 0; j < map_size; j++){
            cout<<map[i][j];
        }
        cout<<endl;
    }
    
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

Position Map::create_grow_item(){
    int temp;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, map_size-2);
    Position grow_item;
    grow_item.x=dis(gen);
    grow_item.y=dis(gen);
    while (map[grow_item.x][grow_item.y]!=0){
        temp=++grow_item.x/map_size;
        grow_item.x=(grow_item.x)%(map_size);
        grow_item.y=(grow_item.y+temp)%(map_size);
    }
    map[grow_item.x][grow_item.y]=10;
    return grow_item;
}
Position Map::create_poison_item(){
    int temp;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, map_size-2);
    Position poison_item;
    poison_item.x=dis(gen);
    poison_item.y=dis(gen);
    while (map[poison_item.x][poison_item.y]!=0){
        temp=++poison_item.x/map_size;
        poison_item.x=(poison_item.x)%(map_size);
        poison_item.y=(poison_item.y+temp)%(map_size);
    }
    map[poison_item.x][poison_item.y]=11;
    return poison_item;
}
Position Map::create_gate(){
    int temp;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, map_size-2);
    Gate_Position gate;
    gate.x=dis(gen);
    gate.y=dis(gen);
    while (map[gate.x][gate.y]!=0){
        temp=++gate.x/map_size;
        gate.x=(gate.x)%(map_size);
        gate.y=(gate.y+temp)%(map_size);
    }
    // gate 위치에 따른 나가는 방향
    map[gate.x][gate.y]=12;
    return gate;
}

bool Map::check_map_Pos(int x, int y){
    if(0<=x && x<map_size && 0<=y && y<map_size) return true;
    else return false;
}

Gate_Position Map::find_gate_direction(Gate_Position gate){
    // 정면
    if (check_map_Pos(gate.x,gate.y+1) && map[gate.x][gate.y+1]==0){
        gate.u=true;
        gate.gate_d[0]=true;
    }
    if (check_map_Pos(gate.x,gate.y-1) && map[gate.x][gate.y-1]==0){
        gate.d=true;
        gate.gate_d[1]=true;
    }
    if (check_map_Pos(gate.x+1,gate.y) && map[gate.x+1][gate.y]==0){
        gate.r=true;
        gate.gate_d[2]=true;
    }
    if (check_map_Pos(gate.x-1,gate.y) && map[gate.x-1][gate.y]==0){
        gate.l=true;
        gate.gate_d[3]=true;
    }
    return gate;
}