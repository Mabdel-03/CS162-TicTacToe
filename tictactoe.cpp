#include <iostream>
#include <cstring>

using namespace std;

#define BLANK 0
#define ROWS 3
#define COLS 3
#define X_MOVE 1
#define O_MOVE 2

void printBoard(int board[ROWS][COLS]);
void resetBoard(int board[ROWS][COLS]);
int checkWin(int board[ROWS][COLS]);
bool checkBoard(int board[ROWS][COLS]);
bool checkTie(int board[ROWS][COLS]);

int main() {

  int board[ROWS][COLS];
  int winner = 0;
  const int X_TURN = 0;
  const int O_TURN = 1;
  bool stillPlaying = true;
  bool successfulMove = false;
  int turn = X_TURN;
  char str[3]; 
  int xWins = 0;
  int oWins = 0;

  while(stillPlaying == true) {

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Please enter your move!" << endl;
    cout << "Enter in letter-number format (ex. a1, b3, etc.)" << endl;

    resetBoard(board);
    turn = X_TURN;
    while(checkWin(board) == 0 && checkTie(board) == false) {

      successfulMove = false;
      printBoard(board);
      cout << "Enter your move: " << endl;
      cin.get(str, 3);
      cin.get();

      //check if input works
      if(strlen(str) != 2) {
	cout << "Please enter a letter followed by a number (ex. a1,b3, etc.)" << endl;
      }
      else {
	if((str[0]!= 'a') && (str[0] != 'b') && (str[0] != 'c')) {
	cout << "The row must be either a, b, or c" << endl;
	}
	else {
	  if((str[1] != '1') && (str[1] != '2') && (str[1] != '3')) {
	    cout << "column must be either 1, 2, or 3" << endl;
	  }
	  else { //legal

	    int row = str[0] - 'a';
	    int column = str[1] - '1';

	    //X Move
	    if((turn == X_TURN) && (board[row][column] == BLANK)) {
	      board[row][column] = X_MOVE;
	      successfulMove = true;
	    }
	    //if there is a piece in the spot:
	    else if((turn == X_TURN) && (board[row][column] != BLANK)) {
	      cout << "There is already a piece there!" << endl;
	    }

	    //O Move
	    if((turn == O_TURN) && (board[row][column] == BLANK)) {
	      board[row][column] = O_MOVE;
	      successfulMove = true;
	    }
	    //if there is a piece in the spot
	    else if((turn == O_TURN) && (board[row][column] == BLANK)) {
	      cout << "There is already a piece here!" << endl;
	    }

	    //switch turns following each successful move
	    if((turn == X_TURN) && (successfulMove == true)) {
	      cout << "O Turn" << endl;
	      turn = O_TURN;
	    }
	    else if((turn == O_TURN) && (successfulMove == true)) {
	      cout << "X Turn" << endl;
	      turn = X_TURN;
	    }

	  }
	}
      }
    }

      //check for wins and ties

      if(checkWin(board) == 0) { //tie 
	cout << "It's a tie!" << endl;
	cout << "# of X Wins: " << xWins << endl;
	cout << "# of O wins: " << oWins << endl;
      }

      else if(checkWin(board) == 1) { //X Win
	cout << "X Wins!" << endl;
	xWins++;
	cout << "# of X Wins: " << xWins << endl;
	cout << "# of O wins: " << oWins << endl;
      }

      else if(checkWin(board) == 2) { //O Win
	cout << "O Wins!" << endl;
	oWins++;
	cout << "# of X Wins: " << xWins << endl;
	cout << "# of O Wins: " << oWins << endl;
      }

      char playAgain = 'y';
      bool response = false;

      while(response == false) {
	cout << "Do you want to play again? (Answer y or n)" << endl;
	cin >> playAgain;
	if (playAgain == 'N' || playAgain == 'n') {
	  stillPlaying = false;
	  response = true;
	}
	else if (playAgain == 'Y' || playAgain == 'y') {
	  stillPlaying = true;
	  response = true;
	}
	else {
	  cout << "Invalid response! Answer with y or n!" << endl;
	  response = false;
	}
      }
  }
  
    return 0;
  }

  //board setup
  void printBoard(int board[ROWS][COLS]) {
    cout << " 1 2 3" << endl; //print columns
    char output[4]; //print rows

    for(int i = 0; i < 3; i++) {

      int counter = 0;
      output[0] = ('a'+i); //through each iteration will increment the letter
      counter++;

      for(int j = 0; j < 3; j++) {

	if(board[i][j] == X_MOVE) {
	  output[counter] = 'X'; //print an X in the slot
	  counter++;
	}
	else if(board[i][j] == O_MOVE) {
	  output[counter] = 'O'; //print an O in the slot
	  counter++;
	}
	else if(board[i][j] == BLANK) {
	  output[counter] = ' '; //print nothing in the slot
	  counter++;
	}
      }
      //finally, print out all lines
      cout << output[0] << " " << output[1] << " " << output[2] << " " << output[3] << endl;

    }
  }

  //reset board
  void resetBoard(int board[ROWS][COLS]) {

    board[0][0] = BLANK;
    board[1][0] = BLANK;
    board[2][0] = BLANK;
    board[0][1] = BLANK;
    board[0][2] = BLANK;
    board[1][1] = BLANK;
    board[1][2] = BLANK;
    board[2][1] = BLANK;
    board[2][2] = BLANK;

  }

  //check for wins/ties
  int checkWin(int board[ROWS][COLS]) {

    for(int i = 1; i <= 2; i++) {
      if(board[0][0] == i && board[0][1] == i && board[0][2] == i) {//check top row across
	return i;
      }
      if(board[0][0] = i && board[1][1] == i && board[2][2] == i) {//check diagonal top left to bottom right
	return i;
      }
      if(board[0][2] == i && board[1][1] == i && board[2][0] == i) {//diagonal top right to bottom left
	return i;
      }
      if(board[0][2] == i && board[1][2] == i && board[2][2] == i) {//check right column down
	return i;
      }
      if(board[1][0] == i && board[1][1] == i && board[1][2] == i) {//check middle row across
	return i;
      }
      if(board[2][0] == i && board[2][1] == i && board[2][2] == i) {//check bottom row across
	return i;
      }
      if(board[0][0] == i && board[1][0] == i && board[2][0] == i) {//check left column down
	return i;
      }
      if(board[0][1] == i && board[1][1] == i && board[2][1] == i) {//middle row down
	return i;
      }
    }
    return 0; //no win (tie)

  }

  //check whether board is filled up or not
  bool checkBoard(int board[ROWS][COLS]) {
    if(
       board[0][0] != BLANK  &&
       board[1][0] != BLANK  &&
       board[2][0] != BLANK  &&
       board[0][1] != BLANK  &&
       board[0][2] != BLANK  &&
       board[1][1] != BLANK  &&
       board[1][2] != BLANK  &&
       board[2][1] != BLANK  &&
       board[2][2] != BLANK
       ) {
      return true; //board filled
    }
    else {
      return false; //board not filled
    }
  }

  //check for a tie --> board completely filled up BUT no winner
  bool checkTie(int board[ROWS][COLS]) {
    if(checkBoard(board) == true && checkWin(board) == 0) {
      return true;
    }
    return false;
  }
  
