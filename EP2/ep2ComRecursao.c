
// EP2 com recursão (10/12/2019)

#include <stdio.h>
#include <stdlib.h>
#define ASTERISK '*'
#define BLANCK ' '

int max(int a, int b){
  return (a > b) ? a : b;
}

int size(char *string){
  int count = 0;
  while(string[count] != '\0')
    count++;
  return count;
}

char asterOrBlanck(int which){
  if(which == -1)
    return ASTERISK;
  return BLANCK;
}

void recursion(char **crossWords, int lines, int cols,
      char **words, int numWords, int wordsInserted){

    if(wordsInserted != numWords){
      if(1 < 2){
        wordsInserted++;
      }
      recursion(crossWords, lines, cols, words, numWords, wordsInserted);
    }
    return;
}

int main(){

  int numLines, numCols;
  char **crossWords;
  char **words;
  int i, j, aux;

  while(scanf("%d %d", &numLines, &numCols)
        && numLines != 0 && numCols != 0){

    crossWords = malloc(numLines * sizeof(char *));
    for(i = 0; i < numLines; i++){
      crossWords[i] = malloc(numCols * sizeof(int));
    }

    for(i = 0; i < numLines; i++){
      for(j = 0; j < numCols; j++){
        scanf("%d", &aux);
        crossWords[i][j] = asterOrBlanck(aux);
      }
    }

    scanf("%d", &aux);
    words = malloc(aux * sizeof(char *));

    for(i = 0; i < aux; i++){
      words[i] = malloc(max(numLines, numCols) * sizeof(char));
      scanf("%s", words[i]);
      printf("\n%s, size=%d", words[i], size(words[i]));
    }

    recursion(crossWords, numLines, numCols, words, aux, 0);
  }

  return 0;
}


/*
  Entrada:
  5 4
  -1  0  0  0
   0  0  0  0
   0  0 -1  0
   0  0  0  0
   0 -1  0  0
  10
  ad antas carn casa do lado
  lua os soda ur
  3 3
  -1  0  0
   0  0  0
   0 -1  0
  5
  ab au bug la lua
  0 0
*/
