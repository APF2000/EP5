
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

void printStack(stack* st){
  int i;
  printf("\nStack:");
  for(i = 0; i < st->top; i++){
    printf("\n(%d,%d)", st->v[st->top - i].line, st->v[st->top - i].col);
  }
}

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
  P->top ++;
  P->v[P->top] = q;
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
  return (P->v[P->top]);
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

  for(i = 0; i < n; i++)
    if(board[i][col] == 1 || board[line][i] == 1){
      return 0;
    }

  for(i = 0; i < n; i++){
    auxLine = line  + i;
    auxCol  = col   + i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      if(board[auxLine][auxCol] == 1 || board[auxLine][auxCol] == 1){
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

int recursive(int **board, int n, int col){

  int i;

  if(col >= n)
    return 1;

  for(i = 0; i < n; i++){
    if(isSafe(board, n, i, col)){
      board[i][col] = 1;

      if(recursive(board, n, col+1))
        return 1;

      board[i][col] = 0;
    }
  }
  return 0;
}

int backTrack(int **board, int n){
  stack* st = createStack(n);
  int i, j, count = 0;
  queen auxQueen;

  while(count != n){
    for(i = 0; i < n && !isSafe(board, n, i, count); i++);

    if(i == n){

      for(auxQueen = top(st); count > 0 && auxQueen.line == n - 1; count--){
        board[auxQueen.line][count - 1] = 0;
        unstack(st);
        auxQueen = top(st);
      }
      if(count == 0 && auxQueen.line == n - 1) return 0;

      for(i = auxQueen.col; i > 0 && !isSafe(board, n, auxQueen.line, i); i--){
        for(j = auxQueen.line; j < n && !isSafe(board, n, j, i); j++){
          board[j][i] = 0;
          if( j < (n - 1) ){
            board[j + 1][i] = 1;
            st->v[st->top].line++;
          }else
            auxQueen = unstack(st);
        }
        if(isSafe(board, n, j - 1, i))
          break;
      }
      if(isSafe(board, n, auxQueen.line, i - 1)){
        board[auxQueen.line][i] = 0;
        st->v[st->top].line++;
        board[auxQueen.line + 1][i] = 1;
      }
    }else{
      board[i][count] = 1;
      createQueen(&auxQueen, i, count);
      stackUp(st, auxQueen);
      count++;
    }
  }
  return 1;
}

int matrixEquality(int **M1, int **M2, int n){
  int i, j;
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      if(M1[i][j] != M2[i][j])
        return 0;
  return 1;
}

int main(){

  int **board1, **board2;
  int i, j, k;

  for(j = 7; j < 11; j++){

    board1 = malloc(j * sizeof(int *));
    board2 = malloc(j * sizeof(int *));
    for(i = 0; i < j; i++){
      board1[i] = malloc(j * sizeof(int));
      board2[i] = malloc(j * sizeof(int));
      printf("\nHallo");
      for(k = 0; k < j; k++){
        printf("\n\ni=%d, j=%d, k=%d", i, j, k);
        board1[i][k] = 0;
        printf("\nok1");
        board2[i][k] = 0;
        printf("\nok2");
      }
    }
    printf("\n%d %s", j, recursive(board1, j, 0) ? "true" : "false");
    backTrack(board2, j);
    /*printMatrix(board1, j, j);
    printMatrix(board2, j, j);*/

    printf("\nMatrixs are equal? (%s)", matrixEquality(board1, board2, j)?"true":"false");

    free(board1);
    free(board2);
  }

  return 0;
}
