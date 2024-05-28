#include <iostream>
#include <curses.h>
#include <random>
#include <vector>
#include "Map.h"
#include "snake.h"

using namespace std;

Map::Map(int map_size){
    // 0 : 빈공간, 1 : 벽, 2 끼인 벽, 
    // 10 : grow_item, 11 : poison_item, 12 : gate
    // 20: snake 머리, 21 : snake 몸
    if(map_size%2==0) map_size++;
    this->map_size=map_size;

    map=new int*[map_size];
    for(int i=0; i<map_size; i++) map[i]=new int[map_size];

    reset_map();
}

Map::~Map(){
    for(int i=0; i<map_size; i++) delete[] map[i];
    delete[] map;
}

void Map::reset_map(int stage){
    int wall=map_size/2+1;
    int half=wall/2;
    int start=wall-half-1;
    if(stage==0){
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
    else if(stage==1){
        reset_map();
        for (size_t i = 0; i < wall; i++){
            map[start+i][wall-half-1]=1;
        }
    }
    else if(stage==2){
        reset_map(1);
        for (size_t i = 0; i < wall; i++){
            map[start+i][wall+half-1]=1;
        }
    }
    else if(stage==3){
        reset_map(2);
        for (size_t i = 0; i < wall; i++){
            map[wall-half-1][start+i]=1;
        }
    }
    else if(stage==4){
        reset_map(3);
        for (size_t i = 0; i < wall; i++){
            map[wall+half-1][start+i]=1;
        }
    }
    
    
}

void Map::snake_to_map(Snake &snake){
    // 20: snake 머리, 21 : snake 몸
    int body_len=snake.snake_body.size();
    Position temp;
    temp=snake.snake_body[0];
    map[temp.y][temp.x]=20;
    for (size_t i = 1; i < body_len; i++){
        temp=snake.snake_body[i];
        map[temp.y][temp.x]=21;
    }
}
void Map::grow_item_to_map(Position grow){
    // 10 : grow_item, 11 : poison_item, 12 : gate
    map[grow.y][grow.x]=10;
}
void Map::poison_item_to_map(Position poison){
    // 10 : grow_item, 11 : poison_item, 12 : gate
    map[poison.y][poison.x]=11;
}
void Map::gate_to_map(Gate_Position gate){
    // 10 : grow_item, 11 : poison_item, 12 : gate
    map[gate.y][gate.x]=12;
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
    return poison_item;
}
Gate_Position Map::create_gate(){
    int temp;
    mt19937 gen(rd());
    vector<Gate_Position> gates;
    Gate_Position temp_P;

    for (int i = 0; i < map_size; i++){
        temp_P.x=i;
        for (int j = 0; j < map_size; j++){
            if(map[i][j]==1){
                temp_P.y=j;
                gates.push_back(temp_P);
            }
        }
    }
    uniform_int_distribution<int> dis(0, gates.size()-1);
    temp=dis(gen);
    return gates[temp];
}

bool Map::check_map_Pos(int x, int y){
    if(0<=x && x<map_size && 0<=y && y<map_size) return true;
    else return false;
}

Gate_Position Map::reset_gate_direction(Gate_Position gate){
    gate.u=false;
    gate.d=false;
    gate.r=false;
    gate.l=false;
    for (size_t i = 0; i < 4; i++) gate.gate_d[i]=false;
    return gate;
}

Gate_Position Map::find_gate_direction(Gate_Position gate){
    // 정면
    gate=reset_gate_direction(gate);
    if (check_map_Pos(gate.x,gate.y+1) && map[gate.x][gate.y+1]==0){
        gate.d=true;
        gate.gate_d[1]=true;
    }
    if (check_map_Pos(gate.x,gate.y-1) && map[gate.x][gate.y-1]==0){
        gate.u=true;
        gate.gate_d[0]=true;
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