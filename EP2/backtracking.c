
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **matrix, int lines, int cols){
  int i, j;
  printf("\n\nPrintingmatrix\n\n");
  for(i = 0; i < lines; i++){
    printf("\n");
    for(j = 0; j < cols; j++){
      printf("%d ", matrix[i][j]);
    }
  }
  printf("\n\n");
}

int isSafe(int **board, int n, int line, int col){
  int i, auxLine, auxCol;

  printf("\nIs it safe?\n");

  for(i = 0; i < n; i++)
    if(board[i][col] == 1 || board[line][i] == 1){
      printf("\nNot safe1\n");
      return 0;
    }

  for(i = 0; i < n; i++){
    auxLine = (line + n + i) % n;
    auxCol  = (col  + n + i) % n;
    printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);
    if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
      printf("\nNot safe2\n");
      return 0;
    }
    auxLine = (line + n - i) % n;
    auxCol  = (col  + n - i) % n;
    printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);
    if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
      printf("\nNot safe3\n");
      return 0;
    }
  }
  return 1;
}

int solveNQUtil(int **board, int n, int col){

  int i;

  if(col >= n)
    return 1;

  for(i = 0; i < n; i++){
    if(isSafe(board, n, i, col)){
      board[i][col] = 1;
      printMatrix(board, n, n);

      if(solveNQUtil(board, n, col+1))
        return 1;

      board[i][col] = 0;
    }
  }
  return 0;
}

int main(){

  int **board;
  int i, j;

  for(j = 3; j < 4; j++){
    printf("\n------------------------\n");
    board = malloc(j * sizeof(int *));
    for(i = 0; i < j; i++){
      board[i] = malloc(j * sizeof(int));
    }

    printf("\n%d %s\n", j, solveNQUtil(board, j, 0) ? "true" : "false");
  }

  return 0;
}
