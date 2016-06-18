/*
 * Player.cc
 *
 * Author: Ivan Josa
 */

#include "Constants.h"

#include "Player.h"


Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->currentXCell=0;
	this->currentYCell=0;
	this->estat = QUIET;
	this->vx = 0;
	this->vy = 0;
	this->t_darrer = 0;
	this->t_fi = 0;
}


Player::Player(float x,float y)
{
	this->x = x;
	this->y = y;
	this->currentXCell=0;
	this->currentYCell=0;
	this->estat = QUIET;
	this->vx = 0;
	this->vy = 0;
	this->t_darrer = 0;
	this->t_fi = 0;
}

Player::Player(Cell pCell, int cell_size,int xCell,int yCell)
{
	this->x = pCell.getBottomWall().p1.x + cell_size/2;
	this->y = pCell.getUpWall().p1.y - cell_size/2;
	this->currentXCell = xCell;
	this->currentYCell = yCell;
	this->vx = 0;
	this->vy = 0;
	this->t_darrer = 0;
	this->t_fi = 0;
	this->estat = QUIET;
}

void Player::setVX(float vx)
{
	this->vx = vx;
}

float Player::getVX()
{
	return this->vx;
}

void Player::setVY(float vy)
{
	this->vy = vy;
}

float Player::getVY()
{
	return this->vy;
}

void Player::setEstat(int estat)
{
	this->estat = estat;
}

int Player::getEstat()
{
	return this->estat;
}

void Player::setX(float x)
{
	this->x = x;
}

float Player::getX()
{
	return this->x;
}

void Player::setY(float y)
{
	this->y = y;
}

float Player::getY()
{
	return this->y;
}

void Player::setCurrentXCell(int currentXCell)
{
	this->currentXCell = currentXCell;
}

int Player::getCurrentXCell()
{
	return this->currentXCell;
}

void Player::setCurrentYCell(int currentYCell)
{
	this->currentYCell = currentYCell;
}

int Player::getCurrentYCell(){
	return this->currentYCell;
}

void Player::setLastTime(long t_darrer)
{
	this->t_darrer = t_darrer;
}

long Player::getLastTime()
{
	return this->t_darrer;
}

void Player::setEndTime(long t_fi)
{
	this->t_fi = t_fi;
}

long Player::getEndTime()
{
	return this->t_fi;
}

/**************************************/

/*
 * Assigna una posició al jugador
 */
void Player::assignar_posicio(float px, float py)
{
	this->x = px;
	this->y = py;
}

/*
 * Inicia el moviment del jugador
 */
void Player::iniciar_moviment(float px,float py,int durada, long t)
{
	this->vx = (px - this->x) / durada;

	this->vy = (py - this->y) / durada;

	this->estat = MOVING;
	this->t_darrer = t;
	this->t_fi = this->t_darrer + durada;
}


/*
 * Actualitza la posició del jugador en funció de la seva velocitat
 */
void Player::integrar(long t)
{
	if(this->estat == MOVING && t < this->t_fi)
	{
		this->x = this->x + this->vx * (t - this->t_darrer);
		this->y = this->y + this->vy * (t - this->t_darrer);
		this->t_darrer = t;
	}
	else if(this->estat==MOVING && t>=this->t_fi)
	{
		this->x = this->x + this->vx * (this->t_fi - this->t_darrer);
		this->y = this->y + this->vy * (this->t_fi - this->t_darrer);
		this->estat = QUIET;
	}
}


/*
 * Comprova si el moviment amunt és possible i en cas afirmatiu, el realitza
 */
void Player::moveUp(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,1)){

		this->assignar_posicio(this->x,this->y);
		this->iniciar_moviment(this->x,this->y + cell_size,movement_duration,t);
		this->currentYCell++;
	}
}


/*
 * Comprova si el moviment avall és possible i en cas afirmatiu, el realitza
 */
void Player::moveDown(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,2)){

		this->assignar_posicio(this->x,this->y);
		this->iniciar_moviment(this->x,this->y - cell_size,movement_duration,t);
		this->currentYCell--;
	}
}


/*
 * Comprova si el moviment a la dreta és possible i en cas afirmatiu, el realitza
 */
void Player::moveRight(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,3)){

		this->assignar_posicio(this->x,this->y);
		this->iniciar_moviment(this->x + cell_size,this->y,movement_duration,t);
		this->currentXCell++;
	}
}

/*
 * Comprova si el moviment a l'esquerra és possible i en cas afirmatiu, el realitza
 */
void Player::moveLeft(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,4)){

		this->assignar_posicio(this->x,this->y);
		this->iniciar_moviment(this->x - cell_size,this->y,movement_duration,t);
		this->currentXCell--;
	}
}

/*
 * Dibuixa el jugador
 */
void Player::draw()
{
	glColor3f(1,1,0);
	glBegin(GL_QUADS);

	int v1x = this->x - (cell_size/player_reduction);
	int v1y = this->y - (cell_size/player_reduction);

	int v2x = this->x + (cell_size/player_reduction);
	int v2y = this->y - (cell_size/player_reduction);

	int v3x = this->x + (cell_size/player_reduction);
	int v3y = this->y + (cell_size/player_reduction);

	int v4x = this->x - (cell_size/player_reduction);
	int v4y = this->y + (cell_size/player_reduction);

	glPushMatrix();
	glScalef(2.0,2.0,0);
	glVertex2i(v1x,v1y);
	glVertex2i(v2x,v2y);
	glVertex2i(v3x,v3y);
	glVertex2i(v4x,v4y);

	glPopMatrix();
	glEnd();
}

/*
 * Comprova si el moviment en la direcció especificada entre les cel·les és permés
 */
bool Player::canMove(Cell srcCell,Cell dstCell,int direction)
{
	if(direction==UP){
		return srcCell.getUpWall().getIsHole() || dstCell.getBottomWall().getIsHole();
	}else if(direction==DOWN){
		return srcCell.getBottomWall().getIsHole() || dstCell.getUpWall().getIsHole();
	}else if(direction==RIGHT){
		return srcCell.getRightWall().getIsHole() || dstCell.getLeftWall().getIsHole();
	}else if(direction==LEFT){
		return srcCell.getLeftWall().getIsHole() || dstCell.getRightWall().getIsHole();
	}

	return true;
}

/*
 * Retorna la cel·la actual del jugador
 */
Cell Player::getPlayerCurrentCell(vector < Cell > generatedMaze, Cell pCell)
{
	Cell currentCell;

	for (size_t i = 0; i != generatedMaze.size(); ++i){
		if(generatedMaze[i] == pCell){
			currentCell = generatedMaze[i];
		}
	}
	return currentCell;
}

/*
 * Retorna la cel·la a la qual es mourà el jugador si el moviment és permés
 */
Cell Player::getPlayerDstCell(vector < Cell > generatedMaze, Cell pCell)
{
	Cell currentCell;

	for (size_t i = 0; i != generatedMaze.size(); ++i){
		if(generatedMaze[i] == pCell){
			currentCell = generatedMaze[i];
		}
	}
	return currentCell;
}
