/*
 * Cell.h
 *
 * Author: Ivan Josa
 */

#ifndef CELL_H_
#define CELL_H_

#ifdef __APPLE__
# include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>          /* Open GL Util    OpenGL*/
#endif

#include <vector>
#include <list>
#include "Constants.h"
#include "CellWall.h"

using namespace std;


class Cell {
	Point v1;
	Point v2;
	Point v3;
	Point v4;

	bool isValid;

	bool isInMaze;

	int mazeX;
	int mazeY;

	int cellNumber;



//	CellWall bottomWall;
//	CellWall rightWall;
//	CellWall upWall;
//	CellWall leftWall;

public:
	CellWall bottomWall;
	CellWall rightWall;
	CellWall upWall;
	CellWall leftWall;

	list<Cell> connectedCells;

	int BFSStatus;

	Cell();

	Cell(Point p1,Point p2,Point p3,Point p4);

	Cell(CellWall p1,CellWall p2,CellWall p3,CellWall p4);

	Cell(CellWall p1,CellWall p2,CellWall p3,CellWall p4,int xPos,int yPos,int cellNumber);


	int getMazeX();

	void setMaxeX(int pX);

	int getMazeY();

	void setMaxeY(int pY);

	void setIsValid(bool pBool);

	bool getIsValid();

	CellWall getBottomWall();

	CellWall getRightWall();

	CellWall getUpWall();

	CellWall getLeftWall();

	void setBottomWall(CellWall pWall);

	void setRightWall(CellWall pWall);

	void setUpWall(CellWall pWall);

	void setLeftWall(CellWall pWall);

	void setIsInMaze(bool pIsInMaze);

	bool getIsInMaze();

	void setCellNumber(int cellNumber);

	int getCellNumber();


	bool operator == (const Cell &pCell) const;


	/***************Utils**************/

	void removeWall(CellWall wall);

	bool checkIsInMaze(Cell pCell,vector<Cell> finalMaze);

	void destroyWall(CellWall wall/*,vector <Cell> finalMaze*/);

	Cell getCellFromFinalMaze(Cell searchCell,vector<Cell> finalMaze);

	Cell getNeightbourFinalCell(CellWall currentWall,vector<Cell> finalMaze);

	Cell getNeightbourCell(CellWall currentWall,Cell maze[MAZE_X][MAZE_Y]);

	list<Cell> getNeightbourCells(Cell maze[MAZE_X][MAZE_Y]);
	list<Cell> getNeightbourFinalCells(vector<Cell>);

	list<Cell> getAccessibleCells(vector<Cell> finalMaze);

	bool isAccessible(Cell fromCell,vector<Cell> finalMaze,int orientation);

	/***************End Utils**************/

	void drawFloor();

};


#endif /* CELL_H_ */
