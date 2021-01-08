#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAX_ROWS 10
#define MAX_COLS 10

typedef enum ship_name
{
DESTROYER,
SUBMARINE,
CRUISER,
BATTLESHIP,
CARRIER,
}Ship_name;

typedef enum dir
{
	VERTICAL, HORIZONTAL
} Dir;

typedef enum boolean
{
	FALSE, TRUE
}Boolean;

typedef struct ship
{
	char display; //'c''r'
	char *name;
	Boolean is_sunk;
	int length;
	int num_of_hits;
}Ship;

typedef struct cell
{
	int col; 
	int row; 
	Boolean is_occupied;
	char display;
	Ship *ship_ptr;
}Cell;

int select_who_starts_first(void);
int welcome_screen(void);
void init_board(Cell board[][MAX_COLS], int num_rows, int num_cols);
void print_board(Cell board[][MAX_COLS], int num_rows, int num_cols, int player);
void randomly_place_ship(Cell board[][MAX_COLS], Ship ship[], int player);
void manually_place_ship(Ship ship[], Cell board[][MAX_COLS], int player, int index);
void take_shot(Cell board[][MAX_COLS], Ship ship[], int player, FILE *outfile, int *hit, int *missed);
int check_ships(Ship ship[], int player);
void print_move(FILE *outfile, int row, int col, Cell board[][MAX_COLS], int player);