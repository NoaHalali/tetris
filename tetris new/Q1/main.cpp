
#include "TetrisGame.h"



//void shapeTester();
//void BoardTester(TetrisBoard board);
void GameTester();

void main()
{
	srand(time(0));
	TetrisGame Game;
	Game.start();
	//void BoardTester()
	//BoardTester();
	//GameTester();

}

//void GameTester()
//{
//	bool isGameover = false;
//	TetrisBoard boardOne, boardTwo;
//	boardOne.init(GameConfig::MIN_X_BOARD1);
//	boardTwo.init(GameConfig::MIN_X_BOARD2);
//	while (boardOne.getDidLose() ==FALSE && boardTwo.getDidLose() ==FALSE)
//	{
//		for (int i = 0; i < 3; i++) 
//		{
//			char keyPressed = 0;
//			if (_kbhit()) //if key is pressed
//			{
//				keyPressed = _getch();
//				if (keyPressed == GameConfig::ESC)
//				{
//					isGameover = true;
//					break;
//				}
//				keyPressed = toupper(keyPressed);
//			}
//			//change to uppercase letters the keypressed
//			//checking if the first player pressed any of his keys and if so moving curr piece
//			if (keyPressed == GameConfig::eKeys_left::LEFT || keyPressed == GameConfig::eKeys_left::RIGHT ||
//				keyPressed == GameConfig::eKeys_left::ROTATE_clockwise || keyPressed == GameConfig::eKeys_left::ROTATE_counter ||
//				keyPressed == GameConfig::eKeys_left::DROP)
//			{
//				boardOne.move(keyPressed);
//				boardTwo.move(0);
//			}
//			//checking if the second player pressed any of his keys and if so moving curr piece 
//			else if (keyPressed == GameConfig::eKeys_right::LEFT || keyPressed == GameConfig::eKeys_right::RIGHT ||
//				keyPressed == GameConfig::eKeys_right::ROTATE_clockwise || keyPressed == GameConfig::eKeys_right::ROTATE_counter ||
//				keyPressed == GameConfig::eKeys_right::DROP)
//			{
//				boardTwo.move(keyPressed);
//				boardOne.move(0);
//			}
//			else
//			{
//				boardOne.move(0);
//				boardTwo.move(0);
//			}
//			Sleep(50);
//		}
//		Sleep(50);
//		//move both board pieces down in every round
//
//	}
//
//}
//void drawBorderSomewhere()
//{
//	for (int col = GameConfig::MIN_X; col < GameConfig::MIN_X + GameConfig::GAME_WIDTH; col++)
//	{
//		gotoxy(col, GameConfig::MIN_Y - 1);
//		cout << "-";
//
//		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
//		cout << "-";
//	}
//
//	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::MIN_Y + GameConfig::GAME_HEIGHT; row++)
//	{
//		gotoxy(GameConfig::MIN_X - 1, row);
//		cout << "|";
//
//		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
//		cout << "|";
//	}
//}


//void movingStarInBoardSomewhere()
//{
//	drawBorderSomewhere();
//	int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//
//	while (!_kbhit() || _getch() != 27)
//	{
//		gotoxy(x, y);
//		cout << "*";
//		Sleep(500);
//		gotoxy(x, y);
//		cout << " ";
//
//		++x;
//		if (x == GameConfig::GAME_WIDTH + GameConfig::MIN_X) //ìçæåø ìàåúä ð÷åãä ùì úçéìú äìåç (X)
//			x = GameConfig::MIN_X;
//
//		++y;
//		if (y == GameConfig::GAME_HEIGHT + GameConfig::MIN_Y) //ìçæåø ìàåúä ð÷åãä ùì úçéìú äìåç (Y
//			y = GameConfig::MIN_Y;
//
//	}
//}


//
//void movingStarInBoardSomewhereWithPoint()
//{
//	drawBorderSomewhere();
//	//int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//	Point p1;
//	p1.init(1, 1);
//
//	while (true)
//	{
//		int keyPressed = 0;
//		if (_kbhit())
//		{
//			keyPressed = _getch();
//			if (keyPressed == (int)GameConfig::ESC)
//				break;
//		}
//		p1.draw('*', 120);
//		Sleep(500);
//		p1.draw(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//
//		p1.move(keyPressed);
//		//p1.move();
//	}
//}

//void shapeTester()
//{	
//	drawBorder();
//	//int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//	shape s;
//	srand(time(NULL));
//	s.init(rand() % (TetrisBoard::NUM_OF_SHAPES + 1), '#', 120);
//	s.setCoords();
//
//	while (true)
//	{
//		int keyPressed = 0;
//		if (_kbhit())
//		{
//			keyPressed = _getch();
//			if (keyPressed == GameConfig::ESC)
//				break;
//		}
//		s.drawShape('#', 120);
//		Sleep(500);
//		s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//		s.move(keyPressed);
//	}
//}

//void BoardTester()
//{
//	TetrisBoard board;
//	board.drawBorder();
//	//int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//	shape s;
//	srand(time(NULL));
//	s.init(rand()% (TetrisBoard::NUM_OF_SHAPES+1), '#', 120);
//	s.setShape();
//	
//	while (true)
//	{
//		shape tempShape = s; //éöéøú òåú÷ ìáãé÷ú ú÷éðåú
//		int keyPressed = 0;
//		if (_kbhit()) //if key is pressed
//		{
//			keyPressed = _getch();
//			if (keyPressed == GameConfig::ESC)
//				break;
//
//			else
//				tempShape.move(keyPressed);
//				if (board.checkMovePieceOnBoard(tempShape))
//				{
//					s.drawShape('#', 120);
//					board.placePieceOnBoard(s);
//					Sleep(500);
//					s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//					board.deletePieceOnBoard(s);
//					s.move(keyPressed);
//				}
//		}
//		//else, keep going down
//		if (board.checkMovePieceOnBoard(tempShape))
//		{
//			s.drawShape('#', 120);
//			board.placePieceOnBoard(s);
//			Sleep(500);
//			s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//			board.deletePieceOnBoard(s);
//			s.move(keyPressed);
//		}
//		else
//		{
//			s.drawShape('#', 120);
//			board.placePieceOnBoard(s);
//		}
//	}
//}

///*void run(TetrisBoard board, int minX)
//{
//	
//	board.drawBorder(minX);
//	while (true)
//	{
//		int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//		bool isShapeChanged = false;
//		shape s;
//		srand(time(NULL));
//		s.init(rand() % (TetrisBoard::NUM_OF_SHAPES + 1), '#', 120);
//		s.init(2, '#', 120); //áãé÷ú òîåã
//		s.setShape();
//		board.placePieceOnBoard(s);
//		s.drawShape('#', 120);
//		Sleep(500);
//		s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//		board.deletePieceOnBoard(s);
//		while (!isShapeChanged)
//		{
//			shape tempShapeDown, tempShapeLeftRight; //éöéøú òåú÷éí ìáãé÷ú ú÷éðåú
//			int	keyPressed = 0;
//			if (_kbhit()) //if key is pressed
//			{
//				keyPressed = _getch();
//				if (keyPressed == GameConfig::ESC)
//					break;
//			}
//			
//			tempShapeDown = s;
//			for (int i = 0; i < 4; i++)//down
//			{
//				tempShapeDown.getShape()[i].movePointDown();
//			}
//			if(board.checkMovePieceDown(tempShapeDown))
//			{
//				keyPressed = 0;
//				for (int i = 0; i < 4; i++)
//				{
//					s.getShape()[i].movePointDown();
//				}
//				board.placePieceOnBoard(s);
//				s.drawShape('#', 120);
// 				Sleep(500);
//				s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//				board.deletePieceOnBoard(s);
//				s.move(keyPressed);
//			}
//			else
//			{
//				s.drawShape('#', 120);
//				board.placePieceOnBoard(s);
//				isShapeChanged = true;
//				board.checkFullLinesOnBoard();
//
//			}
//			keyPressed = s.convert(keyPressed);
//			tempShapeLeftRight = s;
//			tempShapeLeftRight.move(keyPressed); //right or left or rotate
//			if (board.checkMovePieceRightAndLeft(tempShapeLeftRight) && !isShapeChanged && keyPressed!=0)
//			{
//				s.drawShape('#', 120);
//				board.placePieceOnBoard(s);
//				Sleep(500);
//				s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//				board.deletePieceOnBoard(s);
//				s.move(keyPressed);
//			}
//			
//			/*if ((board.checkMovePieceDown(tempShape))&&(board.checkMovePieceRightAndLeft(tempShape)))
//			{
//				s.drawShape('#', 120);
//				board.placePieceOnBoard(s);
//				Sleep(500);
//				s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//				board.deletePieceOnBoard(s);
//				s.move(keyPressed);
//			}*/
//			else, keep going down
//				/*tempShape.move(keyPressed);
//				if (board.checkMovePieceDown(tempShape) && (board.checkMovePieceRightAndLeft(tempShape)))
//				{
//					s.drawShape('#', 120);
//					board.placePieceOnBoard(s);
//					Sleep(500);
//					s.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//					board.deletePieceOnBoard(s);
//					s.move(keyPressed);
//				}*/
//				tempShape = s;
//				s.move(keyPressed);
//
//		}
//	}
//}