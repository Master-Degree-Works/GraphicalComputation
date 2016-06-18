/*
 * Player.h
 *
 * Author: Ivan Josa
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Bullet.h"
#include "Cell.h"
#include <vector>

class Player{
	float vx,vy,vz;
	int estat;
	long t_darrer;
	long t_fi;


	int currentXCell;
	int currentYCell;

	int orientation;
	int right;
	int left;

	bool turningRight;
	bool turningLeft;



public:
	float x,y,z;
	vector <Bullet> bullets;

	Player();
	Player(float x,float y,float z);
	Player(Cell pCell,int cell_size, int xCell,int yCell,vector<Cell> finalMaze);

	void setVX(float vx);
	float getVX();

	void setVY(float vy);
	float getVY();

	void setEstat(int estat);
	int getEstat();

	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setCurrentXCell(int currentXCell);
	int getCurrentXCell();

	void setCurrentYCell(int currentYCell);
	int getCurrentYCell();

	void setLastTime(long t_darrer);
	long getLastTime();

	void setEndTime(long t_fi);
	long getEndTime();

	void setOrientation(int orientation);
	int getOrientation();

	/**************************************/
	void fire(vector < Cell > generatedMaze,Cell maze[MAZE_X][MAZE_Y]);

	void turnRight();
	void turnLeft();
	void moveForward(Cell currentCell,Cell dstCell,int cell_size,long t);
	void moveBackward(Cell currentCell,Cell dstCell,int cell_size,long t);

	Cell getPlayerCurrentCell(vector < Cell > generatedMaze,Cell pCell);
	Cell getPlayerDstCell(vector < Cell > generatedMaze, Cell pCell);
	bool canMove(Cell srcCell,Cell dstCell,int direction);

	void assignar_posicio(float x,float	y,float z);
	void iniciar_moviment(float x,float y,float z,int durada,long t);
	void integrar(long t);

	void generateTank();
	void drawTank();


};

#endif /* PLAYER_H_ */
