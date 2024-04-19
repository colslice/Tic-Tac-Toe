#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void printBoard(char board[3][3]);
void computerMove(int *row, int *col);
void clearBoard(char board[3][3]);
int checkFreeSpaces(char board[3][3], int row, int col);
char checkWinner(char board[3][3]);

int main(void)
{
    char player, computer, board[3][3], playAgain;
    player = 'X';
    computer = 'O';
    int free, row, col, freeSpaces;
    char winner;

    
    srand(time(NULL));

    // do-while loop controls one complete game. At the end, checks if player want to play again
    do
    {
        winner = ' ';
        clearBoard(board);
        freeSpaces = 9;

        // loops until a winner is found or there are no more free spaces
        while (winner == ' ' && freeSpaces > 0)
        {

            // the player's move. Row and col decremented to correspond with board array. 
            printBoard(board);
            printf("Please enter the row you'd like to play (Enter 1-3):\n");
            scanf("%d", &row);
            printf("Please enter the column you'd like to play (Enter 1-3):\n");
            scanf("%d", &col);
            row--;
            col--;

            // if free is not equal to 0, the space is already taken
            free = checkFreeSpaces(board, row, col);
            //while loop continues until player picks a non-occupied space
            while (free != 0)
            {
                printf("That position is already taken. Please try again.\n");
                printf("Please enter the row you'd like to play (Enter 1-3):\n");
                scanf("%d", &row);
                printf("Please enter the column you'd like to play (Enter 1-3):\n");
                scanf("%d", &col);
                row--;
                col--;
                free = checkFreeSpaces(board, row, col);
            }
            // free set to 1 to avoid skipping past the next while loop
            free = 1;

            // player move is put on the board
            board[row][col] = player;
            winner = checkWinner(board);        
            
            // freeSpaces keeping the count of free spaces left on the board. When freeSpaces == 0, game is over. 
            freeSpaces--;
            if (freeSpaces == 0 || winner != ' ')
                break;

            //loop until computer finds a valid move
            while (free != 0)
            {
                computerMove(&row, &col);
                free = checkFreeSpaces(board, row, col);
            }

            board[row][col] = computer;
            freeSpaces--;

            winner = checkWinner(board);
        }

        printBoard(board);

        if (winner == player)
            printf("You won!\n");

        else if (winner == computer)
            printf("Computer wins!\n");

        else
            printf("It's a tie!\n");


        printf("Would you like to play again? (y/n)\n");
        getchar();
        scanf("%c", &playAgain);

    } while (playAgain == 'y');
    printf("Thanks for playing!\n");

    return 0;
}

void printBoard(char board[3][3])
{

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

void computerMove(int *row, int *col)
{
    int random;

    
    random = rand();
    *row = random % 3;
    random = rand();
    *col = random % 3;
}

void clearBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            board[i][j] = ' ';
        }
    }
}

int checkFreeSpaces(char board[3][3], int row, int col)
{

    if (board[row][col] == ' ')
        return 0;
    
    else 
        return 1;
}

char checkWinner(char board[3][3])
{
    int i, j;
    char winner = ' ';

    // across
    for (i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            winner = board[i][0];
            return winner;
        }
    }

    // down
    for (i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            winner = board[0][i];
            return winner;
        }
    }
    
    
    // diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        winner = board[0][0];
        return winner;
    }

    if (board[0][2] == board[1][1] && board[2][0] == board[1][1])
    {
        winner = board[0][2];
        return winner;
    }

    else
        return winner;
}