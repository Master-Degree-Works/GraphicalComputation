/*
 * Main.cpp
 *
 * Author: Ivan Josa
 */


#include "Constants.h"
#include "Player.h"
#include "Cell.h"

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <cstring>

#include <iostream>

#ifndef	DRAWERUTILS
#include "DrawerUtils.h"
#endif


#define PI 3.1416


/*--- Global variables that determine the viewpoint location ---*/
int anglealpha;
int anglebeta;


Cell maze[MAZE_X][MAZE_Y];
vector< Cell > finalMaze;
Player player;

using namespace std;

void display();
void teclat(unsigned char c,int x,int y);
void idle();

void PosicionarObservador(float alpha,float beta,int radi);

void fillMaze();
void generateMazeWithPrimAlg();
void resetMaze();
bool checkIsFinish(Cell cell);



int main(int argc, char **argv)
{

	anglealpha=90;
	anglebeta=30;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,(glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	glutInitWindowSize((MAZE_X+100)*2,(MAZE_Y+100)*2);
	glutCreateWindow("Ivan Josa <--> Mazemagik");
	glEnable(GL_DEPTH_TEST);


	generateMazeWithPrimAlg();

	player = Player(maze[1][1],cell_size,1,1,finalMaze);
	player.generateTank();

	glutDisplayFunc(display);
	glutKeyboardFunc(teclat);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

void display()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	PosicionarObservador(anglealpha,anglebeta,450);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-((int)MAZE_X),(int)MAZE_X,-((int)MAZE_Y),(int)MAZE_Y,10,2000);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_LINE);

	drawMazeVector(finalMaze);


	drawStart(maze[1][1]);
	drawEnd(maze[MAZE_X/(int)cell_size][MAZE_Y/(int)cell_size]);

	player.drawTank();


	glutSwapBuffers();
}

void teclat(unsigned char key,int x,int y)
{
	if(player.getEstat()==QUIET){

		long t=	glutGet(GLUT_ELAPSED_TIME);

		Cell currentCell = player.getPlayerCurrentCell(finalMaze,maze[player.getCurrentXCell()][player.getCurrentYCell()]);
		Cell dstCell;

		int dstCellX = 0;
		int dstCellY =0;

		switch(key){
		case 'i':
			//Endavant
			if(player.getOrientation()==NORTH){

				dstCellX = player.getCurrentXCell();
				dstCellY =player.getCurrentYCell()-1;

			}else if(player.getOrientation()==SOUTH){

				dstCellX = player.getCurrentXCell();
				dstCellY = player.getCurrentYCell()+1;

			}else if(player.getOrientation()==EAST){

				dstCellX = player.getCurrentXCell()+1;
				dstCellY =player.getCurrentYCell();

			}else if(player.getOrientation()==WEST){

				dstCellX = player.getCurrentXCell()-1;
				dstCellY =player.getCurrentYCell();
			}

			dstCell = player.getPlayerDstCell(finalMaze,maze[dstCellX][dstCellY]);
			player.moveForward(currentCell,dstCell,cell_size,t);
			break;

		case 'k':
			//Enrere
			if(player.getOrientation()==NORTH){

				dstCellX = player.getCurrentXCell();
				dstCellY =player.getCurrentYCell()+1;

			}else if(player.getOrientation()==EAST){

				dstCellX = player.getCurrentXCell()-1;
				dstCellY =player.getCurrentYCell();

			}else if(player.getOrientation()==SOUTH){

				dstCellX = player.getCurrentXCell();
				dstCellY =player.getCurrentYCell()-1;

			}else if(player.getOrientation()==WEST){
				dstCellX = player.getCurrentXCell()+1;
				dstCellY =player.getCurrentYCell();
			}

			dstCell = player.getPlayerDstCell(finalMaze,maze[dstCellX][dstCellY]);
			player.moveBackward(currentCell,dstCell,cell_size,t);

			break;

		case 'j':
			//Gir a Esquerra
			player.turnLeft();
			break;
		case 'l':
			//Gir a Dreta
			player.turnRight();
			break;
		case 'w':
			//Pujar camera
			if(anglebeta<=(90-4)){
				anglebeta=(anglebeta+3);
			}
			break;
		case 's':
			//Baixar camera
			if(anglebeta>=(-90+4)){
				anglebeta=anglebeta-3;
			}
			break;
		case 'a':
			//Girar camera a la dreta
			anglealpha=(anglealpha+3)%360;
			break;
		case 'd':
			//Girar camera a l'esquerra
			anglealpha=(anglealpha-3+360)%360;
			break;
		case 'r': //reset
			resetMaze();
			break;
		case 'q': //quit
			exit (0);
			break;
		default:
			break;
		}

		if(checkIsFinish(maze[player.getCurrentXCell()][player.getCurrentYCell()])){
			resetMaze();
		}
	}
	glutPostRedisplay();
}

void idle()
{
	long t;	t=glutGet(GLUT_ELAPSED_TIME);
	player.integrar(t);
	glutPostRedisplay();
}


void PosicionarObservador(float alpha,float beta,int radi)
{
	float x,y,z;
	float upx,upy,upz;
	float modul;

	x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
	y = (float)radi*sin(beta*2*PI/360.0);
	z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

	if (beta>0)
	{
		upx=-x;
		upz=-z;
		upy=(x*x+z*z)/y;
	}
	else if(beta==0)
	{
		upx=0;
		upy=1;
		upz=0;
	}
	else
	{
		upx=x;
		upz=z;
		upy=-(x*x+y*y)/y;
	}


	modul=sqrt(upx*upx+upy*upy+upz*upz);

	upx=upx/modul;
	upy=upy/modul;
	upz=upz/modul;

	gluLookAt(x,y,z,0.0, 0.0, 0.0,upx,upy,upz);
}

/****************************************************************************************************/

/*
 * Inicialitza el laberint amb totes les cel·les amb 4 murs
 */
void fillMaze()
{
	for(unsigned int x=0;x<=MAZE_X;x+=cell_size)
	{
		for(unsigned int y=0;y<=MAZE_Y;y+=cell_size)
		{

			//Bottom Wall
			Point p11 = Point(x,0,y);
			Point p12 = Point(x+cell_size,0,y);
			CellWall bottomWall = CellWall(p11,p12);
			bottomWall.setType("B");

			//Right Wall
			Point p21 = Point(x+cell_size,0,y);
			Point p22 = Point(x+cell_size,0,y+cell_size);
			CellWall rightWall = CellWall(p21,p22);
			rightWall.setType("R");

			//UpWall
			Point p31 = Point(x+cell_size,0,y+cell_size);
			Point p32 = Point(x,0,y+cell_size);
			CellWall upWall = CellWall(p31,p32);
			upWall.setType("U");

			//LeftWall
			Point p41 = Point(x,0,y+cell_size);
			Point p42 = Point(x,0,y);
			CellWall leftWall = CellWall(p41,p42);
			leftWall.setType("L");

			maze[x/(int)cell_size][y/(int)cell_size] = Cell(bottomWall,rightWall,upWall,leftWall,x/(int)cell_size,y/(int)cell_size);
		}
	}
}

/*
 * Genera un laberint mitjançant l'algorisme de Prim
 */
void generateMazeWithPrimAlg()
{
	srand(time(NULL));
	fillMaze();

	vector < CellWall > walls;

	int x = (rand() % MAZE_X)/cell_size;
	int y = (rand() % MAZE_Y)/cell_size;

	while(x==0){
		x = (rand() % MAZE_X)/cell_size;
	}

	while(y==0){
		y = (rand() % MAZE_Y)/cell_size;
	}

	Cell currentCell = maze[x][y];
	currentCell.setIsInMaze(true);
	finalMaze.push_back(currentCell);

	walls.push_back(currentCell.getBottomWall());
	walls.push_back(currentCell.getRightWall());
	walls.push_back(currentCell.getUpWall());
	walls.push_back(currentCell.getLeftWall());


	while(walls.size()!=0){

		int random = rand() % walls.size();

		CellWall currentWall = walls.at(random);

		Cell oppositeCell = oppositeCell.getNeightbourCell(currentWall,maze);

		if(oppositeCell.checkIsInMaze(oppositeCell,finalMaze)){
			walls.erase(walls.begin()+random);
		}else if(oppositeCell.getIsValid()){

			currentWall.setIsHole(true);
			oppositeCell.setIsInMaze(true);

			oppositeCell.destroyWall(currentWall);

			finalMaze.push_back(oppositeCell);

			walls.erase(walls.begin()+random);

			//Comprovar que no sigui una paret frontera abans d'afegir-ho
			if(oppositeCell.getBottomWall().p1.z >= 0){
				walls.push_back(oppositeCell.getBottomWall());
			}

			if(oppositeCell.getRightWall().p1.x <= (int)MAZE_X){
				walls.push_back(oppositeCell.getRightWall());
			}

			if(oppositeCell.getLeftWall().p1.x >= 0){
				walls.push_back(oppositeCell.getLeftWall());
			}

			if(oppositeCell.getUpWall().p1.z <= (int)MAZE_Y){
				walls.push_back(oppositeCell.getUpWall());
			}
		}else{
			walls.erase(walls.begin()+random);
		}
	}
}


/*
 * Reinicia el laberint
 */
void resetMaze()
{
	fillMaze();
	finalMaze.clear();
	generateMazeWithPrimAlg();
	player = Player(maze[1][1],cell_size,1,1,finalMaze);
	glutPostRedisplay();
}

/*
 * Comprova si s'ha arribat a la cel·la final
 */
bool checkIsFinish(Cell dstCell)
{
	return (dstCell.getMazeX()==MAZE_X/cell_size && dstCell.getMazeY()==MAZE_Y/cell_size)
			||(dstCell.getMazeX()==MAZE_X/cell_size && dstCell.getMazeY()==MAZE_Y/cell_size);
}


