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

int main() {
    // TODO: Finish the program!
    ifstream stream;
    string line;
    int c;

    string filename = promptUserForFile(stream, "Grid file input?");
    getline(stream, line);
    int row = stringToInteger(line);
    cout << "rows: " << row << endl;
    getline(stream, line);
    int column = stringToInteger(line);
    cout << "columns: " << column << endl;
    Grid<char> matrix(row, column);
    for (int r = 0; r < row; r++){
        getline(stream, line);
        c = 0;
        for(char symbol : line) {
            matrix[r][c] = symbol;
            c++;
        }
    }
    //cout << "matrix: " << matrix;
    stream.close();
    cout << "Have a nice Life!" << endl;
    printGrid(matrix);
    return 0;
}

