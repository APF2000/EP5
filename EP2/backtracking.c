
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
  printf("Stacking up{ (%d, %d)\n", q.line, q.col);
  printStack(P);
  P->top ++;
  P->v[P->top] = q;
  printf("\n}");
}

int isEmpty(stack* P){
  return (P->top == 0);
}

queen unstack(stack* P){
  printf("\nUstacking (%d, %d):{", P->v[P->top-1].line, P->v[P->top-1].col);
  if (isEmpty(P)) printf("\nERROR:Tried to unstack empty stack\n");
  printStack(P);
  printf("\n}");
  return P->v[--P->top];
}

queen top(stack* P){
  if (isEmpty(P)) printf("\nERROR:Tried to get top of empty stack\n");
  printStack(P);
  printf("top:,(%d, %d), ", P->v[P->top].line, P->v[P->top].col);
  printf("top-1:(%d, %d)", P->v[P->top - 1].line, P->v[P->top - 1].col);
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

int recursive(int **board, int n, int col){

  int i;

  if(col >= n)
    return 1;

  for(i = 0; i < n; i++){
    if(isSafe(board, n, i, col)){
      board[i][col] = 1;
      //printMatrix(board, n, n);

      if(recursive(board, n, col+1))
        return 1;

      board[i][col] = 0;
    }
  }
  return 0;
}

int backTrack(int **board, int n){
  stack* st = createStack(n);
  int i, count = 0, queenPut = 0;
  queen auxQueen;

  while(count != n){
    printf("\n------------------------------\n");
    printf("count=%d\nantes do for\n", count);
    for(i = 0; i < n && !isSafe(board, n, i, count); i++);
    printf("depois do for i=%d, n=%d\n", i, n);
    if(i == n){
      printf("\nEntramos no for2?");
      for(auxQueen = top(st), printf("\nAuxqueenline=%d", auxQueen.line); count > 0 && auxQueen.line == n - 1; count--){
        printf("\nVoltando rainha, count=%d", count);
        unstack(st);
        auxQueen = top(st);
        printf("\nNewTop: (%d, %d); count=%d", auxQueen.line, auxQueen.col, count);
        printf("\nAntes: board[%d][%d]", auxQueen.line, count);
        board[auxQueen.line][count] = 0;
        printf("\nDepois: board[%d][%d]", auxQueen.line, count);
        printf("\nDepois, board=%d", board[auxQueen.line][count]);
      }
      printf("\nSaimos do for2\n");
      if(count == 0 && auxQueen.line == n - 1) return 0;

      board[auxQueen.line][count - 1] = 0;
      printf("\nantes(pilha-line):(%d, %d)", st->v[st->top].line,st->v[st->top].col);
      st->v[st->top].line++;
      printf("\ndepois(pilha-line):(%d, %d)", st->v[st->top].line,st->v[st->top].col);
      board[auxQueen.line + 1][count - 1] = 1;

    }else{
      board[i][count] = 1;
      createQueen(&auxQueen, i, count);
      stackUp(st, auxQueen);
      count++;
    }
    printMatrix(board, n, n);
    printf("\n\n");
  }
  return 1;
}

int main(){

  int **board;
  int i, j;

  for(j = 10; j < 11; j++){
    /*printf("\n-- ----------------------\n");*/
    board = malloc(j * sizeof(int *));
    for(i = 0; i < j; i++){
      board[i] = malloc(j * sizeof(int));
    }
    /*printf("\n%d %s", j, recursive(board, j, 0) ? "true" : "false");*/
    backTrack(board, j);
    printMatrix(board, j, j);
  }

  return 0;
}
