/* Asteroids view
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

#include "asteroids.h"
#include "model.h"
#include "utils.h"


Display *graphics = Display::theDisplay();

const colour_t background = rgb(0,0,0); /* Black */
const float pi = 3.1415926f;

#define asteroid_width 16
#define asteroid_height 16
static unsigned char asteroid[] = { // bitmap
   0x01, 0x00, 0x03, 0xe0, 0x0c, 0x30, 0x10, 0x18, 0x20, 0x08, 0x20, 0x04,
   0x20, 0x02, 0x60, 0x03, 0x40, 0x01, 0x40, 0x01, 0x40, 0x01, 0x40, 0x03,
   0x40, 0x02, 0x30, 0x04, 0x0c, 0x38, 0x03, 0xc0 };

#define heart_width 7
#define heart_height 8
static unsigned char heart_bits[] = { //bitmap
 0x36, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 0x08 };


/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}


void drawSection(void)
{
	/*screen stuff -----------------------------------------------*/
	graphics->fillScreen(background);
	graphics->drawRect(0,0,480,272,WHITE); /*white border*/
	graphics->setCursor(20,25);
	graphics->printf("Score %i",score,WHITE);
	/*screen stuff -----------------------------------------------*/
}

void LivesHeart(void) // draws the hearts
{
	for (int i=1;i<=lives;i++){
		graphics->drawBitmap((i*20),10,heart_bits,7,8 ,RED); // loop places heart at set distance from one another.
	}
}


void Ship()//draws the ship
{
	graphics->drawLine(shipTipHor, shipTipVert, crnrrightHor, crnrrightVert,BLUE);//RIGHT //draws lines in correct place
	graphics->drawLine(crnrrightHor, crnrrightVert, shipCenterHor, shipCenterVert,BLUE);//BOTTOM RIGHT //draws lines in correct place
	graphics->drawLine(crnrleftHor, crnrleftVert, shipCenterHor, shipCenterVert,BLUE);//BOTTOM LEFT //draws lines in correct place
	graphics->drawLine(crnrleftHor, crnrleftVert,shipTipHor, shipTipVert,BLUE);//LEFT //draws lines in correct place
}

void shield() // draws shield 20 px out from center
{
	graphics->drawCircle(shipCenterHor, shipCenterVert,20,GREEN); 
}

void drawAsteroid(rock_t *head){ // draws the asteroid
	rock_t* headnode = head;
	while(headnode!=NULL) //checks not null
{
	graphics->drawBitmap(headnode->pos.x,headnode->pos.y,asteroid, 16,16, WHITE);//bitmsp
	headnode = headnode->next;
}
}

void drawMissile(shot_t* head){
	shot_t* headnode=head;
	while(headnode !=NULL) { //checks not null
		graphics->fillCircle(headnode->pos.x, headnode->pos.y, 2, RED);
		headnode = headnode->next;
	}
}

void increasesScore() // increments the score rapidly.
{
	score++;
}

void draw(void) // function execution
{
		
		drawSection();
		increasesScore();
		Ship();
		shield();
		drawMissile(shots);
		drawAsteroid(asteroids);
		LivesHeart();
    swap_DBuffer();	
}
