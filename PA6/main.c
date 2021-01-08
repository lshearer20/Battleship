/*
///////(((((((((((((((((((((((((((((((AFter i submitted, it asked me if i wanted to save changes, so wasnt sure what was sent in)))))))))))))))))))))
Lucas Shearer
WSUID: 10956939
Cpts 121- 04L- TA: Hannah
PA6

Function: Our main function that runs the program
Date created:11/10/17
Last modified:Today
Description: This is our main file for our program
Input parameters: na
Return: 0
Preconditions: Visual Studios
Postconditions: Executes without errors
*/

#include "head.h"

int main(void)
{
	FILE *outfile = NULL;
	outfile = fopen("output.txt", "w");
	Cell p1_board[MAX_ROWS][MAX_COLS];
	Cell p2_board[MAX_ROWS][MAX_COLS];
	Ship p1_ship[5];
	Ship p2_ship[5];

	srand((unsigned int)time(NULL));

	int manindex=4, start = -1, col_st_pt = 0, row_st_pt = 0, menu = -1, win1 = 0, win2 = 0, player1 = 1, player2 = 2, man_or_ran = 2, playagain = -1, *p1_hit = 0, *p1_missed = 0, *p2_hit = 0, *p2_missed = 0;

// MENU ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (menu == -1)
	menu = welcome_screen();
	if (menu == 0)
	{
		return 0;
	}
	if (menu == 2)
	{
// initialize/ print initial boards players boards /////////////////////////////////////////////////////////
		init_board(p1_board, MAX_ROWS, MAX_COLS);
		init_ship(p1_ship);
		init_board(p2_board, MAX_ROWS, MAX_COLS);
		init_ship(p2_ship);
		print_board(p1_board, MAX_ROWS, MAX_COLS,player1);
		print_board(p2_board, MAX_ROWS, MAX_COLS,player2);
		putchar('\n');
		puts("Would you like to randomly place your ships or would you rather place them yourself?\n1.Place your own ships.\n2.Randomly place ships.\n");
		scanf("%d", &man_or_ran);

		switch (man_or_ran)
		{
		case 1://manually place ships ///////////////////////////////////////////////////////////////////////////////
			manually_place_ship(p1_ship, p1_board, player1, manindex);
			break;
		case 2://randomlly place player 1 ships//////////////////////////////////////////////////////////////////////////////
			randomly_place_ship(p1_board, p1_ship, player1);
			break;
		}

//place player 2 random ships /////////////////////////////////////////////////////////////////////
		randomly_place_ship(p2_board, p2_ship, player2);
		system("cls");
//show boards of random ships////////////////////////////////////////////////////////////
		print_board(p2_board, MAX_ROWS, MAX_COLS, player2);
		print_board(p1_board, MAX_ROWS, MAX_COLS, player1);
// Computer random shots ////////////////////////////////////////////////////////////////
		start = select_who_starts_first();
		while (win1 == 0 && win2 == 0)
		{
			switch (start)
			{
			case 0:
				//player 1 turn
				take_shot(p2_board, p2_ship, player1, outfile, &p1_hit, &p1_missed);
				win1 = check_ships(p2_ship, player1);
				print_board(p2_board, MAX_ROWS, MAX_COLS, player2);
				print_board(p1_board, MAX_ROWS, MAX_COLS, player1);

			case 1:
				printf("Its the computers turn now, press any key to continue");
				getch();
				//player 2 computer turn
				take_shot(p1_board, p1_ship, player2, outfile, &p2_hit, &p2_missed);
				win2 = check_ships(p1_ship, player2);
				print_board(p2_board, MAX_ROWS, MAX_COLS, player2);
				print_board(p1_board, MAX_ROWS, MAX_COLS, player1);
			}
		}
	}
	//print some stuff///////////////////////////////////////////////////////////////
	fprintf(outfile, "player 1 hit %d shots\n", p1_hit);
	fprintf(outfile, "player 1 missed %d shots\n", p1_missed);
	fprintf(outfile, "player 2 hit %d shots\n", p2_hit);
	fprintf(outfile, "player 2 missed %d shots\n", p2_missed);

	printf("Would you like to play again?\n1.Yes\n2.No\n");
	scanf("%d", &playagain);
	if (playagain == 1)
	{
		main();
	}
	else
	{
		fclose(outfile);
		return 0;
	}
}
