/*
 * DrawerUtils.h
 *
 * Author: Ivan Josa
 */


#ifndef DRAWERUTILS_H_
#define DRAWERUTILS_H_

#include "Constants.h"

void drawStart(Cell startCell)
{
	glColor3f(166,166,166);
	glBegin(GL_QUADS);

	int cellOffset = 0;
	int sizeReduction = cell_size/4;

	int v1x = startCell.getLeftWall().p1.x+cellOffset;
	int v1y = startCell.getLeftWall().p1.y+cellOffset;

	int v2x = startCell.getLeftWall().p2.x+cellOffset;
	int v2y = startCell.getLeftWall().p2.y+cellOffset;

	int v3x = startCell.getRightWall().p1.x+cellOffset;
	int v3y = startCell.getRightWall().p1.y+cellOffset;

	int v4x = startCell.getRightWall().p2.x+cellOffset;
	int v4y = startCell.getRightWall().p2.y+cellOffset;


	glVertex2i(v1x+sizeReduction,v1y-sizeReduction);
	glVertex2i(v2x+sizeReduction,v2y+sizeReduction);
	glVertex2i(v3x-sizeReduction,v3y+sizeReduction);
	glVertex2i(v4x-sizeReduction,v4y-sizeReduction);

	glEnd();
}

void drawEnd(Cell endCell)
{
	glColor3f(0,1,0);
	glBegin(GL_QUADS);

	int cellOffset = 0;
	int sizeReduction = cell_size/4;

	int v1x = endCell.getLeftWall().p1.x+cellOffset;
	int v1y = endCell.getLeftWall().p1.y+cellOffset;

	int v2x = endCell.getLeftWall().p2.x+cellOffset;
	int v2y = endCell.getLeftWall().p2.y+cellOffset;

	int v3x = endCell.getRightWall().p1.x+cellOffset;
	int v3y = endCell.getRightWall().p1.y+cellOffset;

	int v4x = endCell.getRightWall().p2.x+cellOffset;
	int v4y = endCell.getRightWall().p2.y+cellOffset;

	glVertex2i(v1x+sizeReduction,v1y-sizeReduction);
	glVertex2i(v2x+sizeReduction,v2y+sizeReduction);
	glVertex2i(v3x-sizeReduction,v3y+sizeReduction);
	glVertex2i(v4x-sizeReduction,v4y-sizeReduction);

	glEnd();
}

void drawHole(int x0,int x1, int y0,int y1)
{
	glBegin(GL_LINES);

	glLineWidth(2.5);
	glColor4ub(0,0,0,0);
	glVertex2i(x0,y0);
	glVertex2i(x1,y1);

	glEnd();
}

void drawLine(int x0,int x1, int y0,int y1)
{
	glBegin(GL_LINES);

	glLineWidth(2.5);
	glColor4ub(255,0,0,0);
	glVertex2i(x0,y0);
	glVertex2i(x1,y1);

	glEnd();
}

void drawCell(Cell cell)
{
	if(!cell.getBottomWall().getIsHole()){
		drawLine(cell.getBottomWall().p1.x,cell.getBottomWall().p2.x,cell.getBottomWall().p1.y,cell.getBottomWall().p2.y);
	}else{
		drawHole(cell.getBottomWall().p1.x,cell.getBottomWall().p2.x,cell.getBottomWall().p1.y,cell.getBottomWall().p2.y);
	}

	if(!cell.getRightWall().getIsHole()){
		drawLine(cell.getRightWall().p1.x,cell.getRightWall().p2.x,cell.getRightWall().p1.y,cell.getRightWall().p2.y);
	}else{
		drawHole(cell.getRightWall().p1.x,cell.getRightWall().p2.x,cell.getRightWall().p1.y,cell.getRightWall().p2.y);
	}

	if(!cell.getUpWall().getIsHole()){
		drawLine(cell.getUpWall().p1.x,cell.getUpWall().p2.x,cell.getUpWall().p1.y,cell.getUpWall().p2.y);
	}else{
		drawHole(cell.getUpWall().p1.x,cell.getUpWall().p2.x,cell.getUpWall().p1.y,cell.getUpWall().p2.y);
	}

	if(!cell.getLeftWall().getIsHole()){
		drawLine(cell.getLeftWall().p1.x,cell.getLeftWall().p2.x,cell.getLeftWall().p1.y,cell.getLeftWall().p2.y);
	}else{
		drawHole(cell.getLeftWall().p1.x,cell.getLeftWall().p2.x,cell.getLeftWall().p1.y,cell.getLeftWall().p2.y);
	}
}

void drawMazeVector(vector<Cell> finalMaze)
{
	for(std::vector<Cell>::size_type i = 0; i != finalMaze.size(); i++) {
		Cell cell = finalMaze[i];
		drawCell(cell);
	}
}


#endif /* DRAWERUTILS_H_ */
