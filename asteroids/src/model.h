/* Asteroids Model */
struct point {
    float x,y;
};

typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some insitial struct types if you want to usd them */
/*struct ship {
    coordinate_t p;
    vector_t     v;
};*/

/* initial struts for building linked lists */
typedef struct rock_t { //declaration for A rock/node not the entire linked list.
    coordinate_t pos;//stores the coordinates of the rock.
	vector_t vec;//stores vector which is direction and speed.
    struct rock_t* next;//stores the pointer within the node to the next node.
}rock_t;

typedef struct shot_t { //declaration for A rock/node not the entire linked list.
    coordinate_t pos;//stores the coordinates of the rock.
		vector_t vec;//stores vector which is direction and speed.
    struct shot_t* next;//stores the pointer within the node to the next node.
}shot_t;


/*struct missile {
    coordinate_t p;
    struct missile *next;
};*/

void shipTurns();
void Thrust();
void physics(void);
void createMissile(shot_t *head);//uses the linked list and passes shots to controller.
