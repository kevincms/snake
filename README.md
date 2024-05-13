# snake
슈슉 슈숙. 슉. 슈수뱀이다.

## 파일 분할 구상
> ### Map
> - class로 만듦.
> - snake 게임의 기본 틀 + 아이템과 게이트 관리
>> #### function
>> 1. 생성자와 소멸자로 int **map에 맵 저장. Gamemanager에서 알아서 가져감.
>> 2. create_gate : gate 생성. gate 좌표와 가장자리 여부 Snake에 리턴
>> 3. create_item : item 생성. item 좌표와 item 종류 Snake에 리턴

|function|input|return|  
|---|---|---|  
|create_gate|None|Snake::gate 좌표와 가장자리 여부|
|create_item|None|Snake::item 좌표와 item 종류|

> ### Snake
> - class로 만듦.
> - snake의 몸체 부분과 각종 상호작용(기본 움직임, 아이템 획득 여부, 게이트 통과 움직임)을 관리
>> #### function
>> 1. input : 0.5초동안 입력을 받아서 스네이크의 움직임을 결정.
>> 2. move_with_gate : Map으로부터 gate 좌표와 가장자리 여부를 전달받아 움직임 처리
>> 3. gain_item : Map으로부터 item 좌표와 item 종류를 전달받아 점수(snake 길이) Gamemanager에 전달

|function|input|return|  
|---|---|---|  
|input|키보드 입력|None|
|move_with_gate|Map::gate좌표와 가장자리 여부|None|
|gain_item|Map::item 좌표와 item 종류|Gamemanager::점수(snake 길이)|

> ### Gamemanager
> - class로 만듦.
> - 점수, 시간, 게임오버 여부, 스크린 디스플레이 등 전반적인 운영을 관리
>> #### function
>> - 1. is_gameover : Snake에서 snake 좌표와 Map에서 map을 가져와 게임이 종료됬는지 판단해 bool값 반환

|function|input|return|  
|---|---|---|  
|is_gameover|Map::map 좌표, Snake::snake 좌표|bool|

