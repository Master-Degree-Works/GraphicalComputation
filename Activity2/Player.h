/*
 * Player.h
 *
 * Author: Ivan Josa
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Cell.h"

class Player{
	float vx,vy;
	int estat;
	long t_darrer;
	long t_fi;

	float x,y;
	int currentXCell;
	int currentYCell;

public:

	Player();
	Player(float x,float y);
	Player(Cell pCell,int cell_size, int xCell,int yCell);

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


	/**************************************/

	void moveRight(Cell currentCell,Cell dstCell,int cell_size,long t);
	void moveLeft(Cell currentCell,Cell dstCell,int cell_size,long t);
	void moveUp(Cell currentCell,Cell dstCell,int cell_size,long t);
	void moveDown(Cell currentCell,Cell dstCell,int cell_size,long t);

	Cell getPlayerCurrentCell(vector < Cell > generatedMaze,Cell pCell);
	Cell getPlayerDstCell(vector < Cell > generatedMaze, Cell pCell);
	bool canMove(Cell srcCell,Cell dstCell,int direction);

	void draw();

	void assignar_posicio(float x,float	y);
	void iniciar_moviment(float x,float y,int durada,long t);
	void integrar(long t);

};

#endif /* PLAYER_H_ */
