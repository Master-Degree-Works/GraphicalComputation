/*
 * Constants.h
 *
 * Author: Ivan Josa
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


//Dimensions
const unsigned int MAZE_X = 500;
const unsigned int MAZE_Y = 500;
const unsigned int cell_size = 50;

//Smooth movement duration (ms)
const unsigned int movement_duration = 750;


const unsigned int wall_width = 0;
const unsigned int player_reduction  = 10; // Lower value is greater player size (player_size = cell_size/player_reduction)


//Direction Constants
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

//State Constants
#define QUIET 0
#define MOVING 1




#endif /* CONSTANTS_H_ */
