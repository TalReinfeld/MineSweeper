
/* This program let the user to choose a size for a board,
then gets two numbers from the user and translate them to a row and a column in the board.
if there are no mines in the place that he chose, the place will revealed and if there is a mine the game will be over. */
//A place in the array will be called a "cell".

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define ROWS 22
#define COLS 22

int mainMenu();
void initDisplayBoard(char board[ROWS][COLS]);
void plantMines(int board[ROWS][COLS], int numberOfRows, int numberOfCols);
void plantNumbers(int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols);
void printDisplayBoard(char arr[ROWS][COLS], int numberOfRows, int numberOfCols);
void updateDisplayBoard(char displayBoard[ROWS][COLS], int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols);
void initDataBoard(int board[ROWS][COLS], int numberOfRows, int numberOfCols);
void printLine(char shape, int HowMuch);
void printDataBoard(int arr[ROWS][COLS], int numberOfRows, int numberOfCols);
void cheat(char displayBoard[ROWS][COLS], int col, int dataBoard[ROWS][COLS], int numberOfCols, int numberOfRows);
void gameOver(int dataBoard[ROWS][COLS], char displayBoard[ROWS][COLS], int numberOfRows, int numberOfCols);
void openZeros(char displayBoard[ROWS][COLS], int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols, int row, int col);

void main()
{
    int userChoice = 0, numberOfRows = 0, numberOfCols = 0;
    userChoice = mainMenu();
    while (userChoice != 0)   //If the user will choce 0 he will exit the program.
    {
        if (userChoice < 0 || userChoice > 4)   //If the user will chose a size that is not on the list he will be asked again for size.
        {
            printf("Invalid choice");
            printf("\n");
            userChoice = mainMenu();
        }
        else    // If the user will choose a possible size, he will start the game.
        {
            switch (userChoice)
            {
            case 1:    //1 for 8X8 board.
                numberOfRows = numberOfCols = 8;
                break;

            case 2:    //2 for 12X12 board.
                numberOfRows = numberOfCols = 12;
                break;

            case 3:    //3 for 15X15 board.
                numberOfRows = numberOfCols = 15;
                break;

            case 4:   //4 for custom size.
                printf("Please choose the size of your board by 2 numbers between 1 to 22,\nthe first will be the number of rows and the second will be the number of columns: ");
                scanf("%d%d", &numberOfRows, &numberOfCols);
                break;
            }
            char DisplayBoard[ROWS][COLS];
            int DataBoard[ROWS][COLS];
            initDisplayBoard(DisplayBoard);    //make the Display Board.
            initDataBoard(DataBoard, numberOfRows, numberOfCols);      //make the Data Board.
            printDisplayBoard(DisplayBoard, numberOfRows, numberOfCols);   //print the Display Board.
            printf("\n");
            //printDataBoard(DataBoard, numberOfRows, numberOfCols);        //This function prits the Data board, only for checkings.
            updateDisplayBoard(DisplayBoard, DataBoard, numberOfRows, numberOfCols);   //The gameplay.
            return;
        }
    }
    printf("Good bye");
}

int mainMenu()      //This function will be displayed at the beginning of the game, and will get a choice of the size from the user.
{
    int userChoice = 0;

    printLine('*', 45);
    printf("*           Welcome to Minesweeper          *\n");
    printf("* Please choose size and enter it's number: *\n");
    printf("* 1. 8X8                                    *\n");
    printf("* 2. 12X12                                  *\n");
    printf("* 3. 15X15                                  *\n");
    printf("* 4. Custom size                            *\n");
    printf("* 0. EXIT                                   *\n");
    printLine('*', 45);
    printf("\n");
    scanf("%d", &userChoice);
    return userChoice;
}

void initDisplayBoard(char board[ROWS][COLS])     //This function will update a two dimensional array of random values to an array of 'X'.
{
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            board[row][col] = 'X';
}

void initDataBoard(int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols) //This function takes the relevant size of the two dimensional array and update it to an array of numbers between -1 to 8.
{    
    for (int row = 0; row < numberOfRows; row++)     //This for loop will replace all the "Data Board" to an array of 0.
        for (int col = 0; col < numberOfCols; col++)
            dataBoard[row][col] = 0;

    for (int i = 0; i < numberOfRows; i++)
    {
        plantMines(dataBoard, numberOfRows, numberOfCols);
    }
    plantNumbers(dataBoard, numberOfRows, numberOfCols);
}


void plantMines(int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols)  //This function update the data board with mines (-1) on random places. Will be used only in the amount of the square root of the cols multiple the rows times in the "init data board".
{    
    srand(time(NULL));
    while (true)
    {
        int yCoordinate, xCoordinate, numOfMines;
        numOfMines = sqrt(numberOfRows * numberOfCols);
        yCoordinate = rand() % numOfMines;
        xCoordinate = rand() % numOfMines;
        if (dataBoard[yCoordinate][xCoordinate] == -1)
        {
            continue;
        }
        dataBoard[yCoordinate][xCoordinate] = -1;
        return;
    }
}

void plantNumbers(int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols) //This function update the data board by replacing the cells with 0 next to the mines (-1) with the number of mines around them.
{   
    int yCoordinate = 0, xCoordinate = 0;
    int count = 0;

    for (yCoordinate = 0; yCoordinate < numberOfRows; yCoordinate++) {
        for (xCoordinate = 0; xCoordinate < numberOfCols; xCoordinate++)
            if (dataBoard[yCoordinate][xCoordinate] == -1) {
                dataBoard[yCoordinate][xCoordinate] = -1;
            }
            else {
                if (dataBoard[yCoordinate][xCoordinate + 1] == -1 && (xCoordinate + 1) < numberOfCols) {
                    count++;
                }
                if (dataBoard[yCoordinate][xCoordinate - 1] == -1 && (xCoordinate - 1) >= 0) {
                    count++;
                }
                if (dataBoard[yCoordinate + 1][xCoordinate] == -1 && (yCoordinate + 1) < numberOfRows) {
                    count++;
                }
                if (dataBoard[yCoordinate - 1][xCoordinate] == -1 && (yCoordinate - 1) >= 0) {
                    count++;
                }
                if (dataBoard[yCoordinate + 1][xCoordinate + 1] == -1 && (yCoordinate + 1) < numberOfRows && (xCoordinate + 1) < numberOfCols) {
                    count++;
                }
                if (dataBoard[yCoordinate + 1][xCoordinate - 1] == -1 && (yCoordinate + 1) < numberOfRows && (xCoordinate - 1) >= 0) {
                    count++;
                }
                if (dataBoard[yCoordinate - 1][xCoordinate + 1] == -1 && (yCoordinate - 1) >= 0 && (xCoordinate + 1) < numberOfCols) {
                    count++;
                }
                if (dataBoard[yCoordinate - 1][xCoordinate - 1] == -1 && (yCoordinate - 1) >= 0 && (xCoordinate - 1) >= 0) {
                    count++;
                }
                dataBoard[yCoordinate][xCoordinate] = count;
                count = 0;
            }
    }
}

void printDisplayBoard(char arr[ROWS][COLS], int numberOfRows, int numberOfCols)     //This function print the display board.
{
    int row = 0, col = 0;
    printf("    ");
    for (col = 0; col < numberOfCols; col++)
    {
        printf("%2d  ", col);
    }
    printf("\n");
    printLine('_', numberOfCols * 4 + 4);

    for (int i = 0; i < numberOfRows; i++)
    {
        printf("%2d ", row);
        for (int j = 0; j < numberOfCols; j++)
        {
            printf("|");
            printf("%2c ", arr[i][j]);
        }
        printf("|");
        printf("\n");
        row++;
    }
    printLine('_', numberOfCols * 4 + 4);
    printf("\n");
}

void printDataBoard(int arr[ROWS][COLS], int numberOfRows, int numberOfCols)  //This function print the data board. The function will only be implemented during programming.
{
    int row = 0;
    printf("    ");
    for (int col = 0; col < numberOfCols; col++)
    {
        printf("%2d  ", col);
    }
    printf("\n");
    printLine('_', numberOfCols * 4 + 4);
    for (int i = 0; i < numberOfRows; i++)
    {
        printf("%2d ", row);
        for (int j = 0; j < numberOfCols; j++)
        {
            printf("|");
            printf("%2d ", arr[i][j]);
        }
        printf("|");
        printf("\n");
        row++;
    }
    printLine('_', numberOfCols * 4 + 4);
    printf("\n");
}

void updateDisplayBoard(char displayBoard[ROWS][COLS], int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols) {   //This function is the gameplay function that updatethe choices of the user.
    int row = 0, col = 0,  reveals = 0, countZeros = 0;
    char action = 'f';
    while (reveals < (numberOfRows * numberOfCols - sqrt(numberOfRows * numberOfCols)))
    {
        printf("Please enter your move, row, column and an action: ");  //The user will ask for enter two numbers, the first will be defined as the row and the second will be defined as the col.
        scanf("%d%d", &row, &col);

        if (row == -1 && col > 0) {     //If the user enter -1 in the rows place he will replace as many non mines cells as the number that he enter in the cols place in the display board.
            
            reveals += col;
            cheat(displayBoard, col, dataBoard, numberOfCols, numberOfRows);
        }
        else if (row == -1 && col < 1) {      //If the user chose an illegal number for the cheat he will get a message.
            printf("Invalid choice!\n");
            printf("\n");
        }
        else {
            scanf(" %c", &action);   //If the user didnt want to use the cheat he will be asked for an action also- sign or reveal.
            if (action != 'o' && action != 'O' && action != 'f' && action != 'F') {     //If the user chose a an action that doesnt exist he will get a message.

                printf("Invalid choice!\n");
                printf("\n");
            }
            else if ((row < -1 || row >= numberOfRows) || (col < 0) || (-1 <= row && row < numberOfRows && col >= numberOfCols)) {     //If the user chose an illegal numbers he will get a message.

                printf("Invalid choice!\n");
                printf("\n");
            }
            else if (displayBoard[row][col] != 'X' && displayBoard[row][col] != 'F')   //If the user chose a cell that he already reveal he will get a message.
            {
                printf("Invalid choice!\n");
                printf("\n");
            }
            else if (action == 'f' || action == 'F')    //If the user want to sign a place on the Display Board, the letter "F" will replace the cell that he chose.
            {
                displayBoard[row][col] = 'F';
            }
            else if (dataBoard[row][col] > 0)    //If the user chose a cell with a number that it not a 0 on the data board, the number will replace the same cell in the display board.
            {
                displayBoard[row][col] = (char)dataBoard[row][col] + 48;
                reveals++;
            }
            else if (dataBoard[row][col] == 0)   //If the user chose a cell with a 0 on the data board, an empty space will replace the same cell continue to open as many ' ' cells in his area and the numbers that surround them.
            {
                openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row, col);
                for (row = 0; row < numberOfRows; row++) {
                    for (col = 0; col < numberOfCols; col++)
                        if (displayBoard[row][col] == 'X' || displayBoard[row][col] == 'F')
                            countZeros++;
                }
                reveals = numberOfRows * numberOfCols - countZeros;

            }
        }
            printDisplayBoard(displayBoard, numberOfRows, numberOfCols);    //After doing one of the statements above, the new display board will be printed.
            printf("\n");

            if (dataBoard[row][col] == -1 && (action == 'o' || action == 'O'))       //If the user chose a mine, he will finish the game by getting out of the loop.
            {
                printf("You've hit a bomb! Game over!");
                printf("\n");
                gameOver(dataBoard, displayBoard, numberOfRows, numberOfCols);
                printDisplayBoard(displayBoard, numberOfRows, numberOfCols);
                return;
            }
    }
        printf("You won!! congragulations! CHAMPION!\nHope you have enjoyed playing !!!!");    // If the user get out of the loop, not by revealing a mine he will win the game.
    return;
}

void printLine(char shape, int howMuch)    //This function print a line of the same shape.
{
    for (int i = 0; i < howMuch; i++)
    {
        printf("%c", shape);
    }
    printf("\n");
}

void cheat(char displayBoard[ROWS][COLS], int col, int dataBoard[ROWS][COLS], int numberOfCols, int numberOfRows)       //This function reveal as many non mines cells as the user ask for.
{
    int row = 0, count = col;
    col = 0;
    while (count > 0) {
        if (col == numberOfCols) {
            col = 0;
            row = row + 1;
        }
        else {
            if (row >= numberOfRows)
                return;
            else if (displayBoard[row][col] != 'X' && displayBoard[row][col] != 'F') {
                count++;
            }
            else if (dataBoard[row][col] == 0) {
                displayBoard[row][col] = ' ';
            }
            else if (dataBoard[row][col] == -1) {
                count++;
            }
            else if (dataBoard[row][col] > 0) {
                 displayBoard[row][col] = (char)dataBoard[row][col] + 48; 
            }
            count--;
            col++;
        }
    }
}

void gameOver(int dataBoard[ROWS][COLS], char displayBoard[ROWS][COLS], int numberOfRows, int numberOfCols)    // This function transfer the display to the data board.
{
    for (int i = 0; i < numberOfRows; i++) {
        for (int j = 0; j < numberOfCols; j++)
        {
            if (dataBoard[i][j] == -1) {
                displayBoard[i][j] = '*';
            }
            else if (dataBoard[i][j] == 0) {
                displayBoard[i][j] = ' ';
            }
            else {
                displayBoard[i][j] = (char)dataBoard[i][j] + 48;
            }
        }
    }
}

void openZeros(char displayBoard[ROWS][COLS], int dataBoard[ROWS][COLS], int numberOfRows, int numberOfCols, int row, int col)      //This function reveals all the cells with ' ' that in the area of the current cell + all the numbers that surround them. 
{
    if (displayBoard[row][col] != 'X')
        return;
    else if (dataBoard[row][col] == -1)
        return;
    else if (row >= numberOfRows || row < 0 || col >= numberOfCols || col < 0)
        return;
    else if (dataBoard[row][col] > 0 && displayBoard[row][col] == 'X')
    {
        displayBoard[row][col] = (char)dataBoard[row][col] + 48;
        return;
    }
    else if (dataBoard[row][col] == 0 && displayBoard[row][col] == 'X')    // If the cell in the Display Board has ' ' and havent opened yet, the function will continue to open the cells in his area in a recursive way.
    {
        displayBoard[row][col] = ' ';
       
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row + 1, col);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row, col + 1);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row - 1, col);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row, col - 1);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row + 1, col + 1);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row - 1, col - 1);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row - 1, col + 1);
        openZeros(displayBoard, dataBoard, numberOfRows, numberOfCols, row + 1, col - 1);
      
    }
    return;    
}