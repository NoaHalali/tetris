#include "TetrisGame.h"

//This function initilizes the boards for the two  human players and initilises the boolian for if the game has already started
void TetrisGame::initNewGameHumans()
{
	p1 = new humanPlayer(GameConfig::MIN_X_BOARD1, gameColor, GameConfig::LEFT_PLAYER);
	p2 = new humanPlayer(GameConfig::MIN_X_BOARD2, gameColor, GameConfig::RIGHT_PLAYER);
	p1->giveMeShape();
	p2->giveMeShape();
	newGame = true;

}
//This function initilizes the boards for the two computer players and initilises the boolian for if the game has already started
void TetrisGame::initNewGameComputers()
{
	char choice1, choice2;

	cout << "Choose game mode for left computer player:" << endl;
	cout << "Press 'a' for BEST, 'b' for GOOD and 'c' for NOVICE mode: ";
	cin >> choice1;
	cout << "Choose game mode for right computer player:" << endl;
	cout << "Press 'a' for BEST, 'b' for GOOD and 'c' for NOVICE mode: ";
	cin >> choice2;
	clrscr();															//Clean screen	
	p1 = new Computer(GameConfig::MIN_X_BOARD1, gameColor, GameConfig::LEFT_PLAYER, choice1);
	p2 = new Computer(GameConfig::MIN_X_BOARD2, gameColor, GameConfig::RIGHT_PLAYER, choice2);
	p1->giveMeShape();
	p2->giveMeShape();
	newGame = true;
}

//This function initilizes the boards for the human player & computer player and initilises the boolian for if the game has already started
void TetrisGame::initNewGameHumanVsComputer()
{
	char choice;
	cout << "Choose game mode:"<< endl;
	cout<< "Press 'a' for BEST, 'b' for GOOD and 'c' for NOVICE mode: ";
	cin >> choice;
	clrscr();															//Clean screen	
	p1 = new humanPlayer(GameConfig::MIN_X_BOARD1, gameColor, GameConfig::LEFT_PLAYER);
	p2 = new Computer(GameConfig::MIN_X_BOARD2, gameColor, GameConfig::RIGHT_PLAYER, choice);
	p1->giveMeShape();
	p2->giveMeShape();
	newGame = true;
}

//This function is running the game
void TetrisGame::start()
{
	newGame = true;															//A new game in the beginning
	gameColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;		//default is black background
	int choice = 0;															//Choice is getting the player's choice of display 
	while (choice != GameConfig::EXIT)										//Checking if the user chose to exit the game
	{
		displayMenu();														//Prints the menu
		cin >> choice;														//Get the user choice
		clrscr();															//Clean screen	
		handleMenuChoice(choice);											//Checking the players choice
	}
}

//This function is printing the menu on screen
void TetrisGame::displayMenu() const
{
	cout << "===== Menu =====" << endl;
	cout << "(1) Start a new game - Human vs Human" << endl;
	cout<<"(2) Start a new game - Human vs Computer " << endl;
	cout<<"(3) Start a new game - Computer vs Computer " << endl;

	if (!newGame)															//Prints option 2 onlt if the game already started and been paused
	{
		cout << "(4) Continue a paused game" << endl;
	}
	cout << "(5) Game color options";
	if (gameColor == GameConfig::BLACK) {
		cout << " (Current game color: Black)" << endl;
	}
	else {
		cout << " (Current game color: ColorFul)" << endl;
	}
	cout << "(8) Display instructions and keys" << endl;
	cout << "(9) Exit" << endl;
	cout << "================" << endl;
}
//This function gets the choice of the user and plays accordingly
void TetrisGame::handleMenuChoice(int choice)
{
	switch (choice) {
	case GameConfig::START_NEW_GAME_HUMAN_VS_HUMAN:
		clrscr();
		initNewGameHumans();
		runGame();
		break;

	case GameConfig::START_NEW_GAME_HUMAN_VS_COMPUTER:
		clrscr();
		initNewGameHumanVsComputer();
		runGame();
		break;

	case GameConfig::START_NEW_GAME_COMPUTER_VS_COMPUTER:
		clrscr();
		initNewGameComputers();
		runGame();
		break;

	case GameConfig::CONTINUE:
		clrscr();
		p1->drawBorder();
		p2->drawBorder();
		p1->PrintNewBoard();
		p2->PrintNewBoard();
		runGame();
		break;

	case GameConfig::COLORS:
		int choice;
		cout << "Press 1 for colors and 2 for non-colored game: ";
		cin >> choice;
		if (choice == WITH_COLORS)
		{
			gameColor = COLORFUL;
			p1->setColor(COLORFUL);
			p2->setColor(COLORFUL);
		}
		else //chose 2
		{
			gameColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;			//Black background
			p1->setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			p2->setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		clrscr();
		break;

	case GameConfig::INSTRUCTIONS:
		displayInstructions();
		clrscr();
		break;

	case GameConfig::EXIT:
		cout << "Goodbye" << endl;
		break;
	}
}

//This function is printing the instruction of the game and the keys for each player
void TetrisGame::displayInstructions() const {
	cout << "=== Tetris Instructions ===" << endl;
	cout << "Right Player Controls:" << endl;
	cout << "-----------------" << endl;
	cout << "LEFT\t\t\t\tj or J" << endl;
	cout << "RIGHT\t\t\t\tl (small L) or L" << endl;
	cout << "ROTATE clockwise\t\tk or K" << endl;
	cout << "ROTATE counterclockwise\t\ti or I (uppercase i)" << endl;
	cout << "DROP\t\t\t\tm or M" << endl;
	cout << "-----------------" << endl;
	cout << "Left Player Controls:" << endl;
	cout << "-----------------" << endl;
	cout << "LEFT\t\t\t\ta or A" << endl;
	cout << "RIGHT\t\t\t\td or D" << endl;
	cout << "ROTATE clockwise\t\ts or S" << endl;
	cout << "ROTATE counterclockwise\t\tw or W" << endl;
	cout << "DROP\t\t\t\tx or X" << endl;
	cout << "-----------------" << endl;

	//to exit instruction 
	cout << "PRESS ANY KEY TO GO BACK TO MENU";

	_getch();
}

//This function is managing the game
void TetrisGame::runGame()
{
	newGame = false;															 //Because game has started now
	while (p1->getDidLose() == FALSE && p2->getDidLose() == FALSE)
	{
		for (int i = 0; i < 2; i++) {
			char keyPressed = shape::MOVE_DOWN;									//Initialize direction, move down by default
			if (_kbhit())														//Check if key is pressed
			{
				keyPressed = _getch();
				if (keyPressed == GameConfig::ESC)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //Remove background color for point and turn to black
					clrscr();
					return;
				}
				keyPressed = toupper(keyPressed);																					//Change to uppercase letters the keypressed
			}
			p1->calcMove(keyPressed);		//calculates and updates next move for player 1
			p2->calcMove(keyPressed);	

			p1->move();						//execute move for player 1
			p2->move();

			Sleep(GameConfig::AVG_SLEEP);

		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);		//Remove background color for point
	//The game is over
	clrscr();
	if (p1->getDidLose())									//Player 1 lost
		cout << "PLAYER " << GameConfig::RIGHT_PLAYER << " WON!" << endl;
	else														//Player 2 lost
		cout << "PLAYER " << GameConfig::LEFT_PLAYER << " WON!" << endl;


	cout << "GAME OVER!" << endl;
	Sleep(GameConfig::LONG_SLEEP_TIME);
	clrscr();

	//Getting all the leftover chars 
	while (_kbhit()) {
		_getch();
	}
	newGame = true;								//Initilises the indicator, the current game has ended
}