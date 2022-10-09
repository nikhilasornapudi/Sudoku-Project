//
//  Sudoku Project.cpp
//
//
//  Created by Nikhila Sornapudi on 20/09/22.
//

#include<iostream>
#include<cstdlib>
#include<cstdbool>
#include<string>
using namespace std;

class Puzzle
{
public:
    int** createPuzzle(int);
    void printPuzzle(int** puzzle);
    bool checkAvailable(int** puzzle, int* row, int* column);
    bool checkBox(int** puzzle, int row, int column, int val);
    bool solvePuzzle(int** puzzle);
    int** copyPuzzle(int** puzzle);
    void userChoice(int** userPuzzle, int** tempPuzzle);
};

int** Puzzle::createPuzzle(int choice)
{
    int i, j;
    int** puzzle;
    if (choice == 1) {
    int arrayPuzzle[9][9] = { 9, 8, 7,   4, 0, 3,   0, 2, 6,
                              0, 0, 0,   2, 0, 6,   9, 0, 0,
                              0, 0, 5,   0, 0, 0,   0, 0, 1,

                              0, 0, 1,   0, 0, 8,   0, 0, 7,
                              0, 9, 3,   0, 6, 0,   8, 4, 0,
                              8, 0, 0,   3, 0, 7,   6, 0, 0,

                              5, 0, 0,   0, 0, 2,   1, 6, 0,
                              0, 0, 9,   6, 0, 4,   0, 0, 0,
                              4, 7, 0,   5, 0, 0,   0, 9, 3, };
         puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            puzzle[i][j] = arrayPuzzle[i][j];
        }
    }
    return puzzle;
    }
    else if (choice == 2) {
    int arrayPuzzle[9][9] = { 9, 8, 0,   4, 0, 3,   0, 2, 6,
                              0, 0, 0,   2, 0, 6,   9, 0, 0,
                              0, 0, 5,   0, 0, 0,   0, 0, 1,

                              0, 0, 1,   0, 0, 8,   0, 0, 7,
                              0, 9, 3,   0, 6, 0,   8, 4, 0,
                              8, 0, 0,   0, 0, 7,   0, 0, 0,

                              5, 0, 0,   0, 0, 2,   1, 6, 0,
                              0, 0, 9,   6, 0, 0,   0, 0, 0,
                              4, 0, 0,   5, 0, 0,   0, 9, 3, };
                               puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            puzzle[i][j] = arrayPuzzle[i][j];
        }
    }
    return puzzle;
    }
    else if (choice == 3) {
    int arrayPuzzle[9][9] = { 0, 8, 7,   4, 0, 0,   0, 2, 6,
                              0, 0, 0,   2, 0, 0,   9, 0, 0,
                              0, 0, 5,   0, 0, 0,   0, 0, 0,

                              0, 0, 1,   0, 0, 8,   0, 0, 0,
                              0, 9, 0,   0, 6, 0,   8, 4, 0,
                              8, 0, 0,   3, 0, 0,   6, 0, 0,

                              5, 0, 0,   0, 0, 0,   1, 6, 0,
                              0, 0, 9,   6, 0, 4,   0, 0, 0,
                              4, 0, 0,   5, 0, 0,   0, 9, 0, };
                               puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            puzzle[i][j] = arrayPuzzle[i][j];
        }
    }
    return puzzle;
    }
    return 0;
}

void Puzzle::printPuzzle(int** puzzle)
{
    int i, j, a;
    cout<<"\n";
    cout<<" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n";
    cout<<" ---------------------------------\n";
    for (i = 0, a = 1; i < 9; i++, a++){
        for(j = 0; j < 9; j++){
            if (j == 0)
                cout<<"|"<<a;
            else if ((j) % 3 == 0)
                cout<<"|";
            printf(" %d ", puzzle[i][j]);
            if (j == 8)
                cout<<"|";
        }
        cout<<"\n";
        if ((i + 1) % 3 == 0)
            cout<<" ---------------------------------\n";
    }
    cout<<" Y\n";
}

bool Puzzle::checkAvailable(int** puzzle, int* row, int* column){
    int i, j;

    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (puzzle[i][j] == 0){
                *row = i;
                *column  = j;
                return true;
            }
        }
    }

    return false;
}

bool Puzzle::checkBox(int** puzzle, int row, int column, int val){
    int i, j;
    int squareRow, squareColumn;

    //CHECK VERTICAL
    for(i = 0; i < 9; i++){
        if (puzzle[i][column] == val)
            return false;
    }

    //CHECK HORIZONTAL
    for(j = 0; j < 9; j++){
        if (puzzle[row][j] == val)
            return false;
    }

    //CHECK SQUARE
    squareRow = row - row % 3;
    squareColumn = column - column % 3;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(puzzle[squareRow + i][squareColumn + j] == val)
                return false;
        }
    }
    return true;
}

bool Puzzle::solvePuzzle(int** puzzle){
    int i, j, val;

    if(!checkAvailable(puzzle, &i, &j))
        return true;

    for(val = 1; val < 10; val++){
        if(checkBox(puzzle, i, j, val)){
            puzzle[i][j] = val;
            if(solvePuzzle(puzzle))
                return true;
            else
                puzzle[i][j] = 0;
        }
    }
    return false;
}

int** Puzzle::copyPuzzle(int** puzzle){
    int i, j;
    int** newPuzzle;

    newPuzzle = (int**)malloc(sizeof(int*) * 9);
    for (i = 0; i < 9; i++){
        newPuzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            newPuzzle[i][j] = puzzle[i][j];
        }
    }
    return newPuzzle;
}

void Puzzle::userChoice(int** userPuzzle, int** tempPuzzle){
    int i, j;
    int positionX, positionY, userVal;
    char c;

    while(1){
    if(!checkAvailable(userPuzzle, &i, &j)){
        cout<<"\nCongrats You Solved the Puzzle!!!\n";
        return;
    }

    while(1){
        cout<<"\nPress Enter to continue or Press \"q\" to Quit.\n";
        c = getchar();
        if((c == 'q') || (c == 'Q')){
            getchar();
            solvePuzzle(userPuzzle);
            cout<<"\nSOLVED PUZZLE:\n";
            printPuzzle(userPuzzle);
            return;
        }
        else if((c != '\n') && (c != 'q'))
            getchar();
        else
            break;
    }


    cout<<"\nplease Enter Coordinate for the square you want to insert the value to in the following format \"X Y\":\n";
    cin>>positionX>>positionY;
    while(1){
        if ((positionX > 9) || (positionX < 1) || (positionY > 9) || (positionY < 1) || (userPuzzle[positionY - 1][positionX - 1] != 0)){
            cout<<"\nyou can't insert value to this Coordinate, please pick a new Coordinate\n";
            cin>>positionX>>positionY;
        }
        else {
            positionX -= 1;
            positionY -= 1;
            break;
        }
    }


    cout<<"\nPlease insert value from 1 to 9\n";
    cin>>userVal;
    while(1){
        if((userVal > 9) || (userVal < 1)){
            cout<<"\nplease insert valid value:\n";
            cin>>userVal;
        }
        else break;
    }

    if(checkBox(userPuzzle, positionY, positionX, userVal))
        userPuzzle[positionY][positionX] = userVal;
    else
        cout<<"\nincorrect value for the X = "<<positionX + 1<<" coordinate and  Y = "<<positionY + 1<<" coordinate, please try again\n";

    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            tempPuzzle[i][j] = userPuzzle[i][j];
        }
    }

    if(!solvePuzzle(tempPuzzle)){
        cout<<"\nincorrect value for the X = "<<positionX + 1<<" coordinate and  Y = "<<positionY + 1<<" coordinate, please try again\n";
        userPuzzle[positionY][positionX] = 0;
    }
    getchar();
    printPuzzle(userPuzzle);
    }

    return;
}

int main()
{
    Puzzle myobj;
    string str;
    int** spuzzle = nullptr;
    int choice;
    cout<<"Enter player Name: ";
    cin>>str;
    cout<<"\nChoose a gameplay mode\n";
    cout<<"1 - Easy\n";
    cout<<"2 - Medium\n";
    cout<<"3 - Hard\n";
    
    cin>>choice;
 
    if(choice == 1)
    {
        cout<<"The puzzle has been generated with easy difficulty\n";
        spuzzle = myobj.createPuzzle(choice);
    }
    else if(choice == 2)
    {
        cout<<"The puzzle has been generated with medium difficulty\n";
        spuzzle = myobj.createPuzzle(choice);
    }
    else
    {
        cout<<"The puzzle has been generated with hard difficulty\n";
        spuzzle = myobj.createPuzzle(choice);
    }
    
    int** userPuzzle = myobj.copyPuzzle(spuzzle);
    int** tempPuzzle = myobj.copyPuzzle(spuzzle);
    cout<<"\nRULES:\n";
    cout<<"1. The objective of Sudoku is to fill a 9x9 grid made of small squares so that each row, each column, and each full 3x3 squares use the numbers 1-9.\n";
    cout<<"2. While solving the sudoku puzzle you can only use each number one time in the square, column, and row.\n";
    cout<<"3. You can only insert numbers in the squares that have value \"0\"\n";
    cout<<"4. If you give up and want to see a solved puzzle please press \"q\" key.\n\n";
    cout<<"GOOD LUCK!\n";
    myobj.printPuzzle(userPuzzle);
    myobj.userChoice(userPuzzle,tempPuzzle);
    free(spuzzle);
    free(userPuzzle);
    free(tempPuzzle);
}

