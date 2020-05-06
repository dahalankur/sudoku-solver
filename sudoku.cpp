/*
 * sudoku.cpp
 * A C++ sudoku solver
 * Author: Ankur Dahal
 * Date: 05/05/2020
*/


#include <iostream>
#include <string>
#include <fstream>

using namespace std; 

/* the sudoku board (indicate empty spots with 0) */
int grid[9][9] = 
                    {
                        {0, 2, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 6, 0, 0, 0, 0, 3},
                        {0, 7, 4, 0, 8, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 3, 0, 0, 2},
                        {0, 8, 0, 0, 4, 0, 0, 1, 0},
                        {6, 0, 0, 5, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 0, 7, 8, 0},
                        {5, 0, 0, 0, 0, 9, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 4, 0}
                    };

const int ROWS = 9;
const int COLUMNS = 9;


/* function declarations */
bool isGridValid();
bool inValidRange(int value, int low, int high);
void printBoard();
bool canEnterNumber(int row, int col, int value);
bool valueInRow(int row, int value);
bool valueInColumn(int col, int value);
bool valueInSquare(int row, int col, int value);
bool canFindNextEmptySpot(int &row, int &col);
bool solveSudoku(int row, int col);
void setGrid(istream &infile);
/* end of function declarations */


int main (int argc, char **argv) {
    if (argc == 2) { /* take input from file */
        string filename = argv[1];
        ifstream infile(filename.c_str());
        if (infile.fail()) {
            cerr << "Cannot read the file " + filename + "\n";
            exit(1);
        }
        setGrid(infile);
        infile.close();
    }
    
    if (not isGridValid()) {
        cerr << "The entered grid is invalid." << 
                " Please check the input and try again.\n";
        exit(1);
    }

    cout << "Before solving, the board: \n";
    printBoard();

    if (solveSudoku(0, 0)) {
        cout << "After solving, the board: \n";
        printBoard();
    } else {
        cout << "No solutions could be found.\n";
    }

    return 0;
}


void setGrid(istream &infile) {
    int value = -1;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            infile >> value;
            grid[i][j] = value;
        }
    }
}



/*  function solveSudoku
    parameters: none
    returns: bool
    does: solves the sudoku puzzle. Returns true if sudoku can be solved,
          otherwise returns false
*/
bool solveSudoku(int row, int col) {
    /* base case: no empty spots in the grid */
    if (not canFindNextEmptySpot(row, col)) 
        return true; 
    
    /* if there is an empty spot, try inserting values there */
    for (int value = 1; value <= 9; ++value) {
        if (canEnterNumber(row, col, value)) {
            grid[row][col] = value;
            if (solveSudoku(row, col))
                return true;
            else 
                grid[row][col] = 0; /* backtrack if can't solve with this
                                        number */    
        }    
    }

    return false; /* can't solve */
}



/*  function canFindEmptySpot
    parameters: int &row - row of the board
                int &col - column of the board
    returns: bool
    does: returns true if an empty spot can be found in grid,
          otherwise returns false
    Note: Since row and col are passed by reference, they get the 
            value of the next free location in the grid in the 
            function that calls this function
*/
bool canFindNextEmptySpot(int &row, int &col) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}



/*  function canEnterNumber
    parameters: int row - row of the board
                int col - column of the board
                int value - value to be inserted in the board
    returns: bool
    does: returns true if value can be inserted in the board, 
          otherwise returns false
*/
bool canEnterNumber(int row, int col, int value) {
    return ((not valueInRow(row, value)) and (not valueInColumn(col, value))
                    and (not valueInSquare(row, col, value)));
}



/*  function isGridValid
    parameters: none
    returns: bool
    does: returns true if the grid is a valid sudoku board,
          otherwise returns false
*/
bool isGridValid() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (not inValidRange(grid[i][j], 0, 9)) 
                return false; 
        }
    }
    return true;
}



/*  function inValidRange
    parameters: int value - the value in the grid
                int low - lower bound of the allowed value
                int high - upper bound of the allowed value 
    returns: bool
    does: returns true if the value is a valid integer within
          the range [low, high] inclusive, otherwise returns
          false
*/
bool inValidRange(int value, int low, int high) {
    return (value >= low) and (value <= high);
}



/*  function printBoard
    parameters: none
    returns: nothing
    does: prints the board state to std::cout
*/
void printBoard() {
    for (int i = 0; i < ROWS; ++i) {
        cout << "\n         | ";
        for (int j = 0; j < COLUMNS; ++j) {
            string value = (grid[i][j] == 0)? ".": to_string(grid[i][j]);
            cout << value << " | ";
        }
        cout << "\n";
    }
    cout << "\n";
    
}



/*  function valueInRow
    parameters: int row - row of the board
                int value - value to be inserted in the board
    returns: bool
    does: returns true if value is already present in the row 
          of the board, else returns false
*/
bool valueInRow(int row, int value) {
    for (int i = 0; i < COLUMNS; ++i) {
        if (grid[row][i] == value) 
            return true;
    }
    return false;
}



/*  function valueInColumn
    parameters: int col - column of the board
                int value - value to be inserted in the board
    returns: bool
    does: returns true if value is already present in the column 
          of the board, else returns false
*/
bool valueInColumn(int col, int value) {
    for (int i = 0; i < ROWS; ++i) {
        if (grid[i][col] == value) 
            return true;
    }
    return false;
}



/*  function valueInSquare
    parameters: int row - row of the board
                int col - column of the board
                int value - value to be inserted in the board
    returns: bool
    does: returns true if value is already present in the 3x3 square
          of the sudoku board, else returns false
*/
bool valueInSquare(int row, int col, int value) {
    /* computing the coordinates of the square where value might be located */
    int square_row = (row / 3) * 3; 
    int square_col = (col / 3) * 3;

    /* iterate through the elements of the square to check if value exists in 
       one of the spots */
    for (int i = square_row; i < square_row + 3; ++i) {
        for (int j = square_col; j < square_col + 3; ++j) {
            if (grid[i][j] == value)
                return true;
        }
    }
    return false;
}

