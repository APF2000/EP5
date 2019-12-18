
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
  printf("\nUstacking (%d, %d):{", P->v[P->top].line, P->v[P->top].col);
  if (isEmpty(P)) printf("\nERROR:Tried to unstack empty stack\n");
  printStack(P);
  printf("\n}");
  return P->v[P->top--];
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

  printf("\nIs it safe in (%d, %d)?\n", line, col);

  for(i = 0; i < n; i++)
    if((board[i][col] == 1 && i != line) ||
        (board[line][i] == 1 && i != col)){
      printf("\nNot safe1\n");
      return 0;
    }

  for(i = 0; i < n; i++){
    auxLine = line  + i;
    auxCol  = col   + i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 && auxLine != line && auxCol != col){
        printf("\nNot safe2\n");
        return 0;
      }
    }
    auxLine = line - i;
    auxCol  = col  - i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 && auxLine != line && auxCol != col){
        printf("\nNot safe3\n");
        return 0;
      }
    }
    auxLine = line  + i;
    auxCol  = col   - i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 && auxLine != line && auxCol != col){
        printf("\nNot safe4\n");
        return 0;
      }
    }
    auxLine = line - i;
    auxCol  = col  + i;
    if(inBounds(auxLine, n) && inBounds(auxCol, n)){
      /*printf("\nauxline=%d, auxcol=%d", auxLine, auxCol);*/
      if(board[auxLine][auxCol] == 1 && auxLine != line && auxCol != col){
        printf("\nNot safe5\n");
        return 0;
      }
    }
  }
  printf("\nYes\n");
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
  int i, j, count = 0;
  queen auxQueen, lastQueen;
  int /*stop,*/ queenPut = 0;

  while(count != n){
    /*scanf("%d", &stop);*/
    printStack(st);
    printf("\n------------------------------\n");
    printf("count=%d\nantes do for\n", count);
    for(i = 0; i < n && !isSafe(board, n, i, count); i++);
    printf("depois do for i=%d, n=%d\n", i, n);
    if(i == n){
      queenPut = 0;
      printf("\ni==n\n");
      for(auxQueen = top(st), printf("\nAuxqueen=(%d, %d)", auxQueen.line, auxQueen.col); count > 0 && auxQueen.line == n - 1; count--){
        printf("\nEntramos no for2?");
        printf("\nVoltando rainha, count=%d", count);
        printf("\nAntes: board[%d][%d]=%d", auxQueen.line, count-1, board[auxQueen.line][count-1]);
        board[auxQueen.line][auxQueen.col] = 0;
        printf("\nDepois: board[%d][%d]=%d", auxQueen.line, count-1, board[auxQueen.line][count-1]);
        printMatrix(board, n, n);
        lastQueen = unstack(st);
        printf("\n\n\ncount=%d\n\n\n", count);
        auxQueen = top(st);
        printf("\nNewTop: (%d, %d); count=%d", auxQueen.line, auxQueen.col, count);
      }
      printf("\n\n\ncount=%d\n\n\n", count);
      printf("\nSaimos do for2, count=%d\n", count);
      if(count == 0 && lastQueen.line == (n - 1)){
        printf("\nImpossivel em R, count=%d, lastqueenline=%d", count, lastQueen.line);
        printMatrix(board, n, n);
        return 0;
      }

      printMatrix(board, n, n);
      for(i = auxQueen.col; i > 0 && !isSafe(board, n, auxQueen.line + 1, i); i--){
        printMatrix(board, n, n);
        board[auxQueen.line][i] = 0;
        printf("\nMagic!! Sumiu!");
        printMatrix(board, n, n);
        printf("\nNovo for1, i=%d", i);
        for(j = auxQueen.line + 1; j < n && !queenPut && !isSafe(board, n, j, i); j++){
          printf("\nNovo for2, j=%d", j);
          printf("\nj<n:%d, !isSafe(j=%d, i=%d)", j<n, j, i);

          board[j][i] = 0;
          /*printf("\nantes(pilha):(%d, %d)", st->v[st->top].line,st->v[st->top].col);*/
          /*printf("\ndepois(pilha):(%d, %d)", st->v[st->top].line,st->v[st->top].col);*/
          printf("\nAntes do IF");
          if( j < (n - 1) ){
            printf("\nj < n-1");
            //board[j][i] = 1;
            st->v[st->top].line++;
            printMatrix(board, n, n);

          }else{
            printf("\nj >= n-1");
            unstack(st);
            count--;
            printf("\n\n\ncount=%d\n\n\n", count);
            auxQueen = top(st);
          }
          printf("\nDepois do IF");
        }
        printf("\nFim do for2, queenPut=%d", queenPut);
        if(j == n) j--;
        if(isSafe(board, n, j, i) && !queenPut){
          board[j][i] = 1;
          //count++;
          printf("\n\n\ncount=%d\n\n\n", count);
          st->v[st->top].line++;
          printMatrix(board, n, n);
          queenPut = 1;
          break;
        }
        while(auxQueen.line == (n - 1) && !queenPut){
          printf("\nTirando as pontas de baixo");
          board[auxQueen.line][auxQueen.col] = 0;
          unstack(st);
          count--;
          printf("\n\n\ncount=%d\n\n\n", count);
          printMatrix(board, n, n);
          auxQueen = top(st);
          if(count == -1) return 0;
          i--;
        }
      }
      printf("\nFim do for1, queenPut=%d", queenPut);
      if(i < 0) i++;
      if(!queenPut){
        printf("\nqueenPut=%d, auxqueen=(%d, %d)", queenPut, auxQueen.line, auxQueen.col);
        board[auxQueen.line][auxQueen.col] = 0;
        if(isSafe(board, n, auxQueen.line, i)){
          //board[auxQueen.line][i] = 0;
          st->v[st->top].line++;
          board[auxQueen.line + 1][i] = 1;
          //count++;
          printf("\n\n\ncount=%d\n\n\n", count);
          printMatrix(board, n, n);
          queenPut = 1;
        }
      }
    }else{
      board[i][count] = 1;
      createQueen(&auxQueen, i, count);
      stackUp(st, auxQueen);
      count++;
      printf("\n\n\ncount=%d\n\n\n", count);
    }
    printMatrix(board, n, n);
    printf("\n\n");
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
  int i, j, k, get;

  for(j = 4; j < 14; j++){
    scanf("%d", &get);
    /*printf("\n-- ----------------------\n");*/
    board1 = malloc(j * sizeof(int *));
    board2 = malloc(j * sizeof(int *));
    for(i = 0; i < j; i++){
      board1[i] = malloc(j * sizeof(int));
      board2[i] = malloc(j * sizeof(int));
      for(k = 0; k < j; k++){
        board1[i][k] = 0;
        board2[i][k] = 0;
      }
    }
    printf("\n%d %s", j, recursive(board1, j, 0) ? "true" : "false");
    backTrack(board2, j);
    printMatrix(board1, j, j);
    printMatrix(board2, j, j);

    printf("\nMatrixs are equal? (%s)", matrixEquality(board1, board2, j)?"true":"false");
  }

  return 0;
}
