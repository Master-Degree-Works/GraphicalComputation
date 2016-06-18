/*
 * CellWall.cc
 *
 * Author: Ivan Josa
 */


#include "CellWall.h"
#include "Constants.h"

CellWall::CellWall()
{
	this->p1 = Point();
	this->p2 = Point();
	this->isHole = false;
	this->isInMaze = false;
	this->type = new char[2];

	this->rightWallId = 0;
	this->leftWallId = 0;
	this->bottomWallId = 0;
	this->upWallId = 0;
}

CellWall::CellWall(Point pp1,Point pp2)
{
	this->p1 = pp1;
	this->p2 = pp2;
	this->isHole = false;
	this->isInMaze = false;
	this->type = new char[2];

	this->rightWallId = 0;
	this->leftWallId = 0;
	this->bottomWallId = 0;
	this->upWallId = 0;
}

void CellWall::setIsHole(bool pIsHole)
{
	this->isHole = pIsHole;
}

bool CellWall::getIsHole()
{
	return this->isHole;
}

void CellWall::setIsInMaze(bool pIsInMaze)
{
	this->isInMaze = pIsInMaze;
}

bool CellWall::getIsInMaze()
{
	return this->isInMaze;
}

string CellWall::getType()
{
	return this->type;
}

void CellWall::setType(string pStr)
{
	this->type = pStr;
}

/**************************************/


/*
 * Comprova si un mur és vei amb el passat per paràmetre
 */
bool CellWall::isNeightBour(CellWall pWall,const unsigned int wall_width)
{
	return (this->p1.x == pWall.p2.x && this->p1.y == pWall.p2.y && this->p1.z == pWall.p2.z &&
			this->p2.x == pWall.p1.x && this->p2.y == pWall.p1.y && this->p2.z == pWall.p1.z);
}



void CellWall::generateBottomWall(){

	//BottomWall
	bottomWallId =glGenLists(1);
	glNewList(bottomWallId,GL_COMPILE);

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y,this->p1.z-wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y,this->p1.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glEnd();

	//Tapa superior
	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glEnd();
	glPopMatrix();

	//Tapes laterals
	glBegin(GL_QUADS);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p2.x-cell_size-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x-cell_size-wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x-cell_size-wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-cell_size-wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glEnd();

	glEndList();
}

void CellWall::generateUpWall(){

	//UPwall
	upWallId =glGenLists(1);
	glNewList(upWallId,GL_COMPILE);

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y,this->p1.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y,this->p1.z+wall_width/2);
	glEnd();


	//Tapa Superior
	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glEnd();
	glPopMatrix();


	//Tapes laterals
	glBegin(GL_QUADS);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p2.x+cell_size+wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x+cell_size+wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x+cell_size+wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+cell_size+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glEnd();



	glEndList();
}

void CellWall::generateLeftWall(){

	//LeftWall
	leftWallId = glGenLists(1);
	glNewList(leftWallId,GL_COMPILE);

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y,this->p1.z+wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y,this->p1.z+wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glEnd();

	//Tapa Superior
	glPushMatrix();

	glBegin(GL_QUADS);

	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z+wall_width/2);
	glEnd();
	glPopMatrix();

	//Tapes laterals
	glBegin(GL_QUADS);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y,this->p1.z+wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y,this->p1.z+wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z+wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z-cell_size-wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y,this->p1.z-cell_size-wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y,this->p1.z-cell_size-wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z-cell_size-wall_width/2);
	glEnd();

	glEndList();
}

void CellWall::generateRightWall(){

	//RightWall
	rightWallId =glGenLists(1);
	glNewList(rightWallId,GL_COMPILE);

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y,this->p1.z-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y,this->p1.z-wall_width/2);
	glEnd();

	//Dibuixem la tapa
	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p1.x+wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glVertex3i(this->p1.x-wall_width/2,this->p1.y+wall_heigth,this->p1.z-wall_width/2);
	glEnd();
	glPopMatrix();

	//Tapes laterals
	glBegin(GL_QUADS);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-wall_width/2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y+wall_heigth,this->p2.z-cell_size-wall_width/2);
	glVertex3i(this->p2.x+wall_width/2,this->p2.y,this->p2.z-cell_size-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y,this->p2.z-cell_size-wall_width/2);
	glVertex3i(this->p2.x-wall_width/2,this->p2.y+wall_heigth,this->p2.z-cell_size-wall_width/2);
	glEnd();

	glEndList();
}

void CellWall::drawWall(){
	glPushMatrix();

	//WALL COLOR
	glColor3f(0,0.5,0);

	if(this->getType()=="R"){
		this->generateRightWall();
		glCallList(rightWallId);
	}
	else if (this->getType()=="L"){
		this->generateLeftWall();
		glCallList(leftWallId);
	}
	else if(this->getType()=="B"){
		this->generateBottomWall();
		glCallList(bottomWallId);
	}
	else if (this->getType()=="U"){
		this->generateUpWall();
		glCallList(upWallId);
	}

	glPopMatrix();

}
