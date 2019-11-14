/**********************************************/
/*   Arthur Pires da Fonseca                  */
/*   No USP : 10773096                        */
/*   MAC0122                                  */
/*   Professor: Carlos Eduardo Ferreira       */
/**********************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

/* Guarda em "convergencia" o número da sequência de Collatz
   e em "passos" a quantidade de passos que faltam para esse número chegar ao 1. */
typedef struct{
    int convergencia;
    int passos;
}entroncamento;



/* Recebe um número inteiro e devolve quantos passos
 foram necessários para chegar ao valor 1 com a conjectura de Collatz.
 Recebe um vetor aux onde guarda todos os números pelos quais a função
 passa e suas quantidades correspondentes de passos caso *vai seja 1.
 Caso contrário, compara os passos e entroncamentos do número anterior
 e se houver convergência, retorna a quantidade de passos do número atual
 (senão *vai é atualizado para 1. */
int Collatz (long unsigned int num, entroncamento aux[MAX], int *vai)
{
   int passos=0, i=0;
   long unsigned int auxiliar;
   entroncamento temporario[MAX];
   if(num == 1){
      printf("ERRO");
      return -1;
   }
   while(num != 1){
       if(num % 2 == 1){
          num = (num * 3 + 1);
          passos ++;
       }
       else{
          num /= 2;
          passos++;
       }


       if(num == aux[i].convergencia){
          return passos + aux[i].passos - 1;
       }

       if((*vai) == 1){
         aux[i].convergencia = num;
         aux[i].passos = passos;
       }
       else{
            temporario[i].convergencia = num;
            temporario[i].passos = passos;
       }
       i++;
   }
   if((*vai) == 1){
     (*vai) = 0;
     for(i=0; i<(passos/2); i++){
        auxiliar = aux[i].convergencia;
        aux[i].convergencia = aux[passos-i-1].convergencia;
        aux[passos-i-1].convergencia = auxiliar;
     }
   }
   else if(temporario[passos-1].convergencia != aux[passos-1].convergencia){
        for(i=0; i<passos; i++){
            aux[i].convergencia = temporario[i].convergencia;
            aux[i].passos = temporario[i].passos;
        }
        (*vai) = 1;
   }
   return passos;
}


int main()
{
    long unsigned int i, f;
    int passos = 0, j;
    int vai = 1;   /* Determina se é necessário recontabilizar os passos do número seguinte no vetor aux */
    entroncamento aux[MAX];
    printf("Digite os extremos i (inferior) e s (superior)\n");
    scanf("%lu %lu", &i, &f);
    if(i == 1){
            printf("O numero %9.lu exigiu   0 passos\n", i);
            i++;
    }
    while(i <= f){

            if(vai == 1){
                for(j=0; aux[j].passos != 0; j++){
                  aux[j].passos = 0;
                  aux[j].convergencia = 0;
                }
            }
            passos = Collatz(i, aux, &vai);
            printf("O numero %9.lu exigiu %3.d passos\n", i, passos);
            i++;
    }

    return 0;
}
