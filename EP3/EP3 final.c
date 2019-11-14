#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int valor;
  int pos;
  int card; /*  Posicao certa de uma panqueca em um vetor organizado  */
}panqueca;


void troca(panqueca v[], int a, int b){
    panqueca aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void flip(panqueca v[], int tam, int pan){
    int i, aux;
    for(i = 0; i < (tam - pan)/2; i++){
        troca(v, pan + i, tam - 1 - i);
        aux = v[pan + i].pos;
        v[pan + i].pos = v[tam - 1 -i].pos;
        v[tam - 1 - i].pos = aux;
    }
}



void bubblesort(panqueca pan[], int tam){
    int i, j;
    panqueca aux;
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam - 1 - i; j++){
            if(pan[j].valor < pan[j + 1].valor){
                aux = pan[j];
                pan[j] = pan[j + 1];
                pan[j + 1] = aux;
            }
        }
    }
}


int ponta_bloco(panqueca pan[], int lugar){
    if(lugar == 0){
        if(pan[0].card + 1 == pan[1].card || pan[0].card - 1 == pan[1].card)
            return 0;
        else
            return 1;
    }
    if(pan[lugar].card + 1 == pan[lugar + 1].card || pan[lugar].card - 1 == pan[lugar + 1].card)
        return 0;
    else
        return 1;
}

int organizado(panqueca pan[], int tam){
    int i;
    for(i = 0; i < tam; i++){
        if(pan[i].valor < pan[i + 1].valor){
            return 0;
        }
    }
    return 1;
}

void print_flip(panqueca pan[], panqueca aux[], int tam, int onde, int add){
    int i;
    printf("%d ", aux[onde].pos + add);
    flip(pan, tam, aux[onde].pos + add);
    for(i = 0; i < tam; i++){
        aux[tam - 1 - pan[i].card].pos = pan[i].pos;
    }
}


void onde_flipa(panqueca pan[], panqueca aux[], int tam){
    int i=0, j;
    printf("\n");
    while(organizado(pan, tam) == 0 && i < 10){
        i++;
        if(pan[tam - 1].card == tam - 1){
            print_flip(pan, aux, tam, 0, 1 - tam);
        }
        else{
            if(ponta_bloco(pan, aux[tam - 2 - pan[tam - 1].card].pos) == 1){
                print_flip(pan, aux, tam, aux[tam - 2 - pan[tam - 1].card].card, 2);

            }
            else{
                for(j = 0; pan[tam - 1 - j].card - 1 == pan[tam - 2 - j].card; j++);

                if(j!=0){ /* Se o bloco for decrescente da direita pra esquerda */
                    print_flip(pan, aux, tam, pan[tam - 1].card - j, 1);
                    print_flip(pan, aux, tam, aux[pan[tam - 1].card + j].pos + 1, - 1);   /* Flipa na ponta esquerda */
                }
                else{ /* Se o bloco for crescente da direita pra esquerda */
                    /* Verifica se o antecessor e ponta */
                    if(pan[tam - 1].card != 0 && ponta_bloco(pan, aux[tam - pan[tam - 1].card].pos) == 1){

                        print_flip(pan, aux, tam, tam - pan[tam - 1].card, 1);

                    }
                    else{ /* Percorre o bloco até chegar ao fim dele, flipa o bloco, flipa embaixo do antecessor do topo, flipa em cima do ultimo ponto */

                        /* Percorre o bloco */
                        for(j = 0; pan[tam - 1 - j].card + 1 == pan[tam - 2 - j].card; j++);

                        if(pan[tam - 1].card == 0){
                            print_flip(pan, aux, tam, aux[tam - 2 - pan[tam - 1 - j].card].pos, - 1);   /* Flipa na ponta esquerda */
                            print_flip(pan, aux, tam, aux[tam - pan[tam - 1].card].pos, 0);   /* Flipa no de cima pra encostar as pontas */

                        }
                        else if(j != 0){
                            /*  Prepara pra juntar com a ponta */
                            print_flip(pan, aux, tam, aux[pan[tam - 1].card + j].card, 0);
                            print_flip(pan, aux, tam, tam - 1 - aux[tam + j - pan[tam - 1].card].card, 0);

                        }
                    }
                }
            }
        }
    }
}


int main(){
    int i, tam;
    panqueca *torre, *aux;
    scanf("%d", &tam);

    torre = malloc(tam * sizeof(panqueca));
    aux = malloc(tam * sizeof(panqueca));

    for(i = 0; i < tam; i++){
        scanf("%d", &torre[i].valor);
        aux[i].valor = torre[i].valor;
        aux[i].pos = torre[i].pos = i;
    }

    bubblesort(aux, tam);

    for(i = 0; i < tam; i++){
        aux[i].card = tam - 1 - i;
        torre[aux[i].pos].card = tam - 1 - i;
    }

    printf("\n");
    onde_flipa(torre, aux, tam);

    return 0;
}




