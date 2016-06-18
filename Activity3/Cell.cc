/*
 * Cell.cc
 *
 * Author: Ivan Josa
 */

#include "Cell.h"
#include <cstdlib>

Cell::Cell(){isInMaze = false;this->isValid = true;mazeX=0;mazeY=0;}


Cell::Cell(Point p1,Point p2,Point p3,Point p4)
{
	this->v1 = p1;
	this->v2 = p2;
	this->v3 = p3;
	this->v4 = p4;
	this->isInMaze = false;
	this->isValid = true;
	this->mazeX = 0;
	this->mazeY = 0;
}

Cell::Cell(CellWall p1,CellWall p2,CellWall p3,CellWall p4)
{

	this->bottomWall = p1;
	this->rightWall = p2;
	this->upWall = p3;
	this->leftWall = p4;

	this->v1.x = this->bottomWall.p1.x;
	this->v1.y = this->bottomWall.p1.y;
	this->v2.x = this->rightWall.p1.x;
	this->v2.y = this->rightWall.p1.y;
	this->v3.x = this->upWall.p1.x;
	this->v3.y = this->upWall.p1.y;
	this->v4.x = this->bottomWall.p1.x;
	this->v4.y = this->bottomWall.p1.y;

	this->isInMaze = false;
	this->isValid = true;
	this->mazeX = 0;
	this->mazeY = 0;
}

Cell::Cell(CellWall p1,CellWall p2,CellWall p3,CellWall p4,int xPos,int yPos)
{
	this->bottomWall = p1;

	this->rightWall = p2;

	this->upWall = p3;

	this->leftWall = p4;

	this->v1.x = this->bottomWall.p1.x;
	this->v1.y = this->bottomWall.p1.y;
	this->v2.x = this->rightWall.p1.x;
	this->v2.y = this->rightWall.p1.y;
	this->v3.x = this->upWall.p1.x;
	this->v3.y = this->upWall.p1.y;
	this->v4.x = this->bottomWall.p1.x;
	this->v4.y = this->bottomWall.p1.y;

	this->isInMaze = false;
	this->isValid = true;
	this->mazeX = xPos;
	this->mazeY = yPos;
}

CellWall Cell::getBottomWall()
{
	this->bottomWall.setType("B");
	return this->bottomWall;
}

CellWall Cell::getRightWall()
{
	this->bottomWall.setType("R");
	return this->rightWall;
}

CellWall Cell::getUpWall()
{
	this->bottomWall.setType("U");
	return this->upWall;
}

CellWall Cell::getLeftWall()
{
	this->bottomWall.setType("L");
	return this->leftWall;
}

void  Cell::setBottomWall(CellWall pWall)
{
	this->bottomWall = pWall;
}

void  Cell::setRightWall(CellWall pWall)
{
	this->rightWall = pWall;
}

void  Cell::setUpWall(CellWall pWall)
{
	this->upWall = pWall;
}

void  Cell::setLeftWall(CellWall pWall)
{
	this->leftWall = pWall;
}

int Cell::getMazeX()
{
	return this->mazeX;
}

void Cell::setMaxeX(int pX)
{
	this->mazeX = pX;
}

int Cell::getMazeY()
{
	return this->mazeY;
}

void Cell::setMaxeY(int pY)
{
	this->mazeY = pY;
}

void Cell::setIsValid(bool pBool)
{
	this->isValid = pBool;
}

bool Cell::getIsValid()
{
	return this->isValid;
}

void Cell::setIsInMaze(bool pIsInMaze)
{
	this->isInMaze = pIsInMaze;
}

bool Cell::getIsInMaze()
{
	return this->isInMaze;
}

bool Cell::operator == (const Cell &pCell) const
				{
	return ( this->bottomWall.p1.x == pCell.bottomWall.p1.x && this->bottomWall.p1.z == pCell.bottomWall.p1.z &&
			this->bottomWall.p2.x == pCell.bottomWall.p2.x && this->bottomWall.p2.z == pCell.bottomWall.p2.z &&
			this->upWall.p1.x == pCell.upWall.p1.x && this->upWall.p1.z == pCell.upWall.p1.z &&
			this->upWall.p2.x == pCell.upWall.p2.x && this->upWall.p2.z == pCell.upWall.p2.z);
				}

/**************************************/


/*
 * Marca el mur com a forat
 */
void Cell::removeWall(CellWall wall)
{
	wall.setIsHole(true);
}


/*
 * Marca el mur de la cel·la com a forat
 */
void Cell::destroyWall(CellWall wall/*,vector <Cell> finalMaze*/)
{
	if(this->bottomWall.p1.x == wall.p2.x && this->bottomWall.p1.z == wall.p2.z &&
			this->bottomWall.p2.x == wall.p1.x && this->bottomWall.p2.z == wall.p1.z){
		this->bottomWall.setIsHole(true);

	}else if(this->leftWall.p1.x == wall.p2.x && this->leftWall.p1.z == wall.p2.z &&
			this->leftWall.p2.x == wall.p1.x && this->leftWall.p2.z == wall.p1.z){
		this->leftWall.setIsHole(true);

	}else if(this->rightWall.p1.x == wall.p2.x && this->rightWall.p1.z == wall.p2.z &&
			this->rightWall.p2.x == wall.p1.x && this->rightWall.p2.z == wall.p1.z){
		this->rightWall.setIsHole(true);

	}else if(this->upWall.p1.x == wall.p2.x && this->upWall.p1.z == wall.p2.z &&
			this->upWall.p2.x == wall.p1.x && this->upWall.p2.z == wall.p1.z){
		this->upWall.setIsHole(true);
	}
}

/*
 * Comprova si la cel·la ja es troba al laberint final
 */
bool Cell::checkIsInMaze(Cell pCell,vector<Cell> finalMaze)
{
	bool found = false;
	if(pCell.isValid){
		for(std::vector<Cell>::size_type i = 0; i != finalMaze.size(); i++) {
			Cell cell = finalMaze[i];
			if(cell==pCell){
				found = true;
				break;
			}
		}
	}
	return found;
}

/*
 * Retorna la cel·la veina del mur passat per paràmetre
 */
Cell Cell::getNeightbourCell(CellWall currentWall,Cell maze[MAZE_X][MAZE_Y]){
	Cell neightbourCell;
	bool found = false;

	for(unsigned int x=1;x<=MAZE_X/cell_size;x++){
		for(unsigned int y=1;y<=MAZE_Y/cell_size;y++){
			if(currentWall.getType()=="B" && maze[x][y].getUpWall().isNeightBour(currentWall,wall_width)){
				neightbourCell = maze[x][y];
				found = true;
			}else if(currentWall.getType()=="L" && maze[x][y].getRightWall().isNeightBour(currentWall,wall_width)){
				neightbourCell = maze[x][y];
				found = true;
			}else if(currentWall.getType()=="U" && maze[x][y].getBottomWall().isNeightBour(currentWall,wall_width)){
				neightbourCell = maze[x][y];
				found = true;
			}else if(currentWall.getType()=="R" && maze[x][y].getLeftWall().isNeightBour(currentWall,wall_width)){
				neightbourCell = maze[x][y];
				found = true;
			}
			if(found) break;
		}
		if(found) break;
	}

	neightbourCell.setIsValid(found);
	return neightbourCell;
}

Cell Cell::getNeightbourFinalCell(CellWall currentWall,vector <Cell> finalMaze){
	bool found = false;
	Cell neightbourCell;
	for(std::vector<Cell>::size_type i = 0; i != finalMaze.size(); i++) {
		Cell cell = finalMaze[i];
		if(currentWall.getType()=="B" && cell.getUpWall().isNeightBour(currentWall,wall_width)){
			neightbourCell = cell;
			found = true;
		}else if(currentWall.getType()=="L" &&cell.getRightWall().isNeightBour(currentWall,wall_width)){
			neightbourCell = cell;
			found = true;
		}else if(currentWall.getType()=="U" && cell.getBottomWall().isNeightBour(currentWall,wall_width)){
			neightbourCell = cell;
			found = true;
		}else if(currentWall.getType()=="R" && cell.getLeftWall().isNeightBour(currentWall,wall_width)){
			neightbourCell = cell;
			found = true;
		}
	}

	if(found){
		neightbourCell.setIsValid(found);
	}

	return neightbourCell;
}

Cell Cell::getCellFromFinalMaze(Cell searchCell,vector<Cell> finalMaze){
	Cell finalCell;
	bool found = false;
	if(searchCell.isValid){
		for(std::vector<Cell>::size_type i = 0; i != finalMaze.size(); i++) {
			Cell cell = finalMaze[i];
			if(cell==searchCell){
				finalCell = cell;
				found = true;
				break;
			}
		}
	}

	finalCell.setIsValid(found);

	return finalCell;
}

void  Cell::drawFloor(){

	glPushMatrix();
	glTranslatef(0,0,MAZE_Y+(2*cell_size));
	glRotatef(180,1,0,0);
	glBegin(GL_QUADS);

	//Comprovem de quin color cal pintar per seguir el format de taulell d'escacs
	if(abs(this->getMazeX()%2) == 0){
		if(abs(this->getMazeY()%2)==0){
			glColor3f(0.8,0.8,0.8);
		}else{
			glColor3f(0.9,0.9,0.9);
		}
	}else{
		if(abs(this->getMazeY()%2)==0){
			glColor3f(0.9,0.9,0.9);
		}else{
			glColor3f(0.8,0.8,0.8);
		}
	}

	glVertex3i(this->getBottomWall().p1.x,this->getBottomWall().p1.y,this->getBottomWall().p1.z);
	glVertex3i(this->getBottomWall().p2.x,this->getBottomWall().p2.y,this->getBottomWall().p2.z);
	glVertex3i(this->getUpWall().p1.x,this->getUpWall().p1.y,this->getUpWall().p1.z);
	glVertex3i(this->getUpWall().p2.x,this->getUpWall().p2.y,this->getUpWall().p2.z);

	glEnd();

	glPopMatrix();
}
