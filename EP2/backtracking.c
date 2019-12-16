
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

void createQueen(queen* q, int line, int col){
  q->line = line;
  q->col = col;
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

queen unstack(stack* P){
  if (isEmpty(P)) printf("\nERROR:Tried to unstack empty stack\n");
  return P->v[P->top--];
}

queen top(stack* P){
  if (isEmpty(P)) printf("\nERROR:Tried to get top of empty stack\n");
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
  int i, count = 0;
  queen auxQueen;

  while(count != n){
    printf("count=%d\nantes do for\n", count);
    for(i = 0; i < n && !isSafe(board, n, i, count); i++);
    printf("depois do for i=%d\n", i);
    if(i == n){
      for(auxQueen = unstack(st); auxQueen.line == n - 1; count--)
        board[auxQueen.line][count] = 0;
      if(count == 0 && auxQueen.line == n - 1) return 0;
      board[auxQueen.line][count] = 0;
      auxQueen.line++;
    }else{
      board[i][count] = 1;
      createQueen(&auxQueen, i, count);
      stackUp(st, auxQueen);
      count++;
    }
    printMatrix(board, n, n);
    printf("\n\n\n\n");
  }
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
    printMatrix(board, j, j);
  }

  return 0;
}
