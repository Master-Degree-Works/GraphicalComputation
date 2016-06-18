/*
 * CellWall.cc
 *
 * Author: Ivan Josa
 */


#include "CellWall.h"

CellWall::CellWall()
{
	this->p1 = Point();
	this->p2 = Point();
	this->isHole = false;
	this->isInMaze = false;
	this->type = new char[2];
}

CellWall::CellWall(Point pp1,Point pp2)
{
	this->p1 = pp1;
	this->p2 = pp2;
	this->isHole = false;
	this->isInMaze = false;
	this->type = new char[2];
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
	return (this->p1.x == pWall.p2.x && this->p1.y == pWall.p2.y &&
			this->p2.x == pWall.p1.x && this->p2.y == pWall.p1.y);
}


