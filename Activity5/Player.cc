/*
 * Player.cc
 *
 * Author: Ivan Josa
 */

#include "Constants.h"
#include <iostream>
#include "Player.h"
#include "Bullet.h"

int minXCoord1 = -((int)MAZE_X);
int minZCoord1 = -(int)MAZE_Y;

int tankId;
int idCos;
int wheelId;

void dibuixarCos();
void dibuixarRodaDreta();
void dibuixarRodaEsquerra();
void dibuixarCano(float playerX,float playerZ,int orientation);


Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->z = z;
	this->currentXCell=0;
	this->currentYCell=0;
	this->estat = QUIET;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->t_darrer = 0;
	this->t_fi = 0;
	this->orientation = NORTH;
	this->right = 0;
	this->left = 0;
	this->turningRight = false;
	this->turningLeft = false;
}


Player::Player(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->currentXCell=0;
	this->currentYCell=0;
	this->estat = QUIET;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->t_darrer = 0;
	this->t_fi = 0;
	this->orientation = NORTH;
	this->right = 0;
	this->left = 0;
	this->turningRight = false;
	this->turningLeft = false;
}

Player::Player(Cell pCell, int cell_size,int xCell,int yCell,vector<Cell> finalMaze)
{
	this->x =pCell.getUpWall().p1.x-cell_size/2;
	this->y =MAZE_Y;
	this->z =pCell.getUpWall().p1.z-cell_size/2;

	this->currentXCell = xCell;
	this->currentYCell = yCell;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->t_darrer = 0;
	this->t_fi = 0;
	this->estat = QUIET;
	this->right = 0;
	this->left = 0;
	this->turningLeft = false;
	this->turningRight = false;

	if(pCell.getCellFromFinalMaze(pCell,finalMaze).getUpWall().getIsHole()){
		this->orientation = SOUTH;
		this->left = 1;
		this->turningLeft = true;
	}else if(pCell.getCellFromFinalMaze(pCell,finalMaze).getRightWall().getIsHole()){
		this->orientation = EAST;
		this->right = 2;
		this->turningRight = true;
	}

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

void Player::setOrientation(int orientation){
	this->orientation = orientation;
}
int Player::getOrientation(){
	return this->orientation;
}

/**************************************/

/*
 * Assigna una posició al jugador
 */
void Player::assignar_posicio(float px, float py,float pz)
{
	this->x = px;
	this->y = py;
	this->z = pz;
}

/*
 * Inicia el moviment del jugador
 */
void Player::iniciar_moviment(float px,float py,float pz,int durada, long t)
{
	this->vx = (px - this->x) / durada;

	this->vy = (py - this->y) / durada;

	this->vz = (pz - this->z) / durada;

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
		this->z = this->z + this->vz * (t - this->t_darrer);
		this->t_darrer = t;
	}
	else if(this->estat==MOVING && t>=this->t_fi)
	{
		this->x = this->x + this->vx * (this->t_fi - this->t_darrer);
		this->y = this->y + this->vy * (this->t_fi - this->t_darrer);
		this->z = this->z + this->vz * (this->t_fi - this->t_darrer);
		this->estat = QUIET;
	}
}


/*
 * Comprova si el moviment amunt és possible i en cas afirmatiu, el realitza
 */
void Player::moveForward(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,FORWARD)){

		this->assignar_posicio(this->x,this->y,this->z);

		switch(this->orientation){
		case NORTH:
			this->iniciar_moviment(this->x,0,this->z+cell_size,movement_duration,t);
			this->currentYCell--;
			break;
		case SOUTH:
			this->iniciar_moviment(this->x,0,this->z-cell_size,movement_duration,t);
			this->currentYCell++;
			break;
		case EAST:
			this->iniciar_moviment(this->x-cell_size,0,this->z,movement_duration,t);
			this->currentXCell++;
			break;

		case WEST:
			this->iniciar_moviment(this->x+cell_size,0,this->z,movement_duration,t);
			this->currentXCell--;
			break;
		default:break;
		}


	}
}


/*
 * Comprova si el moviment avall és possible i en cas afirmatiu, el realitza
 */
void Player::moveBackward(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,BACKWARD)){

		this->assignar_posicio(this->x,this->y,this->z);

		switch(this->orientation){
		case NORTH:
			this->iniciar_moviment(this->x,0,this->z-cell_size,movement_duration,t);
			this->currentYCell++;
			break;
		case SOUTH:
			this->iniciar_moviment(this->x,0,this->z+cell_size,movement_duration,t);
			this->currentYCell--;
			break;
		case EAST:
			this->iniciar_moviment(this->x+cell_size,0,this->z,movement_duration,t);
			this->currentXCell--;
			break;
		case WEST:
			this->iniciar_moviment(this->x-cell_size,0,this->z,movement_duration,t);
			this->currentXCell++;
			break;
		default:break;
		}
	}
}


/*
 * Gira el tanc a la dreta
 */
void Player::turnRight()
{
	this->right++;
	this->turningRight = true;

	switch(this->orientation){
	case NORTH:
		this->orientation = EAST;
		break;
	case EAST:
		this->orientation = SOUTH;
		break;
	case SOUTH:
		this->orientation = WEST;
		break;
	case WEST:
		this->orientation = NORTH;
		break;
	default:break;
	}
}

/*
 * Gira el tanc a l'esquerra
 */
void Player::turnLeft()
{
	this->left++;
	this->turningLeft = true;

	switch(this->orientation){
	case NORTH:
		this->orientation = WEST;
		break;
	case WEST:
		this->orientation = SOUTH;
		break;
	case SOUTH:
		this->orientation = EAST;
		break;
	case EAST:
		this->orientation = NORTH;
		break;
	default:break;
	}
}


/*
 * Comprova si el moviment en la direcció especificada entre les cel·les és permés
 */
bool Player::canMove(Cell srcCell,Cell dstCell,int direction)
{
	if(direction==FORWARD){

		if(this->orientation==NORTH){
			return srcCell.getBottomWall().getIsHole() || dstCell.getUpWall().getIsHole();
		}else if(this->orientation == EAST){
			return srcCell.getRightWall().getIsHole() || dstCell.getLeftWall().getIsHole();
		}else if(this->orientation == SOUTH){
			return srcCell.getUpWall().getIsHole() || dstCell.getBottomWall().getIsHole();
		}else if(this->orientation == WEST){
			return srcCell.getLeftWall().getIsHole() || dstCell.getRightWall().getIsHole();
		}
	}
	else if(direction==BACKWARD){

		if(this->orientation==NORTH){
			return srcCell.getUpWall().getIsHole() || dstCell.getBottomWall().getIsHole();
		}else if(this->orientation == EAST){
			return srcCell.getLeftWall().getIsHole() || dstCell.getRightWall().getIsHole();
		}else if(this->orientation == SOUTH){
			return srcCell.getBottomWall().getIsHole() || dstCell.getUpWall().getIsHole();
		}else if(this->orientation == WEST){
			return srcCell.getRightWall().getIsHole() || dstCell.getLeftWall().getIsHole();
		}
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


void Player::generateTank()
{

	idCos=glGenLists(1);
	glNewList(idCos,GL_COMPILE);

	GLfloat vec[] = {1.0,  1.0,  1.0,  1.0};

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,vec);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);

	//Cos central rectangular
	glNormal3f(0.0f, -1.0f, 1.0f);glVertex3i(25, -25, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);glVertex3i(25, 25, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);glVertex3i(-25, 25, 0);
	glNormal3f(0.0f, 0.0f, -1.0f);glVertex3i(-25, -25, 0);

	glEnd();
	glEndList();


	wheelId=glGenLists(1);
	glNewList(wheelId,GL_COMPILE);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);glTexCoord2f(-1,0.0);glVertex3i(25, -100, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);glTexCoord2f(1,0.0);glVertex3i(25, 100, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);glTexCoord2f(1,1);glVertex3i(-25, 100, 0);
	glNormal3f(0.0f, 0.0f, -1.0f);glTexCoord2f(-1,1);glVertex3i(-25, -100, 0);

	glEnd();
	glEndList();
}

void Player::drawTank(){
	glPushMatrix();

	//Light
	//	GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
	//	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//	GLfloat light_position[] = {this->x, 0.0, this->z, 1.0 };
	//
	//	GLfloat direccio[] = { 1,0, 1, 0 };
	//
	//	glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
	//	glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	//	glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
	//	glLightfv (GL_LIGHT1, GL_POSITION, light_position);
	//
	//
	//	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direccio);
	//	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,128);
	//	//		glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,1);
	//
	//	glEnable(GL_LIGHT1);

	int tx = this->x;
	int tz = this->z;
	glTranslatef(-tx-((int)MAZE_X/2)+(int)cell_size*2,cell_size/10,-tz-((int)MAZE_Y/2)+(int)cell_size*2);

	//Movem el tanc al planol xz
	glRotatef(90,0,0,1);

	int right = this->right;

	while(right!=0){
		//Girar a la dreta
		glRotatef(-90,1,0,0);
		right--;
	}

	if(this->turningRight){
		this->turningRight = false;
	}

	int left = this->left;
	while(left!=0){
		//Girar a la dreta
		glRotatef(90,1,0,0);
		left--;
	}

	if(this->turningLeft){
		this->turningLeft = false;
	}

	glPushMatrix();
	double reductionFactor=MAZE_X/cell_size;
	glScaled(1/reductionFactor,1/reductionFactor,1/reductionFactor);

	dibuixarCos();
	glEnable(GL_TEXTURE_2D);
	glScaled(0.75,0.75,0.75);
	dibuixarRodaDreta();
	dibuixarRodaEsquerra();
	glDisable(GL_TEXTURE_2D);

	dibuixarCano(this->x/reductionFactor,this->z/reductionFactor,this->orientation);

	glPopMatrix();
	glPopMatrix();

}

void dibuixarCos(){


	//Roja
	glPushMatrix();
	glTranslatef(0,0,25);
	glCallList(idCos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,25,0);
	glRotatef(-90,1,0,0);
	glCallList(idCos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-25,0);
	glRotatef(90,1,0,0);
	glCallList(idCos);
	glPopMatrix();

	//Verda
	glPushMatrix();
	glTranslatef(0,0,-25);
	glRotatef(180,0,1,0);
	glCallList(idCos);
	glPopMatrix();

	//Damunt
	glPushMatrix();
	glColor3f(0.5,1.5,0.5);
	glRotatef(90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(idCos);
	glPopMatrix();


	//Davall
	glPushMatrix();
	glColor3f(1,0,0);
	glRotatef(-90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(idCos);
	glPopMatrix();

}

void dibuixarRodaDreta(){

	glPushMatrix();

	glTranslatef(-25,0,50);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,25);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,100,0);
	glRotatef(-90,1,0,0);
	glCallList(idCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,-100,0);
	glRotatef(90,1,0,0);
	glCallList(idCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,-25);
	glRotatef(180,0,1,0);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(-90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();

}

void dibuixarRodaEsquerra(){

	glPushMatrix();
	glTranslatef(-25,0,-50);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,25);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,100,0);
	glRotatef(-90,1,0,0);
	glCallList(idCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,-100,0);
	glRotatef(90,1,0,0);
	glCallList(idCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Verda
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,-25);
	glRotatef(180,0,1,0);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Blava
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(-90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(wheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

}

void dibuixarCano(float playerX,float playerZ,int orientation){

	GLfloat mat_ambient[] = {1.0, 0.0, 0.8, 1.0f};
	GLfloat mat_diffuse[] = {1.0, 0.0, 0.8, 1.0f};
	GLfloat mat_specular[] = {1.0, 0.0, 0.8, 1.0f};

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();
	glRotatef(180, 0, 1,1);
	glTranslatef(0,0,25);

	//Light
	GLfloat vec[] = {1.0, 1.0, 1.0,  1.0};
	GLfloat light_position[] = {playerX-(float)cannonLength, 1.5,  playerZ-(float)cannonLength, 1.0f};
	glLightfv (GL_LIGHT1, GL_SPECULAR, vec);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, vec);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position);

	GLfloat	dir[3] = {0.0,0.0,1.0};
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir);

	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30);
	glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0);
	glEnable(GL_LIGHT1);

	gluCylinder(quadratic,cannonRadius,cannonRadius,cannonLength,1000,1000);
	glPopMatrix();
}

void Player::fire(vector < Cell > generatedMaze,Cell maze[MAZE_X][MAZE_Y]){

	Cell playerCurrentCell = this->getPlayerCurrentCell(generatedMaze,maze[this->currentXCell][this->currentYCell]);
	Bullet bala = Bullet(playerCurrentCell,cell_size,this->currentXCell,this->currentYCell,generatedMaze,this->orientation);

	long t=	glutGet(GLUT_ELAPSED_TIME);

	bala.assignar_posicio(bala.x,1.5,bala.z);
	switch(this->orientation){
	case NORTH:
		bala.iniciar_moviment(bala.x,bala.y,-((int)MAZE_Y*3),bullet_movement_duration,t);
		break;
	case SOUTH:
		bala.iniciar_moviment(bala.x,bala.y,MAZE_Y*3,bullet_movement_duration,t);
		break;
	case EAST:
		bala.iniciar_moviment(MAZE_X*3,bala.y,bala.z,bullet_movement_duration,t);
		break;

	case WEST:
		bala.iniciar_moviment(-((int)MAZE_X*3),bala.y,bala.z,bullet_movement_duration,t);
		break;
	default:break;
	}



	this->bullets.push_back(bala);
}

