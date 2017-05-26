#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	_Bool hasRobot; // 1 (true) a robot is here; 0 (false) the space is clear
	int robHeading; // 0 (west), 1 (north), 2 (east), 3 (south)
	_Bool robAlive; // 1 (true) for running robot; (false) when crashed
} gridSquare;

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	// The 10 by 10 grid
	gridSquare grid[10][10];
	int m,n;
	for (m=0; m<10; m++) {
		for (n=0; n<10; n++) {
			grid[m][n].hasRobot=0;
		}
	}
	// TODO: initialize the grid using a nested loop so there are no robots (DONE)

	int i;
	int row, column;

	// Add 10 robots to the grid
	for (i = 0; i < 10; i++) {

		// This makes sure that the grid space is currently empty
		do {
			row = rand() % 10;
			column = rand() % 10;
		} while (grid[row][column].hasRobot);
		grid[row][column].hasRobot=1;
		grid[row][column].robHeading=rand()%4;
		grid[row][column].robAlive=1;
		// TODO:  Randomly set the heading at (column,row),
		//        and make the robot alive (DONE)
	}

	// Counts the number of live robots
	int liveCount = 10;

	// main loop of the game
	do {
		int a,b;
		for(a=0; a<10; a++) {
			for(b=0; b<10; b++) {
				if (grid[a][b].hasRobot==1 && grid[a][b].robAlive==1){
					printf("R");
				} else if (grid[a][b].hasRobot==1 && grid[a][b].robAlive!=1){
					printf("@");
				} else if (grid[a][b].hasRobot==0){
					printf(".");
				}
			}
			printf("\n");
		}
		// TODO: Output the grid  (DONE)

		char cmd;

		// Obtain user input (move or rotate command)
		printf("\n input action and coordinates, please: ");
		scanf(" %c %i %i", &cmd, &row, &column);

		// Process user command
		if (grid[row][column].hasRobot && grid[row][column].robAlive) {

			if (cmd == 'L') {
				switch (grid[row][column].robHeading) {

			case 0: // Pointing west
				grid[row][column].robHeading=3;
				break;

			case 1: // Pointing north
				grid[row][column].robHeading=0;
				break;

			case 2: // Pointing east
				grid[row][column].robHeading=1;
				break;

			case 3: // Pointing south
				grid[row][column].robHeading=2;
				break;

			default: // Shouldn't happen
				break;
		}

				// TODO: Update the heading accordingly (DONE)

			} else if (cmd == 'R') {
				switch (grid[row][column].robHeading) {

			case 0: // Pointing west
				grid[row][column].robHeading=1;
				break;

			case 1: // Pointing north
				grid[row][column].robHeading=2;
				break;

			case 2: // Pointing east
				grid[row][column].robHeading=3;
				break;

			case 3: // Pointing south
				grid[row][column].robHeading=0;
				break;

			default: // Shouldn't happen
				break;
		}
				// TODO: Update the heading accordingly (DONE)

			} else if (cmd == 'F') {

				// This attempts to move the robot forward, depending on the
				// direction it is currently pointing
				switch (grid[row][column].robHeading) {

					case 0: // Pointing west
						if (column > 0) {
							if (grid[row][column-1].hasRobot) {
								if (grid[row][column-1].robAlive) {
									liveCount = liveCount - 2;
								} else {
									liveCount = liveCount - 1;
								}
								grid[row][column].robAlive=0;
								grid[row][column-1].robAlive=0;
							} else {
								grid[row][column].hasRobot=0;
								grid[row][column-1].hasRobot=1;
								grid[row][column-1].robAlive=1;
								grid[row][column-1].robHeading=grid[row][column].robHeading;
							}
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward (DONE)
						}
						break;

					case 1: // Pointing north
						if (row > 0) {
							if (grid[row-1][column].hasRobot) {
								if (grid[row-1][column].robAlive) {
								liveCount = liveCount - 2;
							} else {
								liveCount = liveCount - 1;
							}
							grid[row][column].robAlive=0;
							grid[row-1][column].robAlive=0;
						} else {
							grid[row][column].hasRobot=0;
							grid[row-1][column].hasRobot=1;
							grid[row-1][column].robAlive=1;
							grid[row-1][column].robHeading=grid[row][column].robHeading;
						}
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward (DONE)
						}
						break;

					case 2: // Pointing east
						if (column < 9) {
							if (grid[row][column+1].hasRobot) {
								if (grid[row][column+1].robAlive) {
								liveCount = liveCount - 2;
							} else {
								liveCount = liveCount - 1;
							}
							grid[row][column].robAlive=0;
							grid[row][column+1].robAlive=0;
						} else {
							grid[row][column].hasRobot=0;
							grid[row][column+1].hasRobot=1;
							grid[row][column+1].robAlive=1;
							grid[row][column+1].robHeading=grid[row][column].robHeading;
						}
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward (DONE)
						}
						break;

					case 3: // Pointing south
						if (row < 9) {
							if (grid[row+1][column].hasRobot) {
								if (grid[row+1][column].robAlive) {
								liveCount = liveCount - 2;
							} else {
								liveCount = liveCount - 1;
							}
							grid[row][column].robAlive=0;
							grid[row+1][column].robAlive=0;
						} else {
							grid[row][column].hasRobot=0;
							grid[row+1][column].hasRobot=1;
							grid[row+1][column].robAlive=1;
							grid[row+1][column].robHeading=grid[row][column].robHeading;
						}
							// TODO: If a robot is in front of you, crash both;
							// otherwise move the robot forward (DONE)
						}
						break;

					default: // Shouldn't happen
						break;
				}

			}

		}

	} while (liveCount >= 0);

	return 0;
}


