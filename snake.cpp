#include<snake.h>

Map::Map(){
    map = new MapDot*[SIZE];
    for(int i = 0;i<SIZE;++i){
        map[i] = new MapDot[SIZE];
    }
    snake = new Snake ;

    InitMap(x);
    
}

Map::~Map(){
    for(int i = 0;i<SIZE;++i){
        delete map[SIZE-i];
    }
    delete map;
    delete snake;
}

void Map::InitMap(int x){///<地图整体的初始化
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
    InitBarrier(x);
    CreateFood();

}

void Map::InitBarrier(int x){
    int i=0,j=0;
    switch (x)
    {
    case 1://四周都是围墙
        for(i= 0; i<SIZE;++i){
            map[i][0].state=Barrier;
            map[i][SIZE-1].state=Barrier;
        }
        for(j=0; j<SIZE;++j){
            map[0][j].state=Barrier;
            map[SIZE-1][j].state=Barrier;
        }
        break;
    
    case 2:
        for(i= 0; i<SIZE;++i){
            map[i][0].state=Barrier;
            map[i][SIZE-1].state=Barrier;
        }
        for(j=0; j<SIZE;++j){
            map[0][j].state=Barrier;
            map[SIZE-1][j].state=Barrier;
        }
        map[SIZE/4][SIZE/4].state=Barrier;
        map[3*SIZE/4][SIZE/4].state=Barrier;
        map[SIZE/4][3*SIZE/4].state=Barrier;
        map[3*SIZE/4][3*SIZE/4].state=Barrier;
        break;
    
    default://默认是没有边界
        break;
    }
}

void Map::InitSnake(){///<蛇的初始化
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
    snake->SnakeLive=1;
}

void Map::Move(int direct){///<蛇移动一步，判断存活和吃食物
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

    if(i<0)i=SIZE-1;
    if(i>=SIZE)i=0;
    if(j<0)j=SIZE-1;
    if(j>=SIZE)j=0;

    snake->SnakeBodyX.push(i);
    snake->SnakeBodyY.push(j);
    map[i][j].SnakeNext=1;
    if(!CheckEaten()){
        snake->SnakeBodyX.pop();
        snake->SnakeBodyY.pop();
    }

    CheckDead();
}

void Map::CreateFood(){///<每吃一次食物后，地图随机生成一个新食物
    int foodx=0,foody=0;
    	srand(time(0));
			do {
				foodx=rand()%(SIZE-2)+1;
				foody=rand()%(SIZE-2)+1;
			  }while(map[foodx][foody].state!=0);
			map[foodx][foody].state=(Thing)3;
        food.Foodx=foodx;
        food.Foody=foody;

}

bool Map::CheckEaten(){///<判断这一步是否吃到食物
    if(map[snake->SnakeBodyX.back()][snake->SnakeBodyY.back()].state==3){
    	score+=10;	//每次得分可根据难度进行修改
        ++snake->SnakeLenth;
    	void CreateFood();
    	return true;
	}else return false;
}

void Map::CheckDead(){///<判断这一步是否撞墙或撞到自身
    if(map[snake->SnakeBodyX.back()][snake->SnakeBodyY.back()].state==1||map[snake->SnakeBodyX.back()][snake->SnakeBodyY.back()].state==2)
       --snake->SnakeLive;
}

bool Map::CheckLive(){///<监测蛇生命值，小于等于0时结束游戏
	if(snake->SnakeLive<=0)return false;
		else return true;
}

void Map::Restart(){///<重新开始游戏
    InitMap(x);
}

void Map::End(){

}

int Map::GetScore(){return score;}

int Map::GetFoodx(){return food.Foodx;}

int Map::GetFoody(){return food.Foody;}
