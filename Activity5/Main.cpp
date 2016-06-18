/*
 * Main.cpp
 *
 * Author: Ivan Josa
 */


#include "Constants.h"
#include "Player.h"
#include "Agent.h"
#include "Cell.h"
#include "TextureUtils.h"
#include "Bullet.h"

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
Agent enemy1;


using namespace std;

void display();
void teclat(unsigned char c,int x,int y);
void idle();

void PosicionarObservador(float alpha,float beta,int radi);

void fillMaze();
void generateMazeWithPrimAlg();
void resetMaze();
bool checkIsFinish(Cell cell);

void redrawMaze();
bool checkImpact(Player player,Agent enemy);

void doMazeLoops(vector<Cell> finalMaze);

void dibuixaEsfera();

int main(int argc, char **argv)
{

	anglealpha=90;
	anglebeta=30;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,(glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	glutInitWindowSize((MAZE_X+100)*3,(MAZE_Y+100)*3);
	glutCreateWindow("Ivan Josa <--> Mazewar");
	glEnable(GL_DEPTH_TEST);

	//Light
	GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light_position[] = { 0.0, 100, 0.0, 0.0 };

	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);

	//Radial attenuation
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	generateMazeWithPrimAlg();
	doMazeLoops(finalMaze);

	player = Player(maze[1][1],cell_size,1,1,finalMaze);
	enemy1 = Agent(maze[(int)(MAZE_X/cell_size)][1],cell_size,MAZE_X/cell_size,1,finalMaze);

	player.generateTank();
	enemy1.generateTank();

	glBindTexture(GL_TEXTURE_2D,0);
	LoadTexture("textures/grass.jpg",64);

	glBindTexture(GL_TEXTURE_2D,1);
	LoadTexture("textures/rodaLat.jpg",64);

	glBindTexture(GL_TEXTURE_2D,2);
	LoadTexture("textures/wall.jpg",64);

	glBindTexture(GL_TEXTURE_2D,3);
	LoadTexture("textures/rodaSup.jpg",64);

	glutDisplayFunc(display);
	glutKeyboardFunc(teclat);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

void dibuixaEsfera(){
	GLfloat mat_ambient_esfera[] = {0.75, 0.75, 0.75, 1.0f};
	GLfloat mat_diffuse_esfera[] = {1.0, 1.0,1.0, 1.0f};
	GLfloat mat_specular_esfera[] = {0.8, 0.8, 0.8, 1.0f};

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_esfera);

	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glTranslatef(0, 100, 0);
	glutSolidSphere(10.0,50,50);
	glPopMatrix();
}

void display()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	PosicionarObservador(anglealpha,anglebeta,450);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-((int)MAZE_X),(int)MAZE_X,-((int)MAZE_Y),(int)MAZE_Y,10,1000);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_LINE);

	glEnable(GL_TEXTURE_2D);
	drawMazeVector(finalMaze);
//	dibuixaEsfera();

	glDisable(GL_TEXTURE_2D);

	drawStart(maze[1][1]);
	drawEnd(maze[MAZE_X/(int)cell_size][MAZE_Y/(int)cell_size]);

	player.drawTank();
	enemy1.drawTank();

	for(std::vector<Bullet>::size_type i = 0; i != player.bullets.size(); i++) {
			player.bullets[i].dibuixar();
	}

	glutSwapBuffers();
}

void teclat(unsigned char key,int x,int y)
{
	if(player.getEstat()==QUIET && enemy1.getEstat()==QUIET){

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

			enemy1.calculateNextMovement(player,maze[dstCellX][dstCellY],t,finalMaze,maze);

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

			enemy1.calculateNextMovement(player,maze[dstCellX][dstCellY],t,finalMaze,maze);

			break;

		case 'j':
			//Gir a Esquerra
			player.turnLeft();
			enemy1.calculateNextMovement(player,currentCell,t,finalMaze,maze);
			break;
		case 'l':
			//Gir a Dreta
			player.turnRight();
			enemy1.calculateNextMovement(player,currentCell,t,finalMaze,maze);
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
		case ' ': //fire
			player.fire(finalMaze,maze);
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
		else if(checkImpact(player,enemy1)){
			redrawMaze();
		}


	}
	glutPostRedisplay();
}

void idle()
{
	long t;
	t=glutGet(GLUT_ELAPSED_TIME);
	player.integrar(t);
	enemy1.integrar(t);

	for(std::vector<Bullet>::size_type i = 0; i != player.bullets.size(); i++) {

		Cell enemyCurrentCell = enemy1.getAgentCurrentCell(finalMaze,maze[enemy1.getCurrentXCell()][enemy1.getCurrentYCell()]);

		if(player.bullets[i].checkTarget(enemyCurrentCell)){
			enemy1 = Agent(maze[(int)(MAZE_X/cell_size)][1],cell_size,MAZE_X/cell_size,1,finalMaze);
			player.bullets.pop_back();
			break;
		}
		player.bullets[i].integrar(t);
	}

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
	int cellCounter = 1;

	for(unsigned int y=cell_size;y<=MAZE_Y;y+=cell_size)
	{
		for(unsigned int x=cell_size;x<=MAZE_X;x+=cell_size)
		{

			int cellX = x/(int)cell_size;
			int cellZ = y/(int)cell_size;

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

			maze[cellX][cellZ] = Cell(bottomWall,rightWall,upWall,leftWall,cellX,cellZ,cellCounter);

			++cellCounter;
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
	doMazeLoops(finalMaze);

	player = Player(maze[1][1],cell_size,1,1,finalMaze);
	enemy1 = Agent(maze[(int)(MAZE_X/cell_size)][1],cell_size,MAZE_X/cell_size,1,finalMaze);

	glutPostRedisplay();
}

void redrawMaze()
{

	player = Player(maze[1][1],cell_size,1,1,finalMaze);
	enemy1 = Agent(maze[(int)(MAZE_X/cell_size)][1],cell_size,MAZE_X/cell_size,1,finalMaze);

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

bool checkImpact(Player player,Agent enemy)
{
	Cell playerCell =player.getPlayerCurrentCell(finalMaze,maze[player.getCurrentXCell()][player.getCurrentYCell()]);

	Cell agentCell =enemy.getAgentCurrentCell(finalMaze,maze[enemy.getCurrentXCell()][enemy.getCurrentYCell()]);

	if(playerCell.getCellNumber()==agentCell.getCellNumber()){
		return true;
	}else{
		return false;
	}
}


void doMazeLoops(vector<Cell> finalMaze1){
	for(std::vector<Cell>::size_type i = 0; i != finalMaze.size(); i++) {
		if(rand()%2==0){

			switch(rand()%2){

			case 0:
				if(finalMaze[i].getRightWall().p1.x <= (int)MAZE_X){
					finalMaze[i].rightWall.isHole = true;

					Cell neightbourghCell =  finalMaze[i].getNeightbourFinalCell(finalMaze[i].rightWall,finalMaze);
					if(neightbourghCell.getLeftWall().p1.x >= 0){
						neightbourghCell.leftWall.isHole = true;
						finalMaze[i].getCellFromFinalMaze(neightbourghCell,finalMaze) =neightbourghCell;
					}

				}

				break;
			case 1:
				if(finalMaze[i].getUpWall().p1.z <= (int)MAZE_Y){
					finalMaze[i].upWall.isHole = true;

					Cell neightbourghCell =  finalMaze[i].getNeightbourFinalCell(finalMaze[i].upWall,finalMaze);
					if(neightbourghCell.getBottomWall().p1.z >= 0){
						neightbourghCell.bottomWall.isHole = true;
						finalMaze[i].getCellFromFinalMaze(neightbourghCell,finalMaze) =neightbourghCell;
					}
				}
				break;
			default:
				break;
			}

		}

		list<Cell> connectedCells = finalMaze[i].getAccessibleCells(finalMaze);
		finalMaze[i].connectedCells = connectedCells;
	}
}


