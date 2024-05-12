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

void Map::InitMap(){///<地图整体的初始化
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
    int food_x=0,food_y=0;
    	srand(time(0));
			do {
				food_x=rand()%(N-2)+1;
				food_y=rand()%(N-2)+1;
			  }while(map(food_x,food_y).state!=0);
			map(food_x,food_y).state=3;
}

bool Map::CheckEaten(){///<判断这一步是否吃到食物
      if(map(Snake->SnakeBodyXback(),Snake->SnakeBodyY.back()).state==3){
    	score+=10;	//每次得分可根据难度进行修改
        ++snake->SnakeLenth;
    	void CreateFood();
    	return true;
	}else return false;
}

void Map::CheckDead(){///<判断这一步是否撞墙或撞到自身
     int snakeheadx,snakeheady;//蛇头位置 
	snakeheadx=Snake->SnakeBodyX.back();
	snakeheady=Snake->SnakeBodyY.back();
    if(snakeheadx==0||snakeheadx==N-1||snakeheady==0||snakeheady==N-1){//判断是否撞墙 
       return true;
	  }else{//判断是否碰到自身， 更优化的算法？ 
		std::queue<int> SnakeBodyX1;
		std::queue<int> SnakeBodyY1;
		int snakebodyx,snakebodyy,i;
	    for(i=0;i<Snake.SnakeLenth-1;++i){
         snakebodyx=SnakeBodyX.pop();
		 snakebodyy=SnakeBodyY.pop();
		 SnakeBodyX1.push(snakebodyx);
		 SnakeBodyY1.push(snakebodyy);
		 if(snakeheadx==snakebodyx&&snakeheady==snakebodyy){
		 	break;
		 };
       };
       if(i<Snake.SnakeLenth-1){
            return true;//碰到自身，游戏结束 
       }else{
       	for(i;i<Snake.SnakeLenth-1;++i){//没有碰到，蛇身s剩余元素继续出队
         snakebodyx=SnakeBodyX.pop();
		 snakebodyy=SnakeBodyY.pop();
		 SnakeBodyX1.push(snakebodyx);
		 SnakeBodyY1.push(snakebodyy);
	   };
       	for(i;i>-1;--i){//蛇身元素重新入队，游戏继续 
       	    snakebodyx=SnakeBodyX1.pop();
		    snakebodyy=SnakeBodyY1.pop();
		    SnakeBodyX.push(snakebodyx);
		    SnakeBodyY.push(snakebodyy);	
		};
		return false;
	   };
	 };
}

void Map::Replay(){///<重新开始游戏
     InitMap();
}

int Map::GetScore(){return score;}
