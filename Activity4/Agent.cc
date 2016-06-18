/*
 * Agent.cc
 *
 * Author: Ivan Josa
 */



#include "Constants.h"
#include <iostream>
#include <stack>
#include "Agent.h"

int agentTankId;
int agentIdCos;
int agentWheelId;
list<Cell> visitedCells;
list<Cell> solPath;
int sol[MAZE_X][MAZE_Y];
list<Cell> bfsPath;

bool bfsDone = false;

void dibuixarCosAgent();
void dibuixarRodaDretaAgent();
void dibuixarRodaEsquerraAgent();
void dibuixarCanoAgent();
bool cellIsVisited(Cell analyzedCell,list<Cell> visitedCells);

Agent::Agent()
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


Agent::Agent(float x,float y,float z)
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

Agent::Agent(Cell pCell, int cell_size,int xCell,int yCell,vector<Cell> finalMaze)
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
	}else if(pCell.getCellFromFinalMaze(pCell,finalMaze).getLeftWall().getIsHole()){
		this->orientation = WEST;
		this->left = 0;
		this->turningLeft = true;
	}

}

void Agent::setVX(float vx)
{
	this->vx = vx;
}

float Agent::getVX()
{
	return this->vx;
}

void Agent::setVY(float vy)
{
	this->vy = vy;
}

float Agent::getVY()
{
	return this->vy;
}

void Agent::setEstat(int estat)
{
	this->estat = estat;
}

int Agent::getEstat()
{
	return this->estat;
}

void Agent::setX(float x)
{
	this->x = x;
}

float Agent::getX()
{
	return this->x;
}

void Agent::setY(float y)
{
	this->y = y;
}

float Agent::getY()
{
	return this->y;
}

void Agent::setCurrentXCell(int currentXCell)
{
	this->currentXCell = currentXCell;
}

int Agent::getCurrentXCell()
{
	return this->currentXCell;
}

void Agent::setCurrentYCell(int currentYCell)
{
	this->currentYCell = currentYCell;
}

int Agent::getCurrentYCell(){
	return this->currentYCell;
}

void Agent::setLastTime(long t_darrer)
{
	this->t_darrer = t_darrer;
}

long Agent::getLastTime()
{
	return this->t_darrer;
}

void Agent::setEndTime(long t_fi)
{
	this->t_fi = t_fi;
}

long Agent::getEndTime()
{
	return this->t_fi;
}

void Agent::setOrientation(int orientation){
	this->orientation = orientation;
}
int Agent::getOrientation(){
	return this->orientation;
}

/**************************************/

/*
 * Assigna una posició al jugador
 */
void Agent::assignar_posicio(float px, float py,float pz)
{
	this->x = px;
	this->y = py;
	this->z = pz;
}

/*
 * Inicia el moviment del jugador
 */
void Agent::iniciar_moviment(float px,float py,float pz,int durada, long t)
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
void Agent::integrar(long t)
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
void Agent::moveForward(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,FORWARD)){
		this->assignar_posicio(this->x,this->y,this->z);
		this->previousCell = currentCell;
		switch(this->orientation){
		case NORTH:
			this->iniciar_moviment(this->x,0,this->z-cell_size,movement_duration,t);
			this->currentYCell--;
			break;
		case SOUTH:
			this->iniciar_moviment(this->x,0,this->z+cell_size,movement_duration,t);
			this->currentYCell++;
			break;
		case EAST:
			this->iniciar_moviment(this->x+cell_size,0,this->z,movement_duration,t);
			this->currentXCell++;
			break;

		case WEST:
			this->iniciar_moviment(this->x-cell_size,0,this->z,movement_duration,t);
			this->currentXCell--;
			break;
		default:break;
		}


	}
}


/*
 * Comprova si el moviment avall és possible i en cas afirmatiu, el realitza
 */
void Agent::moveBackward(Cell currentCell,Cell dstCell,int cell_size,long t)
{
	if(this->canMove(currentCell,dstCell,BACKWARD)){

		this->assignar_posicio(this->x,this->y,this->z);
		this->previousCell = currentCell;
		switch(this->orientation){
		case NORTH:
			this->iniciar_moviment(this->x,0,this->z+cell_size,movement_duration,t);
			this->currentYCell++;
			break;
		case SOUTH:
			this->iniciar_moviment(this->x,0,this->z-cell_size,movement_duration,t);
			this->currentYCell--;
			break;
		case EAST:
			this->iniciar_moviment(this->x-cell_size,0,this->z,movement_duration,t);
			this->currentXCell--;
			break;
		case WEST:
			this->iniciar_moviment(this->x+cell_size,0,this->z,movement_duration,t);
			this->currentXCell++;
			break;
		default:break;
		}
	}
}


/*
 * Gira el tanc a la dreta
 */
void Agent::turnRight()
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
void Agent::turnLeft()
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
bool Agent::canMove(Cell srcCell,Cell dstCell,int direction)
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
Cell Agent::getAgentCurrentCell(vector < Cell > generatedMaze, Cell pCell)
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
Cell Agent::getAgentDstCell(vector < Cell > generatedMaze, Cell pCell)
{
	Cell currentCell;

	for (size_t i = 0; i != generatedMaze.size(); ++i){
		if(generatedMaze[i] == pCell){
			currentCell = generatedMaze[i];
		}
	}
	return currentCell;
}


void Agent::generateTank()
{

	agentIdCos=glGenLists(1);
	glNewList(agentIdCos,GL_COMPILE);

	glBegin(GL_QUADS);

	//Cos central rectangular
	glTexCoord2f(-1,0.0);glVertex3i(25, -25, 0);
	glTexCoord2f(1,0.0);glVertex3i(25, 25, 0);
	glTexCoord2f(1,1);glVertex3i(-25, 25, 0);
	glTexCoord2f(-1,1);glVertex3i(-25, -25, 0);

	glEnd();
	glEndList();


	agentWheelId=glGenLists(1);
	glNewList(agentWheelId,GL_COMPILE);

	glBegin(GL_QUADS);

	glTexCoord2f(-1,0.0);glVertex3i(25, -100, 0);
	glTexCoord2f(1,0.0);glVertex3i(25, 100, 0);
	glTexCoord2f(1,1);glVertex3i(-25, 100, 0);
	glTexCoord2f(-1,1);glVertex3i(-25, -100, 0);

	glEnd();
	glEndList();
}

void Agent::drawTank(){
	glPushMatrix();


	int tx = this->x;
	int tz = this->z;

	int XFactor = 1+(MAZE_X / cell_size)/2;

	glTranslatef(tx-(cell_size*XFactor),10,tz-((int)cell_size*XFactor));

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

	dibuixarCosAgent();

	glScaled(0.75,0.75,0.75);
	dibuixarRodaDretaAgent();
	dibuixarRodaEsquerraAgent();
	dibuixarCanoAgent();

	glPopMatrix();
	glPopMatrix();

}

void dibuixarCosAgent(){


	glColor3d(128,128,0);

	//Roja
	glPushMatrix();
	glTranslatef(0,0,25);
	glCallList(agentIdCos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,25,0);
	glRotatef(-90,1,0,0);
	glCallList(agentIdCos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-25,0);
	glRotatef(90,1,0,0);
	glCallList(agentIdCos);
	glPopMatrix();

	//Verda
	glPushMatrix();
	glTranslatef(0,0,-25);
	glRotatef(180,0,1,0);
	glCallList(agentIdCos);
	glPopMatrix();

	//Damunt
	glPushMatrix();
	glColor3f(0.5,1.5,0.5);
	glRotatef(90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(agentIdCos);
	glPopMatrix();


	//Davall
	glPushMatrix();
	glColor3f(1,0,0);
	glRotatef(-90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(agentIdCos);
	glPopMatrix();

}

void dibuixarRodaDretaAgent(){

	glPushMatrix();
	glColor3f(0.5,0.5,0.5);

	glTranslatef(-25,0,50);

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,25);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,100,0);
	glRotatef(-90,1,0,0);
	glCallList(agentIdCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,-100,0);
	glRotatef(90,1,0,0);
	glCallList(agentIdCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,-25);
	glRotatef(180,0,1,0);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Blava
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(-90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();

}

void dibuixarRodaEsquerraAgent(){

	glPushMatrix();
	glTranslatef(-25,0,-50);

	glColor3f(0.5,0.5,0.5);


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,25);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,100,0);
	glRotatef(-90,1,0,0);
	glCallList(agentIdCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,-100,0);
	glRotatef(90,1,0,0);
	glCallList(agentIdCos);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,1);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0,0,-25);
	glRotatef(180,0,1,0);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Groga
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,3);
	glEnable(GL_TEXTURE_2D);
	glRotatef(-90,0,1,0);
	glTranslatef(0,0,25);
	glCallList(agentWheelId);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();

}

void dibuixarCanoAgent(){

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();
	glColor3f(1,0,0);
	glRotatef(180, 0, 1,1);
	glTranslatef(0,0,25);
	gluCylinder(quadratic,cannonRadius,cannonRadius,cannonLength,1000,1000);
	glPopMatrix();
}


bool cellIsVisited(Cell analyzedCell,list<Cell> visitedCells){
	if(visitedCells.size()==0){
		return false;
	}
	for (std::list<Cell>::iterator it = visitedCells.begin(); it != visitedCells.end(); it++){
		if(analyzedCell==(*it)){
			return true;
		}
	}
	return false;
}

void printPath(list<Cell> bfsPat){
	for (std::list<Cell>::iterator it = bfsPat.begin(); it != bfsPat.end(); it++){
		Cell analyzedCell =*it;
		cout<<"Cell #:" << analyzedCell.getCellNumber()<<endl;
	}
}

void Agent::breakInconsistence(int orientation,Cell agentCurrentCell,Cell agentDstCell,long t,vector<Cell> finalMaze,Cell maze[MAZE_X][MAZE_Y]){
	list<Cell> neighbourCells = agentCurrentCell.getAccessibleCells(finalMaze);

	if(neighbourCells.size()>0){

		for (std::list<Cell>::iterator it = neighbourCells.begin(); it != neighbourCells.end(); it++){
			Cell randomCell =  (*it);

			Cell newDstCell;

			if(agentCurrentCell.getMazeX()<(*it).getMazeX()){
				newDstCell = newDstCell.getCellFromFinalMaze(maze[agentCurrentCell.getMazeX()+1][agentCurrentCell.getMazeY()],finalMaze);
				this->calculateMovement(EAST,newDstCell,(*it),t);
			}
			else if(agentCurrentCell.getMazeX()>(*it).getMazeX()){
				newDstCell = newDstCell.getCellFromFinalMaze(maze[agentCurrentCell.getMazeX()-1][agentCurrentCell.getMazeY()],finalMaze);
				this->calculateMovement(WEST,newDstCell,(*it),t);
			}
			else if(agentCurrentCell.getMazeY()<(*it).getMazeY()){
				newDstCell = newDstCell.getCellFromFinalMaze(maze[agentCurrentCell.getMazeX()][agentCurrentCell.getMazeY()-1],finalMaze);
				this->calculateMovement(SOUTH,newDstCell,(*it),t);
			}
			else if(agentCurrentCell.getMazeY()>(*it).getMazeY()){
				newDstCell = newDstCell.getCellFromFinalMaze(maze[agentCurrentCell.getMazeX()][agentCurrentCell.getMazeY()+1],finalMaze);
				this->calculateMovement(NORTH,newDstCell,(*it),t);
			}
			break;
		}
	}

}

void Agent::calculateMovement(int direction,Cell currentCell,Cell dstCell,long t){

	if(this->orientation == WEST){
		if(direction==WEST){
			this->moveForward(currentCell,dstCell,cell_size,t);
		}else if(direction==EAST){
			this->moveBackward(currentCell,dstCell,cell_size,t);
		}else if(direction==NORTH){
			this->turnRight();
		}else if(direction==SOUTH){
			this->turnLeft();
		}
	}
	else if(this->orientation == EAST){
		if(direction==WEST){
			this->moveBackward(currentCell,dstCell,cell_size,t);
		}else if(direction==EAST){
			this->moveForward(currentCell,dstCell,cell_size,t);
		}else if(direction==NORTH){
			this->turnLeft();
		}else if(direction==SOUTH){
			this->turnRight();
		}

	}
	else if(this->orientation == NORTH){
		if(direction==WEST){
			this->turnLeft();
		}else if(direction==EAST){
			this->turnRight();
		}else if(direction==NORTH){
			this->moveForward(currentCell,dstCell,cell_size,t);
			visitedCells.push_back(dstCell);
		}else if(direction==SOUTH){
			this->moveBackward(currentCell,dstCell,cell_size,t);
			visitedCells.push_back(dstCell);
		}

	}
	else if(this->orientation == SOUTH){
		if(direction==WEST){
			this->turnRight();
		}else if(direction==EAST){
			this->turnLeft();
		}else if(direction==NORTH){
			this->moveBackward(currentCell,dstCell,cell_size,t);
			visitedCells.push_back(dstCell);
		}else if(direction==SOUTH){
			this->moveForward(currentCell,dstCell,cell_size,t);
			visitedCells.push_back(dstCell);
		}
	}

}

void Agent::calculateNextMovement(Player player,Cell playerDstCell,long t,vector<Cell> finalMaze,Cell maze[MAZE_X][MAZE_Y]){

	Cell agentCurrentCell =this->getAgentCurrentCell(finalMaze,maze[this->getCurrentXCell()][this->getCurrentYCell()]);


	list<Cell> bfsPath = this->DFS(agentCurrentCell,playerDstCell,finalMaze,maze);

	Cell agentDstCell;

	for (std::list<Cell>::iterator it = bfsPath.begin(); it != bfsPath.end(); it++){

		Cell analyzedCell =*it;
		agentDstCell = this->getAgentDstCell(finalMaze,maze[analyzedCell.getMazeX()][analyzedCell.getMazeY()]);

		//		cout<<"From Cell #:" << agentCurrentCell.getCellNumber()<<" To Cell #:" << analyzedCell.getCellNumber()<<endl;


		if(agentCurrentCell.getCellNumber()==agentDstCell.getCellNumber()){
			bfsPath = this->DFS(agentCurrentCell,playerDstCell,finalMaze,maze);
			continue;
		}
		else if(this->previousCell.getCellNumber() == agentDstCell.getCellNumber()){

			bfsPath = this->DFS(agentCurrentCell,playerDstCell,finalMaze,maze);
			continue;
		}



		if(agentCurrentCell.getMazeX()<agentDstCell.getMazeX()){
			this->calculateMovement(EAST,agentCurrentCell,agentDstCell,t);
		}
		else if(agentCurrentCell.getMazeX()>agentDstCell.getMazeX()){
			this->calculateMovement(WEST,agentCurrentCell,agentDstCell,t);
		}
		else if(agentCurrentCell.getMazeY()<agentDstCell.getMazeY()){
			this->calculateMovement(SOUTH,agentCurrentCell,agentDstCell,t);
		}
		else if(agentCurrentCell.getMazeY()>agentDstCell.getMazeY()){
			this->calculateMovement(NORTH,agentCurrentCell,agentDstCell,t);
		}
		else
		{
			bfsPath = this->DFS(agentCurrentCell,playerDstCell,finalMaze,maze);
		}

		break;
	}
}



list<Cell> Agent::DFS(Cell agentStartCell,Cell playerDstCell,vector<Cell> finalMaze,Cell maze[MAZE_X][MAZE_Y]){


	list<Cell> path;
	stack<Cell> s;
	int n = finalMaze.size();

	bool visited[n];

	int i;

	for(i=0;i<=n;i++){
		visited[i] = false;
	}

	s.push(agentStartCell);
	visited[agentStartCell.getCellNumber()] = true;

	if(agentStartCell.getCellNumber()==playerDstCell.getCellNumber()){
		path.push_back(agentStartCell);
		return path;
	}

	//	cout << "Depth first Search with objective Cell #"<< playerDstCell.getCellNumber()<<" starting from Cell #"<< agentStartCell.getCellNumber() << " : " << endl;

	bool found = false;
	while(!s.empty()){
		Cell k = s.top();
		s.pop();

		//		cout<< k.getCellNumber()<<" ";

		//L'afegim com a path
		path.push_back(k);

		if(k.getCellNumber()==playerDstCell.getCellNumber()){
			found= true;
			break;
		}

		list<Cell> neighbourCells = k.getAccessibleCells(finalMaze);

		for (std::list<Cell>::iterator it = neighbourCells.begin(); it != neighbourCells.end(); it++){
			if(!visited[(*it).getCellNumber()]){
				s.push((*it));
				visited[(*it).getCellNumber()] = true;
			}
		}
	}

	//	cout<<endl;
	if(found){
		return path;
	}
}
