/*
 * DrawerUtils.h
 *
 * Author: Ivan Josa
 */


#ifndef DRAWERUTILS_H_
#define DRAWERUTILS_H_


#ifdef __APPLE__
# include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>          /* Open GL Util    OpenGL*/
#endif

#include "Constants.h"


void drawSquare(){
	//glBindTexture(GL_TEXTURE_2D,0);
	glBegin(GL_QUADS);
	glColor3f(0.7,0.7,0.7);
	glTexCoord2f(-4.0,0.0); glVertex3i(-200,0,0);
	glTexCoord2f(4.0,0.0); glVertex3i(200,0,0);
	glTexCoord2f(4.0,4.0); glVertex3i(200,200,0);
	glTexCoord2f(-4.0,4.0); glVertex3i(-200,200,0);
	glEnd();
}

void drawStart(Cell startCell)
{


	glPushMatrix();
	int tx = ((int)MAZE_X/2)+cell_size;
	int tz = ((int)MAZE_Y/2)+cell_size;

	GLfloat mat_ambient[] = {0.05, 0.05, 0.05, 1.0f};
	GLfloat mat_diffuse[] = {0.8, 0.0, 0.0, 1.0f};
	GLfloat mat_specular[] = {0.9, 0.8, 0.8, 1.0f};

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);

	glTranslatef(-tx,1.0,-tz);

	glBegin(GL_QUADS);

	float v1x = startCell.getBottomWall().p2.x - (cell_size*startEndCellReduction);
	float v1z = startCell.getBottomWall().p2.z + (cell_size*startEndCellReduction);

	float v2x = startCell.getBottomWall().p1.x + (cell_size*startEndCellReduction);
	float v2z = startCell.getBottomWall().p1.z + (cell_size*startEndCellReduction);


	float v3x = startCell.getUpWall().p2.x + (cell_size*startEndCellReduction);
	float v3z = startCell.getUpWall().p2.z - (cell_size*startEndCellReduction);

	float v4x = startCell.getUpWall().p1.x - (cell_size*startEndCellReduction);
	float v4z = startCell.getUpWall().p1.z - (cell_size*startEndCellReduction);

	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v1x,0,v1z);
	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v2x,0,v2z);
	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v3x,0,v3z);
	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v4x,0,v4z);

	glEnd();
	glPopMatrix();
}

void drawEnd(Cell endCell)
{

	glPushMatrix();
	int tx = ((int)MAZE_X/2)+cell_size;
	int tz = ((int)MAZE_Y/2)+cell_size;

	glTranslatef(-tx,1.0,-tz);

	GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0f};
	GLfloat mat_diffuse[] = {0.0, 0.7, 0.0, 1.0f};
	GLfloat mat_specular[] = {0.8, 0.8, 0.8, 1.0f};

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);

	glBegin(GL_QUADS);

	float v1x = endCell.getBottomWall().p2.x - (cell_size*startEndCellReduction);
	float v1z = endCell.getBottomWall().p2.z + (cell_size*startEndCellReduction);

	float v2x = endCell.getBottomWall().p1.x + (cell_size*startEndCellReduction);
	float v2z = endCell.getBottomWall().p1.z + (cell_size*startEndCellReduction);

	float v3x = endCell.getUpWall().p2.x + (cell_size*startEndCellReduction);
	float v3z = endCell.getUpWall().p2.z - (cell_size*startEndCellReduction);

	float v4x = endCell.getUpWall().p1.x - (cell_size*startEndCellReduction);
	float v4z = endCell.getUpWall().p1.z - (cell_size*startEndCellReduction);

	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v1x,0,v1z);
	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v2x,0,v2z);
	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v3x,0,v3z);
	glNormal3f(0.0f, 1.0f, 0.0f);glVertex3f(v4x,0,v4z);

	glEnd();
	glPopMatrix();
}


void drawCell(Cell cell,vector<Cell> finalMaze)
{

	glPushMatrix();
	glColor3f(0.5,1.0,0.5);

	//Translladem al centre del planol
	glTranslatef(-((int)MAZE_X/2)-(int)cell_size,0,-((int)MAZE_Y/2)-(int)cell_size);

	Cell neightbourghCell;

	//Abans de pintar cap paret, comprovar si la veina també es forat i si ho és, no fer res
	if(!cell.getBottomWall().getIsHole()){

		neightbourghCell =  cell.getNeightbourFinalCell(cell.getBottomWall(),finalMaze);

		if(!neightbourghCell.getUpWall().getIsHole()){
			cell.getBottomWall().drawWall();
		}
	}

	if(!cell.getUpWall().getIsHole()){

		neightbourghCell =  cell.getNeightbourFinalCell(cell.getUpWall(),finalMaze);

		if(!neightbourghCell.getBottomWall().getIsHole()){
			cell.getUpWall().drawWall();
		}
	}


	if(!cell.getRightWall().getIsHole()){

		neightbourghCell =  cell.getNeightbourFinalCell(cell.getRightWall(),finalMaze);

		if(!neightbourghCell.getLeftWall().getIsHole()){
			cell.getRightWall().drawWall();
		}
	}

	if(!cell.getLeftWall().getIsHole()){

		neightbourghCell =  cell.getNeightbourFinalCell(cell.getLeftWall(),finalMaze);

		if(!neightbourghCell.getRightWall().getIsHole()){
			cell.getLeftWall().drawWall();
		}
	}

	cell.drawFloor();

	glPopMatrix();
}

void drawMazeVector(vector<Cell> finalMaze)
{
	for(std::vector<Cell>::size_type i = 0; i != finalMaze.size(); i++) {
		Cell cell = finalMaze[i];
		drawCell(cell,finalMaze);
	}
}



#endif /* DRAWERUTILS_H_ */
