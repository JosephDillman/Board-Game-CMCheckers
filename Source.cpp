//Code written by Joseph Dillman and Gun Min (Richard) Song. CMPT128 D200 assignment 2
//This code is designed to play a game of CMcheckers 
//Last edited on December 5, 2016
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Declare and initialize all global constants, then display function prototypes
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);
void lastrow(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
//bool CheckList(int inArray1[], int inArray2[], int xIndex, int yindex);



int main()
{
	//declare and initialize all main variables
	int numrowsboard = 0;
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };
	int xIndiciesMove[MAX_PIECES] = { 0 };
	int yIndiciesMove[MAX_PIECES] = { 0 };
	int xIndiciesJump[MAX_PIECES] = { 0 };
	int yIndiciesJump[MAX_PIECES] = { 0 };
	int count = 0;
	int player = 1;
	int turn = 1;
	int num1 = 0;
	int num2 = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	char word[1024] = { '0' };
	int jumpablenum[1024] = { '0' };
	bool jump = false;
	//prompt user to enter the size of the board, allow a max three tries if input is incorrect

	for (int count = 0; count<10; count++)
	{
		if (count >= 3)
		{
			cerr << "ERROR:  Too many errors entering the size of the board";
			return(1);
		}
		cout << "Enter the number of squares along each edge of the board ";
		cout << endl;
		if (!(cin >> numrowsboard))
		{
			cerr << "ERROR:  Board size is not an integer";
			cerr << endl << "8 <= number of squares <= 18" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		if (numrowsboard < 8)
		{
			cerr << "ERROR:  Board size too small";
			cerr << endl << "8 <= number of squares <= 18" << endl;
			continue;
		}
		if (numrowsboard > 18)
		{
			cerr << "ERROR:  Board size too large";
			cerr << endl << "8 <= number of squares <= 18" << endl;
			continue;
		}
		if (numrowsboard % 2 != 0)
		{
			cerr << "ERROR:  Board size odd";
			cerr << endl << "8 <= number of squares <= 18" << endl;
			continue;
		}
		break;
	}
	InitializeBoard(myCMCheckersBoard, numrowsboard);
	DisplayBoard(myCMCheckersBoard, numrowsboard);
	//set a long counter to repeat the next tests for each alternating turn 
	for (int x = 0; x <1024; x++)
	{
		if (CountJumps(myCMCheckersBoard, numrowsboard, player, xIndiciesJump, yIndiciesJump) == 0 && CountMove1Squares(myCMCheckersBoard, numrowsboard, player, xIndiciesJump, yIndiciesJump) == 0)
		{
			if (player == WHITEPLAYER)
			{
				cout << "White is unable to move" << endl << "GAME OVER, Red has won" << endl << "Enter any character to close the game";
				cin >> word;
				exit(1);
			}
			else if (player == REDPLAYER)
			{
				cout << "Red is unable to move" << endl << "GAME OVER, White has won" << endl << "Enter any character to close the game";
				cin >> word;
				exit(1);
			}
		}
		else
		{
			if (player == WHITEPLAYER)
			{
				cout << "White takes a turn" << endl;
			}
			else if (player == REDPLAYER)
			{
				cout << "Red takes a turn" << endl;
			}
			for (int x = 0; x<1000; x++) //ensure that the checker selected by the player is usable 
			{
				cout << "Enter the square number of the checker you want to move" << endl;
				if (!(cin >> num1))
				{
					cerr << "ERROR:  you did not enter an integer" << endl;
					cerr << "Try again" << endl;
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				if (num1 < 0 || num1 >(numrowsboard*numrowsboard) - 1)
				{
					cerr << "ERROR:  that square is not on the board." << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == 0)
				{
					cerr << "ERROR:  that square is empty" << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (player == WHITEPLAYER)
				{
					if (myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == REDMULE || myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == REDSOLDIER || myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == REDKING)
					{
						cerr << "ERROR:  that square contains an opponent's checker" << endl;
						cerr << "Try again" << endl;
						continue;
					}
				}
				else if (player == REDPLAYER)
				{
					if (myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == WHITEMULE || myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == WHITESOLDIER || myCMCheckersBoard[num1 / numrowsboard][num1%numrowsboard] == WHITEKING)
					{
						cerr << "ERROR:  that square contains an opponent's checker" << endl;
						cerr << "Try again" << endl;
						continue;
					}
				}
				if (IsJump(myCMCheckersBoard, numrowsboard, player, num1%numrowsboard, num1 / numrowsboard) == false && CountJumps(myCMCheckersBoard, numrowsboard, player, xIndiciesJump, yIndiciesJump) > 0)
				{
					for (int y = 0; y < numrowsboard; y++)
					{
						for (int x = 0; x < numrowsboard; x++)
						{
							if (IsJump(myCMCheckersBoard, numrowsboard, player, x, y) == true)
							{
								jumpablenum[count] = numrowsboard*y + x;
								count++;
							}
						}
					}
					cerr << "ERROR: You can jump with another checker, you may not move your chosen checker" << endl;
					cerr << "You can jump using checkers on the following squares:";
					for (int g = 0; g < count; g++)
					{
						cout << " ";
						cout << jumpablenum[g];
					}
					cout << endl;
					cerr << "Try again" << endl;
					continue;
				}
				if (IsJump(myCMCheckersBoard, numrowsboard, player, num1%numrowsboard, num1 / numrowsboard) == false && IsMove1Square(myCMCheckersBoard, numrowsboard, player, num1%numrowsboard, num1 / numrowsboard) == false)
				{
					cerr << "ERROR: There is no legal move for this checker" << endl;
					cerr << "Try again" << endl;
					continue;
				}
				for (int x = 0; x<1000; x++)
				{
					cout << "Enter the square number of the square you want to move your checker to" << endl;
					if (!(cin >> num2))
					{
						cerr << "ERROR:  you did not enter an integer" << endl;
						cerr << "Try again" << endl;
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					if (num2 < 0 || num2 >(numrowsboard*numrowsboard) - 1)
					{
						cerr << "ERROR:  that square is not on the board." << endl;
						cerr << "Try again" << endl;
						continue;
					}
					if (myCMCheckersBoard[num2 / numrowsboard][num2%numrowsboard] != 0)
					{
						cerr << "ERROR:  It is not possible to move to a square that is already occupied" << endl;
						cerr << "Try again" << endl;
						continue;
					}
					if (IsJump(myCMCheckersBoard, numrowsboard, player, num1%numrowsboard, num1 / numrowsboard) == true && abs((num1 / numrowsboard) - (num2 / numrowsboard)) != 2)
					{
						cerr << "ERROR:  You can jump with this checker, you must jump not move 1 space" << endl;
						cerr << "Try again" << endl;
						continue;
					}
					break;
				}
				break;
			}
			if (MakeMove(myCMCheckersBoard, numrowsboard, player, num1, num2, jump) == false)
			{
				cerr << "ERROR: moving to that square is not legal, Try again" << endl;
				continue;
			}
			while (jump == true)
			{
				if (IsJump(myCMCheckersBoard, numrowsboard, player, num2%numrowsboard, num2 / numrowsboard) == true)
				{
					num1 = num2;
					for (int x = 0; x < 1024; x++)
					{
						cout << "You can jump again,  Please enter the next square you wish to move your checker to" << endl;
						if (!(cin >> num2))
						{
							cerr << "ERROR:  you did not enter an integer" << endl;
							cerr << "Try again" << endl;
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						if (num2 < 0 || num2 >(numrowsboard*numrowsboard) - 1)
						{
							cerr << "ERROR:  that square is not on the board." << endl;
							cerr << "Try again" << endl;
							continue;
						}
						if (myCMCheckersBoard[num2 / numrowsboard][num2%numrowsboard] != 0)
						{
							cerr << "ERROR:  It is not possible to move to a square that is already occupied" << endl;
							cerr << "Try again" << endl;
							continue;
						}
						if (IsJump(myCMCheckersBoard, numrowsboard, player, num1%numrowsboard, num1 / numrowsboard) == true && abs((num1 / numrowsboard) - (num2 / numrowsboard)) != 2)
						{
							cerr << "ERROR:  You can jump with this checker, you must jump not move 1 space" << endl;
							cerr << "Try again" << endl;
							continue;
						}
						if (MakeMove(myCMCheckersBoard, numrowsboard, player, num1, num2, jump) == false)
						{
							cerr << "ERROR: moving to that square is not legal, Try again" << endl;
							continue;
						}
						else
							break;
					}
					break;
				}
				break;
			}
			DisplayBoard(myCMCheckersBoard, numrowsboard);
			if (CheckWin(myCMCheckersBoard, numrowsboard) == true)
			{
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				if (cin >> word)
				{
					exit(1);
				}
			}
		}
		if (player == 1)
		{
			player = 2;
		}
		else if (player == 2)
		{
			player = 1;
		}
	}



	return(0);
}


//FUNCTION DEFINITIONS
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//fill board with starting pieces with rows (y) and columns (x) with respect to numRowsInBoard
	//begin with two for loops declaring (y) and (x) variables of the 2D array
	int x = 0;
	int y = 0;
	for (y = 0; y < numRowsInBoard; y++)
	{
		for (x = 0; x < numRowsInBoard; x++)
		{
			//if the row (y) is the first row in the gameboard (top of board), initialize to {0, 2, 0, 2...}
			if (y == 0)
			{
				if (x == 0)
				{
					CMCheckersBoard[y][x] = NOPLAYER;
				}
				else if (x % 2 == 0)
				{
					CMCheckersBoard[y][x] = NOPLAYER;
				}
				else if (x % 2 != 0)
				{
					CMCheckersBoard[y][x] = WHITEMULE;
				}
			}
			//if the row (y) is not the first row but is a row less than the two middle rows in the board, initialize
			else if (y < (numRowsInBoard / 2) - 1)
			{
				//if even, initialize to {0, 1, 0, 1...}
				if (y % 2 == 0)
				{
					if (x % 2 == 0)
					{
						CMCheckersBoard[y][x] = NOPLAYER;
					}
					else if (x % 2 != 0)
					{
						CMCheckersBoard[y][x] = WHITESOLDIER;
					}
				}
				//if the row (y) is an odd number, initialize to {1, 0, 1, 0...}
				else if (y % 2 != 0)
				{
					if (x % 2 == 0)
					{
						CMCheckersBoard[y][x] = WHITESOLDIER;
					}
					else if (x % 2 != 0)
					{
						CMCheckersBoard[y][x] = NOPLAYER;
					}
				}
			}
			//if the row (y) is the last row of the board, initialize to {5, 0, 5, 0...}
			else if (y == (numRowsInBoard - 1))
			{
				if (x == 0)
				{
					CMCheckersBoard[y][x] = REDMULE;
				}
				else if (x % 2 == 0)
				{
					CMCheckersBoard[y][x] = REDMULE;
				}
				else if (x % 2 != 0)
				{
					CMCheckersBoard[y][x] = NOPLAYER;
				}
			}
			//if the row (y) is not the last row but is a row greater than the two middle rows in the board, initialize
			else if (y > (numRowsInBoard / 2))
			{
				//if the row (y) is an even number, initialize to {0, 4, 0, 4...}
				if (y % 2 == 0)
				{
					if (x % 2 == 0)
					{
						CMCheckersBoard[y][x] = NOPLAYER;
					}
					else if (x % 2 != 0)
					{
						CMCheckersBoard[y][x] = REDSOLDIER;
					}
				}
				//if odd, initialize to {4, 0, 4, 0...}
				else if (y % 2 != 0)
				{
					if (x % 2 == 0)
					{
						CMCheckersBoard[y][x] = REDSOLDIER;
					}
					else if (x % 2 != 0)
					{
						CMCheckersBoard[y][x] = NOPLAYER;
					}
				}
			}
			//the middle (y) rows are initialized to {0, 0, 0, 0...}
			else if (y == (numRowsInBoard / 2) || y == (numRowsInBoard / 2) - 1)
			{
				CMCheckersBoard[y][x] = NOPLAYER;
			}
		}
	}
}

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//print out the board while giving player pieces and empty spaces proper names
	int count = 0;
	for (int y = 0; y < numRowsInBoard; y++)
	{
		cout << endl;
		for (int x = 0; x < numRowsInBoard; x++)
		{
			if (CMCheckersBoard[y][x] == WHITESOLDIER)
			{
				cout << setw(4) << "WS";
			}
			else if (CMCheckersBoard[y][x] == WHITEMULE)
			{
				cout << setw(4) << "WM";
			}
			else if (CMCheckersBoard[y][x] == WHITEKING)
			{
				cout << setw(4) << "WK";
			}
			else if (CMCheckersBoard[y][x] == REDSOLDIER)
			{
				cout << setw(4) << "RS";
			}
			else if (CMCheckersBoard[y][x] == REDMULE)
			{
				cout << setw(4) << "RM";
			}
			else if (CMCheckersBoard[y][x] == REDKING)
			{
				cout << setw(4) << "RK";
			}
			else
			{
				cout << setw(4) << count;
			}
			count += 1;
		}
	}
	cout << endl << endl << endl << endl;
}

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	//this function counts number of checkers which can "jump" at specific turn.
	bool TrueOrFalse = false;
	int count = 0;
	for (int i = 0; i<numRowsInBoard; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}
	for (int x = 0; x<numRowsInBoard; x++)
	{
		for (int y = 0; y<numRowsInBoard; y++)
		{
			TrueOrFalse = IsJump(CMCheckersBoard, numRowsInBoard, player, y, x);
			if (TrueOrFalse == true)
				count++;
		}
	}
	return count;
}

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	//this function decides whether a specific checker can make a jump
	bool moveFL = false; //forward;left
	bool moveFR = false; //forward;right
	bool moveBL = false; //backward;left
	bool moveBR = false; //backward;right
	bool TrueOrFalse = false;
	if (player == 1) //white's turn
	{
		if (CMCheckersBoard[yLoc][xLoc] == 4 || CMCheckersBoard[yLoc][xLoc] == 5 || CMCheckersBoard[yLoc][xLoc] == 6 || CMCheckersBoard[yLoc][xLoc] == 0) //considering red checker
		{
			TrueOrFalse = false;
		}
		else //considering white checker
		{
			if (xLoc<numRowsInBoard - 2)// forward; non-cylindrical; left
			{
				if ((CMCheckersBoard[yLoc + 1][xLoc + 1] == 4 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 5 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 6) && (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
					moveFL = true;
				else
					moveFL = false;
			}
			else if (xLoc == numRowsInBoard - 2)//forward; cylindrical; left
			{
				if ((CMCheckersBoard[yLoc + 1][xLoc + 1] == 4 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 5 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 6) && (CMCheckersBoard[yLoc + 2][0] == 0))
					moveFL = true;
				else
					moveFL = false;
			}
			else//forward; cylindrical; left
			{
				if ((CMCheckersBoard[yLoc + 1][0] == 4 || CMCheckersBoard[yLoc + 1][0] == 5 || CMCheckersBoard[yLoc + 1][0] == 6) && (CMCheckersBoard[yLoc + 2][1] == 0))
					moveFL = true;
				else
					moveFL = false;
			}
			if (xLoc>1) //forward; non-cylindrical; right
			{
				if ((CMCheckersBoard[yLoc + 1][xLoc - 1] == 4 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 5 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 6) && (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
					moveFR = true;
				else
					moveFR = false;
			}
			else if (xLoc == 1) //forward; cylindrical; right
			{
				if ((CMCheckersBoard[yLoc + 1][xLoc - 1] == 4 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 5 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 6) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0))
					moveFR = true;
				else
					moveFR = false;
			}
			else //forward; cylindrical; right
			{
				if ((CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 4 || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 5 || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 6) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0))
					moveFR = true;
				else
					moveFR = false;
			}
			if (moveFR == true || moveFL == true)
				TrueOrFalse = true;
			if (CMCheckersBoard[yLoc][xLoc] == 3)//when the checker is king
			{
				if (xLoc<numRowsInBoard - 2)// backward; non-cylindrical; left
				{
					if ((CMCheckersBoard[yLoc - 1][xLoc + 1] == 4 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 5 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 6) && (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
						moveBL = true;
					else
						moveBL = false;
				}
				else if (xLoc == numRowsInBoard - 2)//backward; cylindrical; left
				{
					if ((CMCheckersBoard[yLoc - 1][xLoc + 1] == 4 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 5 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 6) && (CMCheckersBoard[yLoc - 2][0] == 0))
						moveBL = true;
					else
						moveBL = false;
				}
				else//backward; cylindrical; left
				{
					if ((CMCheckersBoard[yLoc - 1][0] == 4 || CMCheckersBoard[yLoc - 1][0] == 5 || CMCheckersBoard[yLoc - 1][0] == 6) && (CMCheckersBoard[yLoc - 2][1] == 0))
						moveBL = true;
					else
						moveBL = false;
				}
				if (xLoc>1) //backward; non-cylindrical; right
				{
					if ((CMCheckersBoard[yLoc - 1][xLoc - 1] == 4 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 5 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 6) && (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
						moveBR = true;
					else
						moveBR = false;
				}
				else if (xLoc == 1) //backward; cylindrical; right
				{
					if ((CMCheckersBoard[yLoc - 1][xLoc - 1] == 4 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 5 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 6) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
						moveBR = true;
					else
						moveBR = false;
				}
				else //backward; cylindrical; right
				{
					if ((CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 4 || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 5 || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 6) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0))
						moveBR = true;
					else
						moveBR = false;
				}
				if (moveBL == true || moveBR == true)
					TrueOrFalse = true;
				else
					TrueOrFalse = false;
			}
		}
	}
	else //red's turn
	{
		if (CMCheckersBoard[yLoc][xLoc] == 1 || CMCheckersBoard[yLoc][xLoc] == 2 || CMCheckersBoard[yLoc][xLoc] == 3 || CMCheckersBoard[yLoc][xLoc] == 0) //considering white checker
		{
			TrueOrFalse = false;
		}
		else //considering red checker
		{
			if (xLoc<numRowsInBoard - 2)// forward; non-cylindrical; right
			{
				if ((CMCheckersBoard[yLoc - 1][xLoc + 1] == 1 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 2 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 3) && (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0))
					moveFR = true;
				else
					moveFR = false;
			}
			else if (xLoc == numRowsInBoard - 2)//forward; cylindrical; right
			{
				if ((CMCheckersBoard[yLoc - 1][xLoc + 1] == 1 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 2 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 3) && (CMCheckersBoard[yLoc - 2][0] == 0))
					moveFR = true;
				else
					moveFR = false;
			}
			else//forward; cylindrical; right
			{
				if ((CMCheckersBoard[yLoc - 1][0] == 1 || CMCheckersBoard[yLoc - 1][0] == 2 || CMCheckersBoard[yLoc - 1][0] == 3) && (CMCheckersBoard[yLoc - 2][1] == 0))
					moveFR = true;
				else
					moveFR = false;
			}
			if (xLoc>1) //forward; non-cylindrical; left
			{
				if ((CMCheckersBoard[yLoc - 1][xLoc - 1] == 1 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 2 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 3) && (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0))
					moveFL = true;
				else
					moveFL = false;
			}
			else if (xLoc == 1) //forward; cylindrical; left
			{
				if ((CMCheckersBoard[yLoc - 1][xLoc - 1] == 1 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 2 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 3) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
					moveFL = true;
				else
					moveFL = false;
			}
			else //forward; cylindrical; left
			{
				if ((CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 1 || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 2 || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 3) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0))
					moveFL = true;
				else
					moveFL = false;
			}
			if (moveFR == true || moveFL == true)
				TrueOrFalse = true;
			if (CMCheckersBoard[yLoc][xLoc] == 6) //if the checker is king
			{
				if (xLoc<numRowsInBoard - 2)// backward; non-cylindrical; right
				{
					if ((CMCheckersBoard[yLoc + 1][xLoc + 1] == 1 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 2 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 3) && (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0))
						moveBR = true;
					else
						moveBR = false;
				}
				else if (xLoc == numRowsInBoard - 2)//backward; cylindrical; right
				{
					if ((CMCheckersBoard[yLoc + 1][xLoc + 1] == 1 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 2 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 3) && (CMCheckersBoard[yLoc + 2][0] == 0))
						moveBR = true;
					else
						moveBR = false;
				}
				else//backward; cylindrical; right
				{
					if ((CMCheckersBoard[yLoc + 1][0] == 1 || CMCheckersBoard[yLoc + 1][0] == 2 || CMCheckersBoard[yLoc + 1][0] == 3) && (CMCheckersBoard[yLoc + 2][1] == 0))
						moveBR = true;
					else
						moveBR = false;
				}
				if (xLoc>1) //backward; non-cylindrical; left
				{
					if ((CMCheckersBoard[yLoc + 1][xLoc - 1] == 1 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 2 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 3) && (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0))
						moveBL = true;
					else
						moveBL = false;
				}
				else if (xLoc == 1) //backward; cylindrical; left
				{
					if ((CMCheckersBoard[yLoc + 1][xLoc - 1] == 1 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 2 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 3) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0))
						moveBL = true;
					else
						moveBL = false;
				}
				else //forward; cylindrical; right
				{
					if ((CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 1 || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 2 || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 3) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0))
						moveBL = true;
					else
						moveBL = false;
				}
				if (moveBR == true || moveBL == true)
					TrueOrFalse = true;
				else
					TrueOrFalse = false;
			}

		}

	}
	return TrueOrFalse;
}

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	//This function counts the number of possible pieces that can make a move
	int movableCheckers = 0;
	for (int i = 0; i<numRowsInBoard; i++) //initialize arrays to -1
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}
	if (player == 1) //case for white's turn
	{
		for (int y = 0; y<numRowsInBoard; y++)
		{
			for (int x = 0; x<numRowsInBoard; x++)
			{
				if (CMCheckersBoard[y][x] == WHITESOLDIER || CMCheckersBoard[y][x] == WHITEMULE || CMCheckersBoard[y][x] == WHITEKING) //if a white piece is identified
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, x, y) == true) //if a (non jump) move is possible increase count
					{
						movableCheckers++;
					}
				}
			}

		}
	}
	else if (player == 2) //case for red's turn
	{
		for (int y = 0; y<numRowsInBoard; y++)
		{
			for (int x = 0; x<numRowsInBoard; x++)
			{
				if (CMCheckersBoard[x][y] == REDSOLDIER || CMCheckersBoard[x][y] == REDMULE || CMCheckersBoard[x][y] == REDKING) //if a red piece is identified
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, x, y) == true) //if a (non jump) move is possible increase count
					{
						movableCheckers++;
					}
				}
			}

		}
	}
	return movableCheckers;
}

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	// This function considers one checker and decides if there is a possible (non jump) move to be made
	bool makeAMove = false;
	if (player == WHITEPLAYER)
	{
		if (CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{
			if (xLoc == 0) //if the piece is on the left edge of the board
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == NOPLAYER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == NOPLAYER)
				{
					makeAMove = true;
				}
			}
			else if (xLoc == (numRowsInBoard - 1)) //if the piece is on the right edge of board
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] == NOPLAYER || CMCheckersBoard[yLoc + 1][0] == NOPLAYER)
				{
					makeAMove = true;
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] == NOPLAYER || CMCheckersBoard[yLoc + 1][xLoc - 1] == NOPLAYER) //non edge cases 
				{
					makeAMove = true;
				}
			}
		}
		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING) //only including cases of moving backwards, we already know from previous if it can move forward
		{
			if (yLoc != 0) //if the king is not at the top of the board (couldn't move up anymore)
			{
				if (xLoc == 0) //king on left edge
				{
					if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == NOPLAYER || CMCheckersBoard[yLoc - 1][xLoc + 1] == NOPLAYER)
					{
						makeAMove = true;
					}
				}
				else if (xLoc == numRowsInBoard - 1) //king on right edge
				{
					if (CMCheckersBoard[yLoc - 1][0] == NOPLAYER || CMCheckersBoard[yLoc - 1][xLoc - 1] == NOPLAYER)
					{
						makeAMove = true;
					}
				}
				else //non edge case
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == NOPLAYER || CMCheckersBoard[yLoc - 1][xLoc - 1] == NOPLAYER)
					{
						makeAMove = true;
					}
				}
			}
		}
	}
	else if (player == REDPLAYER)
	{
		if (CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			if (xLoc == 0) //if the piece is on the left edge of the board
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == NOPLAYER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == NOPLAYER)
				{
					makeAMove = true;
				}
			}
			else if (xLoc == (numRowsInBoard - 1)) //if the piece is on the right edge of board
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] == NOPLAYER || CMCheckersBoard[yLoc - 1][0] == NOPLAYER)
				{
					makeAMove = true;
				}
			}
			else //non edge cases 
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] == NOPLAYER || CMCheckersBoard[yLoc - 1][xLoc - 1] == NOPLAYER)
				{
					makeAMove = true;
				}
			}
		}
		if (CMCheckersBoard[yLoc][xLoc] == WHITEKING) //only including cases of moving backwards, we already know from previous if it can move forward
		{
			if (yLoc != numRowsInBoard - 1) //if the king is not at the bottom of the board (couldn't move down anymore)
			{
				if (xLoc == 0) //king on left edge
				{
					if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == NOPLAYER || CMCheckersBoard[yLoc + 1][xLoc + 1] == NOPLAYER)
					{
						makeAMove = true;
					}
				}
				else if (xLoc == numRowsInBoard - 1) //king on right edge
				{
					if (CMCheckersBoard[yLoc + 1][0] == NOPLAYER || CMCheckersBoard[yLoc + 1][xLoc - 1] == NOPLAYER)
					{
						makeAMove = true;
					}
				}
				else //non edge cases
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == NOPLAYER || CMCheckersBoard[yLoc + 1][xLoc - 1] == NOPLAYER)
					{
						makeAMove = true;
					}
				}
			}
		}
	}
	return makeAMove;
}

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//this function is designed to check if one of the players has won/lost by loosing all their mules, or only having mules left 
	//establish bool return value, establish counters for all players. rm = red 
	bool win = false;
	int rm = 0;
	int rs = 0;
	int rk = 0;
	int wm = 0;
	int ws = 0;
	int wk = 0;
	for (int x = 0; x<numRowsInBoard; x++)
	{
		for (int y = 0; y<numRowsInBoard; y++)
		{
			if (CMCheckersBoard[y][x] == REDMULE)
			{
				rm += 1;
			}
			else if (CMCheckersBoard[y][x] == REDSOLDIER)
			{
				rs += 1;
			}
			else if (CMCheckersBoard[y][x] == REDKING)
			{
				rk += 1;
			}
			else if (CMCheckersBoard[y][x] == WHITEMULE)
			{
				wm = +1;
			}
			else if (CMCheckersBoard[y][x] == WHITESOLDIER)
			{
				ws += 1;
			}
			else if (CMCheckersBoard[y][x] == WHITEKING)
			{
				wk += 1;
			}
		}
	}

	if (rm == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules";
		win = true;
	}
	if (wm == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules";
		win = true;
	}
	if (rs == 0 && rk == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings";
		win = true;
	}
	if (ws == 0 && wk == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings";
		win = true;
	}

	return win;
}

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	bool move = true;
	jumped = false;
	//this function is designed to move or jump a players piece 
	//begin by making x and y coordinates for the spaces the piece will move t
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	x1 = (fromSquareNum) % numRowsInBoard;
	y1 = (fromSquareNum) / numRowsInBoard;
	x2 = (toSquareNum) % numRowsInBoard;
	y2 = (toSquareNum) / numRowsInBoard;
	char word[1024] = { '0' };

	if (CMCheckersBoard[y2][x2] != 0)
	{
		cerr << "Error;  illegal move" << endl;
		return false;
	}
	if (player == WHITEPLAYER)
	{
		if (y2 - y1 == 1) //if the player is making a move one space down the board
		{
			if (x1 == 0) //if the piece is on the left edge
			{
				if (!(toSquareNum == fromSquareNum + numRowsInBoard + 1 || toSquareNum == fromSquareNum + (2 * numRowsInBoard) - 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else if (x1 == (numRowsInBoard - 1)) //if the piece is on the right edge 
			{
				if (!(toSquareNum == fromSquareNum + numRowsInBoard - 1 || toSquareNum == fromSquareNum + 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else //if the piece is in the middle area of board
			{
				if (!(toSquareNum == fromSquareNum + numRowsInBoard + 1 || toSquareNum == fromSquareNum + numRowsInBoard - 1)) //if legal move
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			CMCheckersBoard[y2][x2] = CMCheckersBoard[y1][x1];
			CMCheckersBoard[y1][x1] = 0;
			lastrow(CMCheckersBoard, numRowsInBoard);
			return true;
		}
		else if (y2 - y1 == 2) //if the player is making a jump
		{
			if (toSquareNum == fromSquareNum + (2 * numRowsInBoard) + 2 || toSquareNum == fromSquareNum + (3 * numRowsInBoard) - 2)// if a legal move from most left or 1 more than most left of the board
			{
				if (x1 == 0)  //if the piece is on the most left 
				{
					//if there is no opponent to be jumped over
					if (!(CMCheckersBoard[y1 + 1][x1 + 1] == REDKING || CMCheckersBoard[y1 + 1][x1 + 1] == REDSOLDIER || CMCheckersBoard[y1 + 1][x1 + 1] == REDMULE || CMCheckersBoard[y1 + 1][x1 + (2 * numRowsInBoard) - 1] == REDKING || CMCheckersBoard[y1 + 1][x1 + (2 * numRowsInBoard) - 1] == REDSOLDIER || CMCheckersBoard[y1 + 1][x1 + (2 * numRowsInBoard) - 1] == REDMULE))
					{
						cerr << "Error;  illegal move" << endl;
						return false;
					}
				}
			}
			if (toSquareNum == fromSquareNum + (2 * numRowsInBoard) - 2 || toSquareNum == fromSquareNum + numRowsInBoard + 2) //if a legal move from the most right or 1 less than the most right of the board
			{
				if (x1 == (numRowsInBoard - 1)) //piece is on the most right column
				{
					//if there is no opponent to be jumped 
					if (!(CMCheckersBoard[y1 + 1][x1 - 1] == REDKING || CMCheckersBoard[y1 + 1][x1 - 1] == REDSOLDIER || CMCheckersBoard[y1 + 1][x1 - 1] == REDMULE || CMCheckersBoard[y1 + 1][0] == REDKING || CMCheckersBoard[y1 + 1][0] == REDSOLDIER || CMCheckersBoard[y1 + 1][0] == REDMULE))
					{
						cerr << "Error;  illegal move" << endl;
						return false;
					}
				}
			}
			if (toSquareNum == fromSquareNum + (2 * numRowsInBoard) - 2 || toSquareNum == fromSquareNum + (2 * numRowsInBoard) + 2) //if a legal move from the middle of the board
			{
				//if there is no opponent to be jumped 
				if (!(CMCheckersBoard[y1 + 1][x1 + (x2 - x1) / 2] == REDKING || CMCheckersBoard[y1 + 1][x1 + (x2 - x1) / 2] != REDMULE || CMCheckersBoard[y1 + 1][x1 + (x2 - x1) / 2] != REDSOLDIER))
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else //if jump is not legal
			{
				cerr << "Error;  illegal move" << endl;
				return false;
			}
		}
		CMCheckersBoard[y2][x2] = CMCheckersBoard[y1][x1];
		CMCheckersBoard[y1][x1] = 0;
		CMCheckersBoard[y1 + 1][x1 + (x2 - x1)/2] = 0;
		jumped = true;
		lastrow(CMCheckersBoard, numRowsInBoard);
		return true;
	}
	if (player == REDPLAYER)
	{
		if (y2 - y1 == -1) //if the player is making a move one space up the board
		{
			if (x1 == 0) //if the piece is on the left edge
			{
				if (!(toSquareNum == fromSquareNum - numRowsInBoard + 1 || toSquareNum == fromSquareNum - 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else if (x1 == (numRowsInBoard - 1)) //if the piece is on the right edge 
			{
				if (!(toSquareNum == fromSquareNum - numRowsInBoard - 1 || toSquareNum == fromSquareNum - (2 * numRowsInBoard) + 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else //if the piece is in the middle area of board
			{
				if (!(toSquareNum == fromSquareNum - numRowsInBoard + 1 || toSquareNum == fromSquareNum - numRowsInBoard - 1)) //if legal move
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			CMCheckersBoard[y2][x2] = CMCheckersBoard[y1][x1];
			CMCheckersBoard[y1][x1] = 0;
			lastrow(CMCheckersBoard, numRowsInBoard);
			return true;
		}
		else if (y2 - y1 == -2) //if the player is making a jump
		{
			if (toSquareNum == fromSquareNum - (2 * numRowsInBoard) + 2 || toSquareNum == fromSquareNum - numRowsInBoard - 2)// if a legal move from most left or 1 more than most left of the board
			{
				if (x1 == 0)  //if the piece is on the most left 
				{
					//if there is no opponent to be jumped over
					if (!(CMCheckersBoard[y1 - 1][x1 + 1] == REDKING || CMCheckersBoard[y1 - 1][x1 + 1] == REDSOLDIER || CMCheckersBoard[y1 - 1][x1 + 1] == REDMULE || CMCheckersBoard[y1 - 1][numRowsInBoard - 1] == REDKING || CMCheckersBoard[y1 - 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[y1 - 1][numRowsInBoard - 1] == REDMULE))
					{
						cerr << "Error;  illegal move" << endl;
						return false;
					}
				}
			}
			if (toSquareNum == fromSquareNum - (2 * numRowsInBoard) - 2 || toSquareNum == fromSquareNum - (3 * numRowsInBoard) + 2) //if a legal move from the most right or 1 less than the most right of the board
			{
				if (x1 == (numRowsInBoard - 1)) //piece is on the most right column
				{
					//if there is no opponent to be jumped 
					if (!(CMCheckersBoard[y1 - 1][x1 - 1] == REDKING || CMCheckersBoard[y1 - 1][x1 - 1] == REDSOLDIER || CMCheckersBoard[y1 - 1][x1 - 1] == REDMULE || CMCheckersBoard[y1 - 1][0] == REDKING || CMCheckersBoard[y1 - 1][0] == REDSOLDIER || CMCheckersBoard[y1 - 1][0] == REDMULE))
					{
						cerr << "Error;  illegal move" << endl;
						return false;
					}
				}
			}
			if (toSquareNum == fromSquareNum - (2 * numRowsInBoard) - 2 || toSquareNum == fromSquareNum - (2 * numRowsInBoard) + 2) //if a legal move from the middle of the board
			{
				//if there is no opponent to be jumped 
				if (!(CMCheckersBoard[y1 + 1][x1 + (x2 - x1) / 2] == WHITEKING || CMCheckersBoard[y1 + 1][x1 + (x2 - x1) / 2] != WHITEMULE || CMCheckersBoard[y1 + 1][x1 + (x2 - x1) / 2] != WHITESOLDIER))
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else //if jump is not legal
			{
				cerr << "Error;  illegal move" << endl;
				return false;
			}
			CMCheckersBoard[y2][x2] = CMCheckersBoard[y1][x1];
			CMCheckersBoard[y1][x1] = 0;
			CMCheckersBoard[y1 - 1][x1 + (x2 - x1) / 2] = 0;
			jumped = true;
			lastrow(CMCheckersBoard, numRowsInBoard);
			return true;
		}
	}
	if (CMCheckersBoard[y1][x1] == WHITEKING || CMCheckersBoard[y1][x1] == REDKING)
	{
		if (y2 - y1 == 1) //if the player is making a move one space up the board
		{
			if (x1 == 0) //if the piece is on the left edge
			{
				if (!(toSquareNum == fromSquareNum - numRowsInBoard + 1 || toSquareNum == fromSquareNum - 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else if (x1 == (numRowsInBoard - 1)) //if the piece is on the right edge 
			{
				if (!(toSquareNum == fromSquareNum - numRowsInBoard - 1 || toSquareNum == fromSquareNum - (2 * numRowsInBoard) + 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else //if the piece is in the middle area of board
			{
				if (!(toSquareNum == fromSquareNum - numRowsInBoard + 1 || toSquareNum == fromSquareNum - numRowsInBoard - 1)) //if legal move
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			CMCheckersBoard[y2][x2] = CMCheckersBoard[y1][x1];
			CMCheckersBoard[y1][x1] = 0;
			lastrow(CMCheckersBoard, numRowsInBoard);
			return true;
		}
		else if (y2 - y1 == 1) //if the player is making a move one space down the board
		{
			if (x1 == 0) //if the piece is on the left edge
			{
				if (!(toSquareNum == fromSquareNum + numRowsInBoard + 1 || toSquareNum == fromSquareNum + (2 * numRowsInBoard) - 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else if (x1 == (numRowsInBoard - 1)) //if the piece is on the right edge 
			{
				if (!(toSquareNum == fromSquareNum + numRowsInBoard - 1 || toSquareNum == fromSquareNum + 1)) //if not legal 
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			else //if the piece is in the middle area of board
			{
				if (!(toSquareNum == fromSquareNum + numRowsInBoard + 1 || toSquareNum == fromSquareNum + numRowsInBoard - 1)) //if legal move
				{
					cerr << "Error;  illegal move" << endl;
					return false;
				}
			}
			CMCheckersBoard[y2][x2] = CMCheckersBoard[y1][x1];
			CMCheckersBoard[y1][x1] = 0;
			lastrow(CMCheckersBoard, numRowsInBoard);
			return true;
		}
	}
	lastrow(CMCheckersBoard, numRowsInBoard);
	return move;
}

void lastrow(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//this function changes any soldier into a king if it goes to the end of the board, it will also end the game if a mule reaches the end
	char word[1024] = { 0 };
	for (int x = 0; x < numRowsInBoard; x++) //make any changes to soldiers who make it all the way to the end of the board, end game if a mule does so
	{
		if (CMCheckersBoard[0][x] == REDSOLDIER)
		{
			CMCheckersBoard[0][x] = REDKING;
		}
		if (CMCheckersBoard[0][x] == REDMULE)
		{
			cout << "Red has created a Mule King,  White wins the game" << endl;
			cout << "Enter any character to terminate the game then press the enter key" << endl;
			cin >> word;
			exit(1);
		}
		if (CMCheckersBoard[numRowsInBoard - 1][x] == WHITESOLDIER)
		{
			CMCheckersBoard[numRowsInBoard - 1][x] = WHITEKING;
		}
		if (CMCheckersBoard[numRowsInBoard - 1][x] == WHITEMULE)
		{
			cout << "White has created a Mule King,  Red wins the game" << endl;
			cout << "Enter any character to terminate the game then press the enter key" << endl;
			cin >> word;
			exit(1);
		}
	}
}