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
#include <cstring>

#ifndef	DRAWERUTILS
#include "DrawerUtils.h"
#endif


Cell maze[MAZE_X][MAZE_Y];
vector< Cell > finalMaze;
Player player;

using namespace std;

void display();
void teclat(unsigned char c,int x,int y);
void idle();


void fillMaze();
void generateMazeWithPrimAlg();
void resetMaze();
bool checkIsFinish(Cell cell);


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,
	                       (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	glutInitWindowSize(MAZE_X+100,MAZE_Y+100);
	glutCreateWindow("Ivan Josa <--> Mazemagik");

	generateMazeWithPrimAlg();

	player = Player(maze[1][1],cell_size,1,1);

	glutDisplayFunc(display);
	glutKeyboardFunc(teclat);
	glutIdleFunc(idle);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,(MAZE_X+100),0.0,(MAZE_Y+100));

	glutMainLoop();
	return 0;
}

void display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawMazeVector(finalMaze);

	drawStart(maze[1][1]);
	drawEnd(maze[MAZE_X/cell_size][MAZE_Y/cell_size]);

	player.draw();

	glutSwapBuffers();
}

void teclat(unsigned char key,int x,int y)
{
	if(player.getEstat()==QUIET){

		long t=	glutGet(GLUT_ELAPSED_TIME);

		Cell currentCell = player.getPlayerCurrentCell(finalMaze,maze[player.getCurrentXCell()][player.getCurrentYCell()]);
		Cell dstCell;

		switch(key){
		case 'w': //Amunt

			dstCell = player.getPlayerDstCell(finalMaze,maze[player.getCurrentXCell()][player.getCurrentYCell()+1]);

			player.moveUp(currentCell,dstCell,cell_size,t);
			break;
		case 's': //Avall

			dstCell = player.getPlayerDstCell(finalMaze,maze[player.getCurrentXCell()][player.getCurrentYCell()-1]);

			player.moveDown(currentCell,dstCell,cell_size,t);
			break;
		case 'a': //Esquerra

			dstCell = player.getPlayerDstCell(finalMaze,maze[player.getCurrentXCell()-1][player.getCurrentYCell()]);

			player.moveLeft(currentCell,dstCell,cell_size,t);
			break;
		case 'd': //dreta

			dstCell = player.getPlayerDstCell(finalMaze,maze[player.getCurrentXCell()+1][player.getCurrentYCell()]);

			player.moveRight(currentCell,dstCell,cell_size,t);
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

/****************************************************************************************************/

/*
 * Inicialitza el laberint amb totes les cel·les amb 4 murs
 */
void fillMaze()
{
	for(unsigned int x=cell_size;x<=MAZE_X;x+=cell_size)
	{
		for(unsigned int y=cell_size;y<=MAZE_Y;y+=cell_size)
		{
			//Bottom Wall
			Point p11 = Point(x+wall_width,y);
			Point p12 = Point(x+cell_size-wall_width,y);
			CellWall bottomWall = CellWall(p11,p12);
			bottomWall.setType("B");

			//Right Wall
			Point p21 = Point(x+cell_size,y+wall_width);
			Point p22 = Point(x+cell_size,y+cell_size-wall_width);
			CellWall rightWall = CellWall(p21,p22);
			rightWall.setType("R");

			//UpWall
			Point p31 = Point(x+cell_size-wall_width,y+cell_size);
			Point p32 = Point(x+wall_width,y+cell_size);
			CellWall upWall = CellWall(p31,p32);
			upWall.setType("U");

			//LeftWall
			Point p41 = Point(x,y+cell_size-wall_width);
			Point p42 = Point(x,y+wall_width);
			CellWall leftWall = CellWall(p41,p42);
			leftWall.setType("L");

			maze[x/cell_size][y/cell_size] = Cell(bottomWall,rightWall,upWall,leftWall,x/cell_size,y/cell_size);
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
			if(oppositeCell.getBottomWall().p1.y >= 0){
				walls.push_back(oppositeCell.getBottomWall());
			}

			if(oppositeCell.getRightWall().p1.x <= MAZE_X){
				walls.push_back(oppositeCell.getRightWall());
			}

			if(oppositeCell.getLeftWall().p1.x >= 0){
				walls.push_back(oppositeCell.getLeftWall());
			}

			if(oppositeCell.getUpWall().p1.y <= MAZE_Y){
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
	player = Player(maze[1][1],cell_size,1,1);
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
