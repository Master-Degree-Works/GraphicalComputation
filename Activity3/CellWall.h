/*
 * CellWall.h
 *
 * Author: Ivan Josa
 */

#ifndef CELLWALL_H_
#define CELLWALL_H_

#ifdef __APPLE__
# include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>          /* Open GL Util    OpenGL*/
#endif


#include <string>

using namespace std;



struct Point{
	int x;
	int y;
	int z;

	Point(){
		x = 0;
		y = 0;
		z = 0;
	}

	Point(int px,int py,int pz){
		x = px;
		y = py;
		z = pz;
	}
};


class CellWall{

	bool isInMaze;

	bool isHole;
	string type;
	int bottomWallId;
	int upWallId;
	int leftWallId;
	int rightWallId;

public:

	Point p1;
	Point p2;

	CellWall();

	CellWall(Point pp1,Point pp2);

	void setIsHole(bool pIsHole);

	bool getIsHole();

	void setIsInMaze(bool pIsInMaze);

	bool getIsInMaze();

	string getType();

	void setType(string pStr);

	bool isNeightBour(CellWall pWall,const unsigned int wall_width);

	void drawWall(const unsigned int wall_width);

	void drawWall();

	void drawHole(const unsigned int wall_width);

	void generateBottomWall();
	void generateUpWall();
	void generateLeftWall();
	void generateRightWall();
};


#endif /* CELLWALL_H_ */
