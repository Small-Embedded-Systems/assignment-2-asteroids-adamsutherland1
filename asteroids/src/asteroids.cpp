/* Asteroids
    Sample solution for assignment
    Semester 2 -- Small Embedded Systems
    Dr Alun Moon
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"

/* Game state */
float elapsed_time; 
int   score;
int   lives;
//struct ship, player;

double shipCenterHor = 240; //stored variables for ship for position
double shipCenterVert = 150; // y position
double shipTipHor = shipCenterHor; // position
double shipTipVert = 	shipCenterVert - 15; // position
double crnrrightVert = shipCenterVert + 10;// position
double crnrrightHor = shipCenterHor +7;// position
double crnrleftVert = shipCenterVert+10;// position
double crnrleftHor = shipCenterHor -7;// position
rock_t *asteroids;
shot_t *shots;

float Dt = 0.01f;

Ticker model, view, controller;

bool paused = true;
/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);

void initialise(){
    asteroids = static_cast<rock_t*>(malloc(sizeof(rock_t)));//initialise the asteroids.
		asteroids->next = NULL;
		asteroids->pos.x =0;
		asteroids->pos.y=0;
		asteroids->vec.x =1;
		asteroids->vec.y=1;//initialise the shots
		shots = static_cast<shot_t*>(malloc(sizeof(shot_t)));
		shots->next = NULL;
}

int main()
{

    init_DBuffer();
    

    view.attach( draw, 0.025);
    model.attach( physics, Dt);
    controller.attach( controls, 0.1);
    
    lives = 5;
    initialise();
    /* Pause to start */
   // while( userbutton.read() ){ /* remember 1 is not pressed */
        //paused=true;
       // wait_ms(100);
    //}
   // paused = false;
    //while(true) {
        /* do one of */
        /*Wait until all lives have been used*/
       // while(lives>0){
        //    // possibly do something game related here
           // wait_ms(200);
        }
        /* Wait until each life is lost
        while( inPlay ){
            // possibly do something game related here
            wait_ms(200);
        }
        */
   // }
//}
