/* Asteroids model */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"
#include "controller.h"

double x,y,sidex1,sidex2,sidey1,sidey2;
int length = 20; // changes size of the ship
float angle = 0.0;//angle values
float vel_x, vel_y;//velocity values
float angle_stepsize = 0.025; // change speed of the ship
static int numberRocks;//current rock count
		
void shipCheck() // this function checks the ship being outof bounds. makes ship appear in d
{
	if (shipCenterVert - 20 > 272){ 
			shipCenterVert = 25;}
	if (shipCenterHor + 7 < 0){
			shipCenterHor = 486;}
	if (shipCenterHor - 7 >487){
			shipCenterHor = 8;}
	if (shipCenterVert + 10 < 19){
			shipCenterVert = 285;}
	
}


void Thrust() 
{
	 vel_x =  (10 * cos(angle));//turning circle
   vel_y =  (10	* sin(angle));//turning circle
	if(joystickup == true){ // sets joystick up to true.
	shipCenterHor += (vel_x /25);//higher number = slower as dividing by.
	shipCenterVert += (vel_y /25);//higher number = slower as dividing by.
		joystickdown=false;//sets joystick down to false
	}
}

void shipTurns()
{
        x = length * cos (angle); // using cosine to calculate  x angle
        y = length * sin (angle);//using sine to calculate y angle
			  sidex1 = length * cos (angle + 4.01426);// angle that the ship comes off at. = 50 degrees either side of 180
			  sidey1 = length * sin (angle + 4.01426);// angle that the ship comes off at. = 50 degrees either side of 180
			  sidex2 = length * cos (angle + 2.26893);// angle that the ship comes off at. = 50 degrees either side of 180
				sidey2 = length * sin	(angle + 2.26893);// angle that the ship comes off at. = 50 degrees either side of 180
	
	/* this section keeps ship sides and lines equal to another and at the same point*/
	
				shipTipHor = x + shipCenterHor;
				shipTipVert = y + shipCenterVert;
				crnrrightHor = sidex1 + shipCenterHor;
				crnrrightVert = sidey1 + shipCenterVert;
				crnrleftHor = sidex2 + shipCenterHor;
				crnrleftVert = sidey2 + shipCenterVert;
	//----------------------------------------------------------//
	
	if (angle > 2 * pi) { //keeps pi in check for the turning circle.
		angle = 0.1;
	}
	if (angle < 0) {
		angle = (2 * pi) - 0.1; //keeps pi in check for the turning circle.
	}
	if (joystickleft == true) { 
		angle += angle_stepsize; //addition assignemnt for angle and stepsize helps to control the ship
	}
	if (joystickright == true)
	{
		angle -= angle_stepsize; //controls right hand turn for ship turn is subtraction assignment.
	}
	if (joystickdown == true){
		joystickleft= false;
		joystickright = false;
		joystickup = false;
		joystickdown = false;
		angle = angle; // this stops the turning upon pressing down.
		}
}



void newRockNode(rock_t* head)//creates new rock uses the struct and assigns random values to position and to the vector
{
	//assigns current to head.
	if(numberRocks < 5) //checks number of rocks is less than 5.
	{
	rock_t* headnode = head; // tells what head is defined as.
	while (headnode->next !=NULL) //checks not null as null equals the end of the list.
		{ 
			headnode = headnode ->next;//points to the next node in the list.
		}
	headnode->next =(rock_t*)malloc(sizeof(rock_t));//memory allocation for the node and then memory allocation equal to the size of the linked list.
	headnode->next->pos.x = randrange(17,464);
	headnode->next->pos.y = randrange(16,256);//assigns a random number from utils in the range 17-463 for x coordinate and 16 255 for y.
	headnode->next->vec.x = randrange(-1,3);//assigns a random vector value.
	headnode->next->vec.y = randrange(-1,3);//assigns a random vector value.
	if(headnode->next->vec.x == 0 && headnode->next->vec.y == 0) //makes sure that the vec is greater than 0 so asteroids move.
		{
			headnode->next->vec.x=1;
			headnode->next->vec.y=1;
		}
	headnode->next->next=NULL;//moves to the last node to end.
	numberRocks++;//increments through rocks so that it does each one.
	}
}

void rockChecks(rock_t* head){ // checks the rock position if it goes off the screen.
	rock_t* headnode = head; // declaring name fr head.
	if (headnode!=NULL) { //checks not null as null equals the end of the list.
		headnode->pos.x += headnode->vec.x; // assigning movement
		headnode->pos.y += headnode->vec.y; // assigning movement
		if(headnode->pos.x >496) {//checks each position
			headnode->pos.x = -16;
		}
		if(headnode->pos.x < -16){//checks each position
			headnode->pos.x = 496;
		}
		if(headnode->pos.y > 290) {//checks each position
			headnode->pos.y = -20;
		}
		if(headnode->pos.y <-20) {//checks each position
			headnode->pos.y =290;
		}
		headnode = headnode->next; // moves to next
		rockChecks(headnode); //calls itself again.
	}
}



void createMissile(shot_t* head) {
	shot_t* currentMissile = head;
	while (currentMissile->next !=NULL) {//checks not null as null equals the end of the list.
		currentMissile = currentMissile->next; //moves to next.
	}
	currentMissile->next = (shot_t*)malloc(sizeof(shot_t)); // assigning memory for shots
	currentMissile->next->pos.x = shipTipHor;//fires from tip
	currentMissile->next->pos.y = shipTipVert;//fires from tip
	currentMissile->next->vec.x = vel_x;//assigns velocity
	currentMissile->next->vec.y = vel_y;//assigns velocity
	currentMissile->next->next = NULL; // ends the shot.
}

void missileMethods(shot_t* head) {
	shot_t* currentMissile = head;
	while(currentMissile !=NULL) {//checks not null
		currentMissile->pos.x += currentMissile->vec.x; //assigns movement
		currentMissile->pos.y += currentMissile->vec.y; //assigns movement
		currentMissile=currentMissile->next;
	}
}

void collisionCheck(rock_t* head){
	rock_t* headnode = head;
	{
	if(headnode->pos.x < shipCenterHor +20 && headnode->pos.x > shipCenterHor - 20 && headnode->pos.y > shipCenterVert - 20 && headnode->pos.y < shipCenterVert + 20)
		{
		headnode->pos.x = randrange(10, 470);//respawns the asteroid in a random place upon collision stops losing all lives.
		headnode->pos.y = randrange(10, 260);//respawns the asteroid in a random place upon collision stops losing all lives.
		lives--;
		}
	}
}

void physics(void)
{
	shipTurns();
	Thrust();
	shipCheck();
	newRockNode(asteroids);
	collisionCheck(asteroids);
	rockChecks(asteroids);
	missileMethods(shots);
}
