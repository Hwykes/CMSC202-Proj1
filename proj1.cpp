/* Title: proj1.cpp
** Author: Henry Wykes
** Date: 9/16/2021
** Description: This application will allow the user to play a game of
** word search, taking in a text file and splitting it into an array.
** Course/Section: CMSC 202 Section 21 (FA21)
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

//Constants
const int xMax = 15;
const int yMax = 15;
const int numWords = 11;

//Function Prototypes
void fillGrid(string grid[][yMax], int numRows);
void userGreet();
string fileChoice();
void loadFile(string grid[][yMax], int numRows, string remWords[], string fileName);
void printPuzzle(string grid[][yMax], int numRows);
void printWords(string remWords[]);
string getWord(string grid[][yMax], int numRows);
string makeWordHorizontal(string grid[][yMax], int numRows, int firstX, int firstY, int secondX, int secondY);
string makeWordVertical(string grid[][yMax], int numRows, int firstX, int firstY, int secondX, int secondY);
string makeWordDiagonal(string grid[][yMax], int numRows, int firstX, int firstY, int secondX, int secondY);
int checkWord(string word, string remWords[], int wordsLeft);

//Main Function
int main(){
  //creates game grid, word list, and string to hold created word
  string grid[xMax][yMax];
  string remWords[numWords];
  string potentialWord;
  fillGrid(grid, xMax);
  string file;
  int wordsLeft = 10;
  //greats the user, asks for a file name, and loads the file
  userGreet();
  file = fileChoice();
  loadFile(grid, xMax, remWords, file);
  //Prints the puzzle/remaining words, and gets the coordinates from the user to create
  //a word and checks it until there are no words remaining
  while (wordsLeft != 0){
    printPuzzle(grid, xMax);
    printWords(remWords);
    potentialWord = getWord(grid, xMax);
    wordsLeft = checkWord(potentialWord, remWords, wordsLeft);
  }
  //Thanks the user for playing and stops the program 
  cout << "Thank you for playing UMBC Word Search!" << endl;
  
  return 0;
}

//Fills in the word search grid
void fillGrid(string grid[][yMax], int numRows){
  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < yMax; j++){
      grid[i][j] = "0";
    }
  }
}

//Greets the user
void userGreet(){
  cout << "Welcome to UMBC Word Search" << endl;
}

//Asks the user what file they want to open
string fileChoice(){
  string choice;
  cout << "What is the name of the file you would like to load?" << endl;
  cin >> choice;
  return choice;
}

//Loads the file into the application
void loadFile(string grid[][yMax], int numRows, string wordArray[], string fileName){
  int letterCount = 0;
  int wordCount = -1;
  ifstream myFile (fileName);
  if(myFile.is_open()){
    for (int i = 0; i < numRows; i++){
      for (int j = 0; j < yMax; j++){
	myFile >> grid[i][j];
	letterCount++;
      }
    }
    for (int i = 0; i < numWords; i++){
      getline(myFile, wordArray[i]);
      wordCount++;
    }
    cout << letterCount << " letters imported." << endl;
    cout << wordCount << " words imported." << endl;
  }
  else{
    cout << "Unable to open file" << endl;
  }
  myFile.close();
}

//Iterates through the created and filled game grid to print it out for the user each guess
void printPuzzle(string grid[][yMax], int numRows){
  int numbersRowCol = -1;
  int counterCol = 0;
  int counterRow = -1;
  int spacing = 10;
  for (int i = numbersRowCol; i < numRows; i++){
    for (int j = numbersRowCol; j < yMax; j++){
      if (i == numbersRowCol && j == numbersRowCol){
	cout << "    ";
	counterRow++;
      }
      else if (i == numbersRowCol){
	if (counterRow < spacing){
	  cout << counterRow << "  ";
	}
	else {
	  cout << counterRow << " ";
	}
	counterRow++;
      }
      else if (j == numbersRowCol){
	cout << counterCol << "  ";
	if (counterCol < spacing){
	  cout << " ";
	}
	counterCol++;
      }
      else{
	cout << grid[i][j] << "  ";
      }
    }
    cout << endl;
  }
  cout << endl;
}

//Creates a word from the given coordinates, using other functions based on which direction the
//coordinates are
string getWord(string grid[][yMax], int numRows){
  string word;
  int firstX;
  int firstY;
  int secondX;
  int secondY;
  cout << "What is the starting X Y (seperated by a space)?" << endl;
  cin >> firstX >> firstY;
  cout << "What is the ending X Y (seperated by a space)?" << endl;
  cin >> secondX >> secondY;
  //Verifies that the user has guessed coordinates within the grid
  while (firstX > numRows - 1|| firstX < 0 || firstY > yMax - 1 || firstY < 0 ||
      secondX > numRows - 1 || secondX < 0 || secondY > yMax - 1 || secondY < 0){
    cout << "That point is not in the grid" << endl;
    cout << endl;
    cout << "What is the starting X Y (seperated by a space)?" << endl;
    cin >> firstX >> firstY;
    cout << "What is the ending X Y (seperated by a space)?" << endl;
    cin >> secondX >> secondY;
  }
  //Checks to see if the coordinates are on the same axis or are diagonal
  //to determine which function to call
  if (firstX == secondX){
    word = makeWordHorizontal(grid, numRows, firstX, firstY, secondX, secondY);
    return word;
  }
  else if (firstY == secondY){
    word = makeWordVertical(grid, numRows, firstX, firstY, secondX, secondY);
    return word;
  }
  else{
    word = makeWordDiagonal(grid, numRows, firstX, firstY, secondX, secondY);
    return word;
  }
  
}
//Creates a word horizontally forwards or backwards depending on which Y value is higher
string makeWordHorizontal(string grid[][yMax], int numRows, int firstX, int firstY, int secondX, int secondY){
  string word;
  if (firstY < secondY){
    for (int j = firstY; j < secondY + 1; j++){
      word += grid[firstX][j];
    }
    return word;
  }
  else{
    for (int j = firstY; j > secondY - 1; j--){
      word += grid[firstX][j];
    }
    return word;
  }
}
//Creates a word vertically forwards or backwards depending on which X value is higher
string makeWordVertical(string grid[][yMax], int numRows, int firstX, int firstY, int secondX, int secondY){
  string word;
  if (firstX < secondX){
    for (int i = firstX; i < secondX + 1; i++){
      word += grid[i][firstY];
    }
    return word;
  }
  else{
    for (int i = firstX; i > secondX - 1; i--){
      word += grid[i][firstY];
    }
    return word;
  }
}
//Creates a word diagonally based on which diagonal direction the coordinates go
string makeWordDiagonal(string grid[][yMax], int numRows, int firstX, int firstY, int secondX, int secondY){
  string word;
  //Checks down and to the right
  if (firstX < secondX && firstY < secondY){
    for (int i = firstX; i < secondX + 1; i++){
      for (int j = firstY; j < secondY + 1; j++){
	if (i == firstX && j == firstY){
	  word += grid[i][j];
	}
	else if (i == firstX + 1 && j == firstY + 1){
	  word += grid[i][j];
	  firstX++;
	  firstY++;
	}
	else if (i == secondX && j == secondY){
	  word += grid[i][j];
	}
      }
    }
    return word;
  }
  //Checks up and to the right
  else if (firstX > secondX && firstY < secondY){
    for (int i = firstX; i > secondX - 1; i--){
      for (int j = firstY; j < secondY + 1; j++){
	if (i == firstX && j == firstY){
	  word += grid[i][j];
	}
	else if (i == firstX - 1 && j == firstY + 1){
	  word += grid[i][j];
	  firstX--;
	  firstY++;
	}
	else if (i == secondX && j == secondY){
	  word += grid[i][j];
	}
      }
    }
    return word;
  }
  //Checks down and to the left
  else if (firstX < secondX && firstY > secondY){
    for (int i = firstX; i < secondX + 1; i++){
      for (int j = firstY; j > secondY - 1; j--){
	if (i == firstX && j == firstY){
	  word += grid[i][j];
	}
	else if (i == firstX + 1 && j == firstY - 1){
	  word += grid[i][j];
	  firstX++;
	  firstY--;
	}
	else if (i == secondX && j == secondY){
	  word += grid[i][j];
	}
      }
    }
    return word;
  }

  //Checks up and to the left
  else if (firstX > secondX && firstY > secondY){
    for (int i = firstX; i > secondX - 1; i--){
      for (int j = firstY; j > secondY - 1; j--){
	if (i == firstX && j == firstY){
	  word += grid[i][j];
	}
	else if (i == firstX - 1 && j == firstY - 1){
	  word += grid[i][j];
	  firstX--;
	  firstY--;
	}
	else if (i == secondX && j == secondY){
	  word += grid[i][j];
	}
      }
    }
    return word;
  }
  else {
    return " ";
  }
}
	  
//Checks to see if a word from the list is formed from the word created in the coordinates
int checkWord(string word, string remWords[], int wordsLeft){
  int wordSizeOne = word.length();
  for (int i = 1; i < numWords; i++){
    bool foundWord = true;
    int wordSizeTwo = remWords[i].length() - 1;
    if (wordSizeOne == wordSizeTwo){
      for (int j = 0; j < wordSizeTwo; j++){
	if (word[j] != remWords[i][j]){
	  foundWord = false;
	}
      }
      if (foundWord == true){
	cout << "You have found the word " << word << "!" << endl;
	wordsLeft--;
	remWords[i] = "";
	return wordsLeft;
      }
    }
  }
  cout << "You didn't find a word." << endl;
  return wordsLeft;
}
  
//Prints out the remaining words for the user before each guess
void printWords(string wordArray[]){
  cout << "*********REMAINING WORDS*********" << endl;
  for (int i = 0; i < numWords; i++){
    if (wordArray[i] != ""){
      cout << wordArray[i] << endl;
    }
  }
}
