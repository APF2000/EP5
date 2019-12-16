
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int line;
  int col;
} queen;

typedef struct {
  queen* v;
  int top;
  int max;
} stack;

stack* createStack(int n){
  stack* aux = malloc(n * sizeof(stack));

  aux->v = malloc(n * sizeof(queen));
  aux->top = 0;
  aux->max = n;
  return aux;
}

void destroyStack(stack* P){
  free(P->v);
  free(P);
}

void resize(stack* P){
  int i;
  queen * aux = P->v;
  P->v = malloc (2*P->max*sizeof(queen));
  for (i = 0; i < P->top; i++)
    P->v[i] = aux[i];
  P->max = 2 * P->max;
  free(aux);
}

void stackUp(stack* P, queen q){
  if (P->top == P->max) resize(P);
  printf("Stacking up (%d, %d)\n", q.line, q.col);
  P->v[P->top] = q;
  P->top ++;
}

int isEmpty(stack* P){
  return (P->top == 0);
}

void unstack(stack* P){
  if (isEmpty(P)) printf("ERROR");
  P->top --;
}

queen top(stack* P){
  if (isEmpty(P)) printf("ERRO");
  return (P->v[P->top - 1]);
}

void printStack(stack* st){
  int i;
  printf("\n\nStack:");
  for(i = 0; i < st->top; i++){
    printf("\n(%d,%d)", st->v[st->top - i - 1].line, st->v[st->top - i - 1].col);
  }
}

//////////////////////////////////////////////

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

int inBounds(int verified, int n){
  if(verified >= n || verified < 0)
    return 0;
  return 1;
}

int isSafe(int **board, int n, int line, int col){
  int i, auxLine, auxCol;

  /*printf("\nIs it safe?\n");*/

  for(i = 0; i < n; i++)
    if(board[i][col] == 1 || board[line][i] == 1){
      /*printf("\nNot safe1\n");*/
      return 0;
    }

  for(i = 0; i < n; i++){
    auxLine = line  + i;
    auxCol  = col   + i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
        /*printf("\nNot safe2\n");*/
        return 0;
      }
    }
    auxLine = line - i;
    auxCol  = col  - i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
        /*printf("\nNot safe3\n");*/
        return 0;
      }
    }
    auxLine = line  + i;
    auxCol  = col   - i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
        /*printf("\nNot safe4\n");*/
        return 0;
      }
    }
    auxLine = line - i;
    auxCol  = col  + i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
        /*printf("\nNot safe5\n");*/
        return 0;
      }
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
      //printMatrix(board, n, n);

      if(solveNQUtil(board, n, col+1))
        return 1;

      board[i][col] = 0;
    }
  }
  return 0;
}

int backTrack(int **board, int n){
  stack* st = createStack(n);
  int i;
  queen teste1, teste2, teste3, teste4;
  teste1.line = 1;
  teste1.col = 2;
  teste2.line = 3;
  teste2.col = 4;
  teste3.line = 5;
  teste3.col = 6;
  teste4.line = 7;
  teste4.col = 8;

  stackUp(st, teste1);
  printStack(st);
  stackUp(st, teste2);
  printStack(st);
  stackUp(st, teste3);
  printStack(st);
  for(i = 0; i < 1; i++){
    stackUp(st, teste4);
  }
  printStack(st);

  unstack(st);
  printStack(st);
  unstack(st);
  unstack(st);
  printf("\nEmpty:%s", isEmpty(st)?"true":"false");
  unstack(st);
  printf("\nEmpty:%s", isEmpty(st)?"true":"false");
  return 1;
}

int main(){

  int **board;
  int i, j;

  for(j = 4; j < 5; j++){
    /*printf("\n------------------------\n");*/
    board = malloc(j * sizeof(int *));
    for(i = 0; i < j; i++){
      board[i] = malloc(j * sizeof(int));
    }
    /*printf("\n%d %s", j, solveNQUtil(board, j, 0) ? "true" : "false");*/
    backTrack(board, j);
    //printMatrix(board, j, j);
  }

  return 0;
}
