/*
 * Bullet.h
 *
 *  Created on: May 22, 2015
 *      Author: ivan
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Cell.h"

class Bullet{
		float vx,vy,vz;

		long t_darrer;
		long t_fi;


		int currentXCell;
		int currentYCell;

		int orientation;
		int right;
		int left;

	public:
		float x,y,z;
		int estat;
		int cannonOrientation;

		Bullet();
		Bullet(float x,float y,float z);
		Bullet(Cell pCell,int cell_size, int xCell,int yCell,vector<Cell> finalMaze,int cannonOrientation);


		void assignar_posicio(float x,float	y,float z);
		void iniciar_moviment(float x,float y,float z,int durada,long t);
		void integrar(long t);

		void dibuixar();

		bool checkTarget(Cell enemyCell);
};



#endif /* BULLET_H_ */
