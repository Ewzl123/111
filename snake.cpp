#include<snake.h>

Map::Map(){
    map = new MapDot*[SIZE];
    for(int i = 0;i<SIZE;++i){
        map[i] = new MapDot[SIZE];
    }
    snake = new Snake ;

    InitMap();
    
}

Map::~Map(){
    for(int i = 0;i<SIZE;++i){
        delete map[SIZE-i];
    }
    delete map;
    delete snake;
}

void Map::InitMap(){
    InitSnake();
    int i,j;
    for( i = 0;i<SIZE;++i){//这里可以增加地图编辑选择，障碍物也在这里放
        for( j=0;j<SIZE;++j){
            map[i][j].state=Empty;
            map[i][j].SnakeNext=0;
        }
    }
    i=snake->SnakeBodyX.front(); 
    j=snake->SnakeBodyY.front();
    map[i][j].state=(enum Thing)2;
    map[i][j-1].SnakeNext=1;
    score=0;

}

void Map::InitSnake(){
    while(!snake->SnakeBodyX.empty()){
        snake->SnakeBodyX.pop();
    }
    while(!snake->SnakeBodyY.empty()){
        snake->SnakeBodyY.pop();
    }
    snake->SnakeBodyX.push(SIZE/2);
    snake->SnakeBodyY.push(SIZE/2);
    snake->SnakeDirection=UP;
    snake->SnakeLenth=1;
}

void Map::Move(int direct){
    int i,j;
    i=snake->SnakeBodyX.back(); 
    j=snake->SnakeBodyY.back();
    map[i][j].SnakeNext=0;
    switch (direct)//UP = 0 DOWN = 1 LEFT = 2 RIGHT = 3 
    {
    case 0: --j; break;
    case 1: ++j; break;
    case 2: --i; break;
    case 3: ++i; break;
    
    default:
        CheckDead();
    }
    
    snake->SnakeBodyX.push(i);
    snake->SnakeBodyY.push(j);
    map[i][j].SnakeNext=1;
    if(!CheckEaten()){
        snake->SnakeBodyX.pop();
        snake->SnakeBodyY.pop();
    }

    CheckDead();
}

void Map::CreateFood(){

}

bool Map::CheckEaten(){

}

void Map::CheckDead(){

}

void Map::Replay(){

}

int Map::GetScore(){return score;}
