/*
 * CellWall.h
 *
 * Author: Ivan Josa
 */

#ifndef CELLWALL_H_
#define CELLWALL_H_

#include <string>

using namespace std;

struct Point{
	unsigned int x;
	unsigned int y;

	Point(){
		x = 0;
		y = 0;
	}

	Point(unsigned int px,unsigned int py){
		x = px;
		y = py;
	}
};


class CellWall{

	bool isInMaze;

	bool isHole;
	string type;

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
};


#endif /* CELLWALL_H_ */
