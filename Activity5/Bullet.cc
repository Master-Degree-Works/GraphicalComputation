/*
 * Bullet.cc
 *
 *  Created on: May 22, 2015
 *      Author: ivan
 */


#include "Bullet.h"


Bullet::Bullet()
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
}


Bullet::Bullet(float x,float y,float z)
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
}

Bullet::Bullet(Cell pCell, int cell_size,int xCell,int yCell,vector<Cell> finalMaze,int cannonOrientation)
{
	this->x =pCell.getUpWall().p1.x-cell_size/2;
	this->y =pCell.getUpWall().p1.y-cell_size/2;
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

	this->cannonOrientation = cannonOrientation;

}

/**************************************/

/*
 * Assigna una posició a la bala
 */
void Bullet::assignar_posicio(float px, float py,float pz)
{
	this->x = px;
	this->y = py;
	this->z = pz;
}

/*
 * Inicia el moviment de la bala
 */
void Bullet::iniciar_moviment(float px,float py,float pz,int durada, long t)
{
	this->vx = (px - this->x) / durada;

	this->vy = (py - this->y) / durada;

	this->vz = (pz - this->z) / durada;

	this->estat = MOVING;
	this->t_darrer = t;
	this->t_fi = this->t_darrer + durada;
}


/*
 * Actualitza la posició de la bala en funció de la seva velocitat
 */
void Bullet::integrar(long t)
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



void Bullet::dibuixar(){

	GLfloat vec[] = {0.5,  0.5,  0.5,  1.0};

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,vec);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);


	glPushMatrix();
	glTranslatef(-((int)MAZE_X)+(int)cell_size*2,2.5,-((int)MAZE_Y)+(int)cell_size*2);

	glTranslatef(this->x,this->y, this->z);
	glutSolidSphere(1.5,50,50);

	glPopMatrix();
}

bool Bullet::checkTarget(Cell enemyCurrentCell){

	int cellLeftX = enemyCurrentCell.getLeftWall().p1.x;
	int cellRightX = enemyCurrentCell.getRightWall().p1.x;

	int cellBottomZ = enemyCurrentCell.getBottomWall().p1.z;
	int cellUpZ = enemyCurrentCell.getUpWall().p1.z;

	int bulletX = this->x;
	int bulletZ = this->z;

	if(bulletX>cellLeftX && bulletX<cellRightX && bulletZ>cellBottomZ && bulletZ<cellUpZ){
		return true;
	}else{
		return false;
	}

}
