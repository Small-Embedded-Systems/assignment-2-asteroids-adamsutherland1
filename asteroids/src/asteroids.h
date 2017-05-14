/* Game state */

extern float elapsed_time; /* time this ship has been active */
extern int   score;        /* total score so far */
extern int   lives;        /* lives  */
extern double shipCenterHor; // external allowance for variables
extern double shipCenterVert; // external allowance for variables
extern double shipTipHor;// external allowance for variables
extern double shipTipVert;// external allowance for variables
extern double crnrrightHor;// external allowance for variables
extern double crnrrightVert;// external allowance for variables
extern double crnrleftHor;// external allowance for variables
extern double crnrleftVert;// external allowance for variables

//extern struct ship player;

extern struct rock_t *asteroids; /* array of rocks / pointer to linked-list */
extern struct shot_t *shots;  /* array of missiles / pointer to linked-list */

extern const float Dt; /* Time step for physics, needed for consistent motion */
