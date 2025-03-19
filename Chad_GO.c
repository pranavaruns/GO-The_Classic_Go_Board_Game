#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 9

char board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void printBoard() {
    printf("   A B C D E F G H I\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool checkAdjacent(int row, int col, char player, int s_row, int s_col, int p_row, int p_col){
    int flag=0;
    if (row+1<=8){
        if (((s_row!=row+1) || (s_col!=col)) && (board[row+1][col]=='.')){
            flag=1;
            return true;
        }
        if (((s_row!=row+1) || (s_col!=col)) && ((p_row!=row+1) || (p_col!=col)) && board[row+1][col]==player){    //one-piece down(same column)
            if(checkAdjacent(row+1, col, player, s_row, s_col, row, col)) return true;
        }
    }
    if (row-1>=0){
        if (((s_row!=row-1) || (s_col!=col)) && (board[row-1][col]=='.')){
            flag=1;
            return true;
        }
        if (((s_row!=row-1) || (s_col!=col)) && ((p_row!=row-1) || (p_col!=col)) && board[row-1][col]==player){    //one-piece up(same column)
            if(checkAdjacent(row-1, col, player, s_row, s_col, row, col)) return true;
        }
    }
    if (col+1<=8){
        if (((s_row!=row) || (s_col!=col+1)) && (board[row][col+1]=='.')){
            flag=1;
            return true;
        }
        if (((s_row!=row) || (s_col!=col+1)) && ((p_row!=row) || (p_col!=col+1)) && board[row][col+1]==player){    //one-piece to the right(same row)
            if(checkAdjacent(row, col+1, player, s_row, s_col, row, col)) return true;
        }
    }
    if (col-1>=0){
        if (((s_row!=row) || (s_col!=col-1)) && (board[row][col-1]=='.')){
            flag=1;
            return true;
        }
        if (((s_row!=row) || (s_col!=col-1)) && ((p_row!=row) || (p_col!=col-1)) && board[row][col-1]==player){    //one-piece to the left(same row)
            if(checkAdjacent(row, col-1, player, s_row, s_col, row, col)) return true;
        }
    }
    if (flag==0) return false;
}

bool isValidMove(int row, int col, char player) {
    int c=0;
    char op='X';
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == '.'){
        if (player=='X'){
            op='O';
        }
        if (row+1<=8){
            if (board[row+1][col]!=op){    //one-piece down(same column)
                c+=1;
            }
        }
        if (row-1>=0){
            if (board[row-1][col]!=op){    //one-piece up(same column)
                c+=1;
            }
        }
        if (col+1<=8){
            if (board[row][col+1]!=op){    //one-piece to the right(same row)
                c+=1;
            }
        }
        if (col-1>=0){
            if (board[row][col-1]!=op){    //one-piece to the left(same row)
                c+=1;
            }
        }
        if (c!=0){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool captureReplace(int row, int col, char op, int p_row, int p_col){
    board[row][col]='.';
    if (row+1<=8){
        if (((p_row!=row+1) || (p_col!=col)) && board[row+1][col]==op){    //one-piece down(same column)
            board[row+1][col]='.';
            captureReplace(row+1, col, op, row, col);
        }
    }
    if (row-1>=0){
        if (((p_row!=row-1) || (p_col!=col)) && board[row-1][col]==op){    //one-piece up(same column)
            board[row-1][col]='.';
            captureReplace(row-1, col, op, row, col);
        }
    }
    if (col+1<=8){
        if (((p_row!=row) || (p_col!=col+1)) && board[row][col+1]==op){    //one-piece to the right(same row)
            board[row][col+1]='.';
            captureReplace(row, col+1, op, row, col);
        }
    }
    if (col-1>=0){
        if (((p_row!=row) || (p_col!=col-1)) && board[row][col-1]==op){    //one-piece to the left(same row)
            board[row][col-1]=='.';
            captureReplace(row, col-1, op, row, col);
        }
    }
    return false;
}

int capture(int row, int col, char op, int p_row, int p_col){
    if (checkAdjacent(row, col, op, row, col, row, col)==false){
        board[row][col]='.';
        if (row+1<=8){
            if (((p_row!=row+1) || (p_col!=col)) && board[row+1][col]==op){    //one-piece down(same column)
                board[row+1][col]='.';
                captureReplace(row+1, col, op, row, col);
            }
        }
        if (row-1>=0){
            if (((p_row!=row-1) || (p_col!=col)) && board[row-1][col]==op){    //one-piece up(same column)
                board[row-1][col]='.';
                captureReplace(row-1, col, op, row, col);
            }
        }
        if (col+1<=8){
            if (((p_row!=row) || (p_col!=col+1)) && board[row][col+1]==op){    //one-piece to the right(same row)
                board[row][col+1]='.';
                captureReplace(row, col+1, op, row, col);
            }
        }
        if (col-1>=0){
            if (((p_row!=row) || (p_col!=col-1)) && board[row][col-1]==op){    //one-piece to the left(same row)
                board[row][col-1]=='.';
                captureReplace(row, col-1, op, row, col);
            }
        }
    }
}

void makeMove(int row, int col, char player) {
    board[row][col] = player;
}

int main() {
    initializeBoard();
    char currentPlayer = 'X';
    int row, col;

    printf("Welcome to the terminal Go game!\n");

    while (true) {
        printBoard();
        printf("Player %c's turn. Enter your move (e.g., A3): ", currentPlayer);
       
        // Read player input
        char input[10];
        scanf("%s", input);

        // Convert input to row and column
        if (sscanf(input, " %c%d", &input[0], &row) != 2) {
            printf("Invalid input. Please enter a move like A3.\n");
            continue;
        }
        col = input[0] - 'A';

        // Adjust row and column to 0-based indexing
        row--;

        // Check if the move is valid
        if (!isValidMove(row, col, currentPlayer)) {
            printf("Invalid move. Try again.\n");
            continue;
        }
        else{
            if (!checkAdjacent(row, col, currentPlayer, row, col, row, col)) {
                printf("Invalid move. THITry again.\n");
                continue;
            }
            else{
                // Make the move
                makeMove(row, col, currentPlayer);
                char op='X';
                if (currentPlayer=='X'){
                    op='O';
                }
                if (row+1<=8){
                    if (board[row+1][col]==op){    //one-piece down(same column)
                        capture(row+1, col, op, row+1, col);
                    }
                }
                if (row-1>=0){
                    if (board[row-1][col]==op){    //one-piece up(same column)
                        capture(row-1, col, op, row-1, col);
                    }
                }
                if (col+1<=8){
                    if (board[row][col+1]==op){    //one-piece to the right(same row)
                        capture(row, col+1, op, row, col+1);
                    }
                }
                if (col-1>=0){
                    if (board[row][col-1]==op){    //one-piece to the left(same row)
                        capture(row, col-1, op, row, col-1);
                    }
                }
            }
        }
       
        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
   
    return 0;
}