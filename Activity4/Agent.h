/*
 * Player.h
 *
 * Author: Ivan Josa
 */

#ifndef AGENT_H_
#define AGENT_H_

#include "Cell.h"
#include "Player.h"
#include <list>


class Agent {
	float vx,vy,vz;
	int estat;
	long t_darrer;
	long t_fi;

	float x,y,z;
	int currentXCell;
	int currentYCell;

	int orientation;
	int right;
	int left;

	bool turningRight;
	bool turningLeft;


public:

	Cell previousCell;

	Agent();
	Agent(float x,float y,float z);
	Agent(Cell pCell,int cell_size, int xCell,int yCell,vector<Cell> finalMaze);

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

	void turnRight();
	void turnLeft();
	void moveForward(Cell currentCell,Cell dstCell,int cell_size,long t);
	void moveBackward(Cell currentCell,Cell dstCell,int cell_size,long t);

	Cell getAgentCurrentCell(vector < Cell > generatedMaze,Cell pCell);
	Cell getAgentDstCell(vector < Cell > generatedMaze, Cell pCell);
	bool canMove(Cell srcCell,Cell dstCell,int direction);

	void assignar_posicio(float x,float	y,float z);
	void iniciar_moviment(float x,float y,float z,int durada,long t);
	void integrar(long t);

	void generateTank();
	void drawTank();

	void calculateNextMovement(Player player,Cell playerDstCell,long t,vector<Cell> finalMaze,Cell maze[MAZE_X][MAZE_Y]);

	list<Cell> DFS(Cell agentStartCell,Cell playerDstCell,vector<Cell> finalMaze,Cell maze[MAZE_X][MAZE_Y]);

	void calculateMovement(int direction,Cell currentCell,Cell dstCell,long t);
	void breakInconsistence(int orientation,Cell agentCurrentCell,Cell agentDstCell,long t,vector<Cell> finalMaze,Cell maze[MAZE_X][MAZE_Y]);

};

#endif /* AGENT_H_ */
