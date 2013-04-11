/*Bingo-based slot machine. Bingo card is generated at the beginning of play with a random number of 'a' and 'b'.
	Entire card must be filled with 'b' to win. Each "Spin" will set one random spot on the card to 'b', if that spot is already 'b' its a wasted spin.
	Card is not reset until a win happens.
	
TO DO: 	Build slots around bingo card functions.
		Add Single spin setup.
		Add betting function.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//constants
const int SIZE = 3;
const char Wheel_Symbols[3] = {'X', '7', '$'};
const int X_Payout = 2;
const int Seven_Payout = 5;
const int Dollar_Payout = 3;


//Bingo Board delcaration
char Bingo[SIZE + 1][SIZE + 1];

//Player money
int Money = 100;


bool Play(bool, int);			   
void PrintBingo();
int SetBingo();
void ChangeBingo();
bool CheckBingo();
void GenerateWin();
bool AskPlay();
void Broke();

int main()
{
	//seed the number generator with current time
	srand(time(NULL));
	bool Winner = false, Ask = false;
	int Minimum = SetBingo(); //sets the board and gets how many 'a's are on the board to start
	PrintBingo(); //prints initial states of the board
	cout << endl;

	
	Ask = AskPlay();

	while (Ask == true)
	{
		Winner = Play(Winner, Minimum); //calls play fucntion and returns the result
		cout << "Money Remaining: $" << Money << endl; //outputs moeny remaining
		
		if (Winner == true) //if player won
		{
			cout << "YOU WON!!!" << endl;
			GenerateWin(); //generate winning symbol and add wins to player money
			cout << "New Blance: $" << Money << endl; 
			int Minimum = SetBingo(); //reset board
			PrintBingo(); //print new board
			Winner = false; //reset winner variable to false
			//Ask = false;
		}
		if (Money == 0) //if player lsoes all money, exit game and output lose statement
		{
			Broke();
			break;
		}
		Ask = AskPlay();
	}
	return 0;
}

//function to initialize entire board to either 'a' or 'b'. Uses a random number, modded by SIZE, to determine which.
int SetBingo()
{
	int PreSet = SIZE*SIZE;
	for (int i = 0; i < SIZE; i++)
	{
		for( int j = 0; j < 10; j++)
		{
			if (rand() % SIZE == 0)
			{
				Bingo[i][j] = 'b';
				PreSet--;
			}
			else
				Bingo[i][j] = 'a';
		}
	}
	return PreSet;
}


//function to print entire bingo board to screen. Mostly just for debugging purposes.
void PrintBingo()
{
	for (int i = 0; i < SIZE; i++)
	{
		for( int j = 0; j < SIZE; j++)
		{
			cout << Bingo[i][j] << ' ';
		}
		cout << endl;
	}
}
	
//function to generate two random number and set the board location of those numbers to 'b'
void ChangeBingo()
{
	int Random1 = rand() % SIZE;
	int Random2 = rand() % SIZE;
	
	Bingo[Random1][Random2] = 'b';
}

//checks the board to see if entire board is 'b'.
bool CheckBingo()
{
	bool Win = false;
	for (int i = 0; i < SIZE; i++)
	{
		for( int j = 0; j < SIZE; j++)
		{
			if (Bingo[i][j] == 'b')
				if (Bingo[i-1][j] == 'a' || Bingo[i-1][j-1] == 'a' || Bingo[i][j-1] == 'a') //check for last symbol on board to make sure surrounding symbols are not 'a'
					Win = false;
				else
					Win = true;
			else 
				Win = false;
		}
	}
	return Win;
}

bool Play(bool Winner, int Minimum)
{
	Money--;
	int Shown[3] = {0};
	static int Plays = 1;
	if(Winner == false || Plays < Minimum) //while the board is not all 'b' and the minimum hasn't been reached
	{
		ChangeBingo();
		Winner = CheckBingo();
		//cout << "@@@ " << Winner << " @@@" << endl;
		//PrintBingo();
		//generate random numbers for use as slot symbols.
		for (int k = 0; k < 3; k++)
			Shown[k] = rand() % 3;
		
		//if all symbols are the same yet not yet a winner, change a random symbol.
		if (Shown[0] == Shown[1] && Shown[1] == Shown[2])
		{
			if(Shown[0] == 0)
			{
				Shown[rand() % 3] = 1;
				//cout << "@@@@@@@@@@@@@@@@@@" << endl;
			}
			else if (Shown[0] == 1)
			{
				Shown[rand() % 3] = 2;
				//cout << "@@@@@@@@@@@@@@@@@@" << endl;
			}
			else if (Shown[0] == 2)
			{
				Shown[rand() % 3] = 0;
				//cout << "@@@@@@@@@@@@@@@@@@" << endl;
			}
		}
		cout << "Spin# " << Plays << ": " << Wheel_Symbols[Shown[0]] << Wheel_Symbols[Shown[1]] << Wheel_Symbols[Shown[2]] << endl;
		Plays++;
	}
	return Winner;
}

void GenerateWin()
{
	char Win_Symbol = Wheel_Symbols[rand() % 3];
	cout << Win_Symbol << Win_Symbol << Win_Symbol << endl;
	if (Win_Symbol == 'X')
	{
		cout << "Wins: $" << X_Payout << endl;
		Money += X_Payout;
	}
	
	else if (Win_Symbol == '7')
	{
		cout << "Wins: $" << Seven_Payout << endl;
		Money += Seven_Payout;
	}
	
	else if (Win_Symbol == '$')
	{
		cout << "Wins: $" << Dollar_Payout << endl;
		Money += Dollar_Payout;
	}
}

bool AskPlay()
{
	char answer;
	cout << "Do you want to play? (Y/N)" << endl;
	cin >> answer;
	
	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
	
}

void Broke()
{
	cout << "You are Broke. Please visit the casino ATM to continue playing." << endl;
}