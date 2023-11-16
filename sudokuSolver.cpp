

#include <iostream>
#include <vector>

/*

Author: Nekruz Ashrapov

enjoy!



*/



/*
*   find_next_empty()
*   
*   This function checks for any empty spaces in the puzzle board
*   using -1 for empty spaces
*   
*   inputs: This function has 3 input parameters such as 2 of int types
*   row and col, and one of a matrix which consists of a type vector 
*   of vector of ints. Which will serve as the main puzzle board (object).
*   All of them are passed by reference
*   
*   Output: This function has a return type of a bool, which means that it will
*   return true when the function reads an empty box and false otherwise.
* 
*/

bool find_next_empty(const std::vector<std::vector<int>>& board, int& row, int& col) {

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {                                              // using -1 for empty spaces

            if (board[row][col] == -1) {

                return true;

            }


        }


    }

    return false;

}

/*
*   is_valid()
*
*   This function checks whether a given guess is valid in the context of the Sudoku puzzle.
*   It validates the guess against the row, column, and the 3x3 subgrid in which the cell is located.
*
*   Inputs:
*       - board: A 9x9 Sudoku puzzle represented as a vector of vectors of integers.
*       - col: The column index of the cell being checked.
*       - row: The row index of the cell being checked.
*       - guess: The number being checked for validity in the cell.
*
*   Output:
*       - Returns a boolean value:
*           - True if the guess is valid in the given row, column, and subgrid.
*           - False if the guess violates the rules of Sudoku in any of the mentioned contexts.
*
*/

bool is_valid(const std::vector<std::vector<int>>& board, int col, int row, int guess) {

    //check row
    for (int c = 0; c < 9; c++) {
        if (board[row][c] == guess) {

            return false;

        }
        
    }

    //check column
    for (int r = 0; r < 9; r++) {
        if (board[r][col] == guess) {

            return false;

        }

    }

    //check subgrid
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;

    for (int r = row_start; r < row_start + 3; r++) {
        for (int c = col_start; c < col_start + 3; c++) {
            if (board[r][c] == guess) {

                return false;

            }


        }


    }

    return true;

}

/*
*   solve_sudoku()
*
*   This function implements a backtracking algorithm to solve a given Sudoku puzzle.
*   It recursively fills in the empty cells of the puzzle, making guesses and backtracking
*   when needed until a valid solution is found or it determines that no solution exists.
*
*   Input:
*       - board: A 9x9 Sudoku puzzle represented as a vector of vectors of integers.
*               The puzzle is modified in place to store the solved configuration.
*
*   Output:
*       - Returns a boolean value:
*           - True if a solution is found for the given Sudoku puzzle.
*           - False if no solution exists for the provided puzzle.
*
*/

bool solve_sudoku(std::vector<std::vector<int>>& board) {

    int row, col;

    if (!find_next_empty(board, row, col)) {

        return true; // Puzzle solved!

       }

    for (int guess = 1; guess <= 9; guess++) {
        if (is_valid(board, col, row, guess)) {
            board[row][col] = guess;

            if (solve_sudoku(board)) {

                return true;
            }

            board[row][col] = -1; //backtrack

        }

    }

    return false; //no solution found

}





int main()
{
    
    std::vector<std::vector<int>> example = {

        {4, -1, -1, -1, -1, -1, -1, 1, -1},
        {-1, -1, -1, -1, 6, 9, 5, -1, 8},
        {-1, 6, -1, 5, -1, 1, -1, -1, -1},
        {-1, 2, 6, 7, -1, 5, 4, 8, 3},
        {-1, 4, 7, -1, 8, -1, -1, -1, -1},
        {-1, 3, 1, 9, 4, 2, -1, 6, 5},
        {6, -1, -1, 2, -1, -1, 1, -1, 4},
        {2, 8, -1, -1, -1, -1, -1, 5, 7},
        {-1, 5, -1, -1, 9, -1, -1, -1, -1}

    };

    if (solve_sudoku(example)) {
        //print the solved puzzle
        for (const auto& row : example) {
            for (int value : row) {

                std::cout << value << " ";

            }

            std::cout << std::endl;
        }


    }
    else{

        std::cout << "No solution found." << std::endl;
    
    }

        return 0;

}

