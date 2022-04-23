// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "strlib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"

using namespace std;

void printGrid(Grid<char>& matrix){
    for(int r = 0; r < matrix.numRows(); r++) {
        for(int c = 0; c < matrix.numCols(); c++) {
            cout << matrix[r][c];
        }
        cout << endl;
    }
}

int detectSurround(Grid<char>& matrix, int r, int c, int row, int column) {
    // situation 1: A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it dies.
    int numX = 0;
    if(c-1 > 0) {
        if(matrix[r][c-1] == 'X') {
            numX++;
        }
    }
    if(c+1 < column) {
        if(matrix[r][c+1] == 'X') {
            numX++;
        }
    }

    if(r-1 > 0) {
        if(matrix[r-1][c] == 'X') {
            numX++;
        }
        if(c-1 > 0) {
            if(matrix[r-1][c-1] == 'X') {
                numX++;
            }
        }
        if(c+1 < column) {
            if(matrix[r-1][c+1] == 'X') {
                numX++;
            }
        }
    }
    if(r+1 < row) {
        if(matrix[r+1][c] == 'X') {
            numX++;
        }
        if(c-1 > 0){
            if(matrix[r+1][c-1] == 'X') {
                numX++;
            }
        }
        if(c+1 < column) {
            if(matrix[r+1][c+1] == 'X') {
                numX++;
            }
        }
    }
    return numX;
}

Grid<char> generation(Grid<char>& matrix, int row, int column) {
    int neighbors;
    Grid<char> newmatrix(row, column);
    for (int r = 0; r < matrix.numRows(); r++) {
        for (int c = 0; c < matrix.numCols(); c++) {
            neighbors = detectSurround(matrix, r, c, row, column);
            //cout << "r, c, neighbors: " << r << c << neighbors << endl;
            if (neighbors <= 1) {
                newmatrix[r][c] = '-';
            } else if (neighbors == 3) {
                newmatrix[r][c] = 'X';
            } else if (neighbors >= 4) {
                newmatrix[r][c] = '-';
            } else {
                newmatrix[r][c] = matrix[r][c];
            }
        }
    }
    return newmatrix;
}

int main() {
    // TODO: Finish the program!
    ifstream stream;
    string line;
    string mode;
    string frames;
    int c;

    string filename = promptUserForFile(stream, "Grid file name?");
    getline(stream, line);
    int row = stringToInteger(line);
    cout << "rows: " << row << endl;
    getline(stream, line);
    int column = stringToInteger(line);
    cout << "columns: " << column << endl;
    Grid<char> matrix(row, column);
    for (int r = 0; r < row; r++) {
        getline(stream, line);
        c = 0;
        for (char symbol : line) {
            matrix[r][c] = symbol;
            c++;
        }
    }
    stream.close();
    printGrid(matrix);
    while (1) {
        mode = getLine("a)nimate, t)ick, q)uit?");
        mode = toLowerCase(mode);
        if (mode == "a") {
           frames = getLine("How many frames?");
           for (int i = 0; i < stringToInteger(frames); i++) {
               // one generation
               matrix = generation(matrix, row, column);
               clearConsole();
               printGrid(matrix);
               pause(50);
           }
        } else if (mode == "t") {
            // one generation
            matrix = generation(matrix, row, column);
            printGrid(matrix);
        } else if (mode == "q") {
            // quit the game
            break;
        }
    }
    cout << "Have a nice Life!" << endl;

    return 0;
}

