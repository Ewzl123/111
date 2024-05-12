#include "string"
#include<iostream>
#include<queue>
#include<cstdio>
//还有需要加的头文件

#define SIZE 100 ///<场景大小

enum Direction{UP,DOWN,LEFT,RIGHT};///<按键和方向的转换
/*UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3 */


enum Level{es,nm,hd,at};///<Level决定蛇的移动速度
/*es = 0
  nm = 1
  hd = 2
  at = 3 */



enum Thing{Empty,Barrier,Snake,Food};///<地图各点是什么
/*Empty=0
Barrier=1
Snake=2
Food=3 */

/*!
 * @brief 地图每个点
 * @param state 点对应的物品
 * @param SnakeNext 是否是蛇下一步走的位置，便于判定
 */

typedef struct {
	Thing state;
	bool SnakeNext;
} MapDot;


/*!
 * @brief 蛇
 * @param snakebody 蛇的每一个位置用二维队列存储，对应每个点的横纵坐标
 * @param SnakeDirection 蛇下一步方向
 * @param SnakeLenth 蛇的长度，用于计分
 */

typedef struct{
		std::queue<int> SnakeBodyX;
		std::queue<int> SnakeBodyY;
		Direction SnakeDirection;
		int SnakeLenth;
} Snake;

/*!
 * @brief 地图
 * @param map 地图上的所有点
 * @param snake 蛇，（后续可以增加一条蛇，双人模式）
 * @param score 计算吃food所得分数
 */

class Map {
	private:
		MapDot** map;
		Snake* snake;
		int score;

	public:
		Map();
		~Map();

		void InitMap();
		void InitSnake();
		void Move(int );
		void CreateFood();
		bool CheckEaten();
		void CheckDead();
		void Replay();
		int  GetScore();

};



