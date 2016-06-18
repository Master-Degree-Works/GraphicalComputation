/*
 * Constants.h
 *
 * Author: Ivan Josa
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


//Maze Dimensions
const unsigned int MAZE_X = 300;
const unsigned int MAZE_Y = 300;

//Cell dimensions
const double cell_size = 50;
const double wall_width = cell_size/10;
const double wall_heigth = cell_size/5;
const float startEndCellReduction  = 0.3;

//Tank Dimensions
const double wheelWidth = 25;
const double cannonRadius = 15;
const double cannonLength = cell_size*2;

//Tank Smooth movement duration (ms)
const unsigned int movement_duration = 750;


//Direction Constants
#define FORWARD 1
#define BACKWARD 2

//State Constants
#define QUIET 0
#define MOVING 1
#define TURNING 2

//Orientation Constants
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//BFS Constants
#define VISITED 1
#define UNVISITED 2
#define EXAMINED 3


#endif /* CONSTANTS_H_ */
