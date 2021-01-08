#include "head.h"

// MENU ##############################################################################################################
int welcome_screen(void)
{
	int menu = -1;


printf("*Please maximize game screen for best gaming experience*\n\n"
	"1....Print game rules\n"
	"2....Start battleship\n"
	"3....Exit\n"
	"(Please select 1, 2 or 3)\n");

scanf("%d", &menu);
system("cls");

switch (menu)
{
case 1:
	printf("The rules of battlehsip are... It is a 2 player game; you vs the computer. Each of you will have a game board and");
	printf("place 5 ships on this board. The carrier(size 5), battleship(size 4), cruiser (size 3), submarine(size 3), and destroyer(size 2).");
	printf("You will each then take turns trying to 'Hit' the other players ships on their board by selecting a point on the boards grid system.");
	printf("If you hit a spot on the grid where one of the opponents ships are, a hit will be comfirmed, if you missed, a miss will be confirmed.");
	printf("Once a player hits all the spots where the opponents ships occupy, that player WINS!!!!");
	menu = -1;
	return menu;
case 2:
	return menu;
case 3:
	printf("Good bye!");
	return 0;
default:
	printf("Please select a valid entry\n");
	menu = -1;
	return menu;
}
return menu;
}

// initialize the game boards /////////////////////////////////////////////////////////////////////////////////////////
void init_board(Cell board[][MAX_COLS], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index].display = '~';
			board[row_index][col_index].col = col_index;
			board[row_index][col_index].row = row_index;
			board[row_index][col_index].is_occupied = FALSE;
			board[row_index][col_index].ship_ptr = NULL;
		}
	}
	return 0;
}

//SELECT WHO START FIRST - Randomly ######################################################################################
int select_who_starts_first(void)
{
	return rand() % 1;
}

// PRINT BOARD ###########################################################################################################
void print_board(Cell board[][MAX_COLS], int num_rows, int num_cols, int player)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			if (row_index == 0 && col_index==0)
			{
				printf("  1 2 3 4 5 6 7 8 9 10\n");
			}

			if (col_index == 0)
			{
					printf("%c ", ('A' + row_index));
			}
			if (player==1)//printing player 1's board
			printf("%c ", board[row_index][col_index].display);
			else//printing player 2's board (not showing ships)
			{
				switch (board[row_index][col_index].display)
				{
				case 'D':
				case 'C':
				case 'R':
				case 'S':
				case 'B':
					printf("%c ", '~');
					break;
				default:
					printf("%c ", board[row_index][col_index].display);
				}
			}
		}

		putchar('\n');
	}
	putchar('\n');
	return 0;
}

 //SHIP DIRECTION ##########################################################################################################
Dir get_direction(void)
{
	Dir direction = 0;
	puts("First decide if you will want your ship to be vertical or horizontal.\n1.Vertical\n2.Horizontal (1 or 2)\n");
	scanf("%d",&direction);
	direction--;
	return direction;
}

//place ship manually///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void manually_place_ship(Ship ship[], Cell board[][MAX_COLS], int player, int manindex)
{
	char row = NULL; //a-j
	int check = -1, row_st_pt=0, col_st_pt=0, valid=0;
	Dir direction = 0;

	while (manindex >= 0)
	{
		direction = get_direction();
		puts("Please select where you would like to place your ships. (Ex. A4, B3, E6)\n"
			"Ships will start at your selected cell and either go to the right if you chose horizontal, or down for vertical");
		switch (manindex)
		{
		case 0:
			puts("Please place your Destoyer, length of 2");
			break;
		case 1:
			puts("Please place your Submarine, length of 3");
			break;
		case 2:
			puts("Please place your Cruiser, length of 3");
			break;
		case 3:
			puts("Please place your Battleship, length of 4");
			break;
		case 4:
			puts("Please place your Carrier, length of 5");
			break;
		}
		valid = 0;
		scanf(" %c%d", &row, &col_st_pt);
		col_st_pt--;
		switch (row)
		{
		case 'A':
		case 'a':
			row_st_pt = 0;
			valid = 1;
			break;
		case 'B':
		case 'b':
			row_st_pt = 1;
			valid = 1;
			break;
		case 'C':
		case 'c':
			row_st_pt = 2;
			valid = 1;
			break;
		case 'D':
		case 'd':
			row_st_pt = 3;
			valid = 1;
			break;
		case 'E':
		case 'e':
			row_st_pt = 4;
			valid = 1;
			break;
		case 'F':
		case 'f':
			row_st_pt = 5;
			valid = 1;
			break;
		case 'G':
		case 'g':
			row_st_pt = 6;
			valid = 1;
			break;
		case 'H':
		case 'h':
			row_st_pt = 7;
			valid = 1;
			break;
		case 'I':
		case 'i':
			row_st_pt = 8;
			valid = 1;
			break;
		case 'J':
		case 'j':
			row_st_pt = 9;
			valid = 1;
			break;
		default:
			puts("Please select a valid entery");
			manindex++;
			valid = 0;
			break;
		}
		check = -1;
		// check if valid choice
		if (valid == 1)
		{
			for (int check_index = 0; check==-1 && check_index < ship[manindex].length;)
			{

				if (direction == VERTICAL && board[row_st_pt + check_index][col_st_pt].is_occupied == FALSE &&
					row_st_pt <= (MAX_ROWS - ship[manindex].length + 1) && col_st_pt <= MAX_COLS)
				{
					check_index++;
					check = -1;
				}
				else if (direction == HORIZONTAL && board[row_st_pt][col_st_pt + check_index].is_occupied == FALSE &&
					row_st_pt <= MAX_ROWS && col_st_pt <= (MAX_COLS - ship[manindex].length + 1)) // horizontal
				{
					check_index++;
					check = -1;
				}
				else
				{
					check = 0;
					manindex++;
				}
			}
			if (check == -1)
			{
				for (int place_index = 0; place_index < ship[manindex].length; ++place_index)
				{


					if (direction == VERTICAL)
					{
						board[row_st_pt + place_index][col_st_pt].display = ship[manindex].display;
						board[row_st_pt + place_index][col_st_pt].is_occupied = TRUE;
						//board[row_st_pt + place_index][col_st_pt].ship_ptr = ship + manindex;
					}
					else // horizontal
					{
						board[row_st_pt][col_st_pt + place_index].display = ship[manindex].display;
						board[row_st_pt][col_st_pt + place_index].is_occupied = TRUE;
						//board[row_st_pt][col_st_pt + place_index].ship_ptr = ship + manindex;
					}
				}
			}
			system("cls");
			print_board(board, MAX_ROWS, MAX_COLS, player);
		
		}
		manindex--;
	}
	return 0;
}

// PLACE SHIP randomly ////////////////////////////////////////////////////////////////////////////////////////////////////////////
void randomly_place_ship(Cell board[][MAX_COLS], Ship ship[], int player)
{
	int index = 0, ship_index=0, row_st_pt=0, col_st_pt=0, check=-1;
	Dir direction=0;

	while (ship_index < 5)
	{
		direction = (Dir)(rand() % 2);

		if (direction == HORIZONTAL) // horizontal
		{
			row_st_pt = rand() % MAX_ROWS; // 0 - 9
			col_st_pt = rand() % (MAX_COLS - ship[ship_index].length + 1);
		}
		else // vertical
		{
			row_st_pt = rand() % (MAX_ROWS - ship[ship_index].length + 1);
			col_st_pt = rand() % MAX_COLS; // 0 - 9
		}
//CHECK to make sure these points wont hit occupied areas//////////////////////////////
		for (index = 0, check=-1; index < ship[ship_index].length;)
		{

			if (direction == VERTICAL && board[row_st_pt + index][col_st_pt].is_occupied == FALSE)
			{
				index++;
			}
			else if (direction == HORIZONTAL && board[row_st_pt][col_st_pt + index].is_occupied == FALSE) // horizontal
			{
				index++;
			}
			else
			{
				index = ship_index + 1;
				check = 0;
				ship_index--;
			}
		}

		if (check == -1)
		{
			for (index = 0; index < ship[ship_index].length; ++index)
			{


				if (direction == VERTICAL)
				{
					board[row_st_pt + index][col_st_pt].display = ship[ship_index].display;
					board[row_st_pt + index][col_st_pt].is_occupied = TRUE;
					board[row_st_pt + index][col_st_pt].ship_ptr = ship + ship_index;
				}
				else // horizontal
				{
					board[row_st_pt][col_st_pt + index].display = ship[ship_index].display;
					board[row_st_pt][col_st_pt + index].is_occupied = TRUE;
					board[row_st_pt][col_st_pt + index].ship_ptr = ship + ship_index;

				}
			}
		}
		ship_index++;
	}
	return 0;
}


// INITIALIZE SHIP ##############################################################################################################
void init_ship(Ship ship[])
{
	
	
	ship[DESTROYER].display='D';
	ship[DESTROYER].length=2;
	ship[DESTROYER].name = "Destroyer";
	ship[DESTROYER].num_of_hits=0;
	ship[DESTROYER].is_sunk = FALSE;
	
	ship[SUBMARINE].display='S';
	ship[SUBMARINE].length=3;
	ship[SUBMARINE].name="Submarine";
	ship[SUBMARINE].num_of_hits=0;
	ship[SUBMARINE].is_sunk = FALSE;

	ship[CRUISER].display='R';
	ship[CRUISER].length=3;
	ship[CRUISER].name="Cruiser";
	ship[CRUISER].num_of_hits=0;
	ship[CRUISER].is_sunk = FALSE;

	ship[BATTLESHIP].display='B';
	ship[BATTLESHIP].length=4;
	ship[BATTLESHIP].name="Battleship";
	ship[BATTLESHIP].num_of_hits=0;
	ship[BATTLESHIP].is_sunk = FALSE;

	ship[CARRIER].display='C';
	ship[CARRIER].length=5;
	ship[CARRIER].name="Carrier";
	ship[CARRIER].num_of_hits=0;
	ship[CARRIER].is_sunk = FALSE;
	return 0;

}

//take shots at eachothers boards//////////////////////////////////////////////////////////////////////////////////////

void take_shot(Cell board[][MAX_COLS], Ship ship[], int player, FILE *outfile, int *hit, int *missed)
{
	int row = 0, col = 0;
	char rowc = NULL;

	if (player == 2)
	{
		row = rand() % MAX_ROWS;
		col = rand() % MAX_COLS;
	}
	else //player 1, choose shots
	{
		puts("Please select where you would like to take a shot. (Ex. A2, B4, etc) \n");
		scanf(" %c%d", &rowc, &col);
		col--;

		switch (rowc)
		{
		case 'A':
		case 'a':
			row = 0;
			break;
		case 'B':
		case 'b':
			row = 1;
			break;
		case 'C':
		case 'c':
			row = 2;
			break;
		case 'D':
		case 'd':
			row = 3;
			break;
		case 'E':
		case 'e':
			row = 4;
			break;
		case 'F':
		case 'f':
			row = 5;
			break;
		case 'G':
		case 'g':
			row = 6;
			break;
		case 'H':
		case 'h':
			row = 7;
			break;
		case 'I':
		case 'i':
			row = 8;
			break;
		case 'J':
		case 'j':
			row = 9;
			break;
		default:
			puts("Please select a valid entery");
			take_shot(board, ship, player, outfile, hit, missed);
			break;
		}
	}
	print_move(outfile, row, col, board, player);

	switch (board[row][col].display)
	{
	case '~':
		system("cls");
		if (player == 1)
			puts("You missed the target!");
		board[row][col].display = 'M';
		*missed+= 1;
		break;
	case 'X':
		if (player == 1)
		{
			puts("You already hit that spot.\n");
			puts("Please select a different spot.\n");
		}
		take_shot(board, ship, player, outfile, hit, missed);
		break;
	case 'M':
		if (player == 1)
		{
			puts("You already missed that spot.\n");
			puts("Please select a different spot.\n");
	    }
		take_shot(board, ship, player, outfile, hit, missed);
		break;
	case 'D':
		system("cls");
		*hit += 1;
		if (player==1)
		puts("You hit the enemy Destroyer!");
		board[row][col].display = 'X';
		ship[DESTROYER].num_of_hits += 1;
		if (ship[DESTROYER].num_of_hits == 2)//sunk
		{
			if (player==1)
			puts("You sunk the enemy destroyer!");
			ship[DESTROYER].is_sunk = TRUE;
		}
		break;
	case 'R':
		system("cls");
		*hit += 1;
		if(player==1)
		puts("You hit the enemy Cruiser!");
		board[row][col].display = 'X';
		ship[CRUISER].num_of_hits += 1;
		if (ship[CRUISER].num_of_hits == 3) //sunk
		{
			ship[CRUISER].is_sunk = TRUE;
			if(player==1)
			puts("You sunk the enemy cruiser!");
		}
		break;
	case 'B':
		*hit += 1;
		system("cls");
		if(player==1)
		puts("You hit the enemy Battleship!");
		board[row][col].display = 'X';
		ship[BATTLESHIP].num_of_hits += 1;
		if (ship[BATTLESHIP].num_of_hits == 4) //sunk
		{
			ship[BATTLESHIP].is_sunk = TRUE;
			if (player==1)
			puts("You sunk the enemy battleship!");
		}
		break;
	case 'C':
		*hit += 1;
		system("cls");
		if (player == 1)
		puts("You hit the enemy Carrier!");
		board[row][col].display = 'X';
		ship[CARRIER].num_of_hits += 1;
		if (ship[CARRIER].num_of_hits == 5) //sunk
		{
			ship[CARRIER].is_sunk = TRUE;
			if (player == 1)
			puts("You sunk the enemy carrier!");
		}
		break;
	case 'S':
		*hit += 1;
		system("cls");
		if (player == 1)
		puts("You hit the enemy Submarine!");
		board[row][col].display = 'X';
		ship[SUBMARINE].num_of_hits += 1;
		if (ship[SUBMARINE].num_of_hits == 3) //sunk
		{
			ship[SUBMARINE].is_sunk = TRUE;
			if (player == 1)
			puts("You sunk the enemy submarine!");
		}
		break;
	}
	return 0;
}

//check if all ships are sunk and if someone has won////////////////////////////////////////////////////////////////
int check_ships(Ship ship[], int player)
{
	int des = 0, sub = 0, cru = 0, bat = 0, car = 0, win=0;

	if (ship[DESTROYER].num_of_hits == 2)//sunk
	{
		des = 1;
	}

	if (ship[SUBMARINE].num_of_hits == 3) //sunk
	{
		sub = 1;
	}
	if (ship[CRUISER].num_of_hits == 3) //sunk
	{
		cru = 1;
	}
	if (ship[BATTLESHIP].num_of_hits == 4) //sunk
	{
		bat = 1;
	}
	if (ship[CARRIER].num_of_hits == 5) //sunk
	{
		car = 1;
	}
	
	if (car == 1 && bat == 1 && cru == 1 && sub == 1 && des == 1)
	{
		if (player == 1)
		{
			puts("You win!");
			puts("All the enemy ships have been taken out!");
			win = 1;
		}
		else
		{
			puts("Player 2 wins!");
			puts("They sunk all of your ships! Wow!");
			win = 1;
		}
	}
	return win;
}


//print moves/////////////////////////////////////////////////////////////////////////////////////////////////
void print_move(FILE *outfile, int row, int col, Cell board[][MAX_COLS], int player)
{
	if (board[row][col].display == 'M' || board[row][col].display=='X')
		return 0;
	else
	fprintf(outfile, "player%d (%d,%d) hit %c\n",player,row,col,board[row][col].display);
	return 0;
}