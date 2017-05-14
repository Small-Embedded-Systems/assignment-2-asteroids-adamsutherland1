/* Controller */

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* hardware platform libraries */
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"


typedef enum {JLT, JRT, JUP, JDN, JCR} btnId_t;
static DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
bool jsPrsdAndRlsd(btnId_t b);


bool joystickup;// for joystick up.
bool joystickdown; // for joystick down.
bool joystickcenter; // for joystick center.
bool joystickleft; // for joystick left.
bool joystickright; // for joystick right.


void controls(void) /*controls for the ship and shots to fire*/
{
	if(jsPrsdAndRlsd(JUP)){ // for joystick UP starts the movement of the ship //
		joystickup = true; // starts movement
		joystickleft = false; //stops left turn.
		joystickright = false; //stops right turning.
	}
	if(jsPrsdAndRlsd(JDN)){ // for joystick DOWN stops the entire movement. // 
		joystickdown = true; // sets to true.
	}
	if(jsPrsdAndRlsd(JRT)){ // for joystick RIGHT //
		joystickright = true; // reiterates that joystick right is = true
		joystickleft = false;// stops the turning left when joystick left pressed.
	}
	if(jsPrsdAndRlsd(JLT)){ //	for joystick LEFT //
		joystickleft = true; // reiterates that joystick left is = true
		joystickright = false; // stops the turning right when joystick left pressed.
	}
	if(jsPrsdAndRlsd(JCR)){ // used to fire missiles //
		createMissile(shots);// calls the funciton
	}
}

bool jsPrsdAndRlsd(btnId_t b) { // controls the button presses 
    bool result = false;
    uint32_t state;
    static uint32_t savedState[5] = {1,1,1,1,1};//5 1s to make it use all 5 buttons
    //initially all 1s: nothing pressed
    state = jsBtns[b].read();
    if ((savedState[b] == 0) && (state == 1)) {
        result = true;
    }
    savedState[b] = state;
    return result;
}
