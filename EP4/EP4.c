#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALFABETO 26
#define TAM_INICIAL 100

typedef struct{
    char *word;
    int qtde;
}word;

typedef struct celu{
    word pal;
    struct celu *prox, *ant;
}celula;

typedef celula* apontador;

typedef struct cel{
    word pal;
    struct cel *esq, *dir, *pai;
}no;

typedef no* galho;

int caso(char *str){
    if(strcmp(str, "VD") == 0){
        /* Vetor desordenado*/
        return 11;
    }
    else if(strcmp(str, "VO") == 0){
        /* Vetor ordenado */
        return 12;
    }
    else if(strcmp(str, "LD") == 0){
        /* Lista ligada desordenada */
        return 21;
    }
    else if(strcmp(str, "LO") == 0){
        /* Lista ligada ordenada */
        return 22;
    }
    else if(strcmp(str, "AB") == 0){
        /* Árvore de busca binária */
        return 3;
    }
    return 0;
}

/* FUNCOES VETOR DESORDENADO */
int strpertence(char *str, char ch){
    int i;
    for(i = 0; i < strlen(str); i++){
        if(str[i] == ch)
            return 1;
    }
    return 0;
}

int nao_letra(char ch){
    if(strpertence("'\"!@#$£%¢¨¢¨¬&*()-_+=§\t/?°´`[{ª~^]}º\\|,<.>;:", ch))
        return 1;
    else if(ch - '0' >= 0 && ch - '0' <= 9)
        return 1;
    return 0;
}

void desloca_string(char *str, int ini, int desloc){
    int i;
    for(i = 0; str[i] != '\0'; i++){
            str[ini - desloc + i] = str[ini + i];
    }
    str[ini - desloc + i] = str[ini + i];
}

void minuscular(char v[], int tam){
    int i;
    for(i = 0; i < tam; i++){
        if(v[i] - 'A' < ALFABETO && v[i] - 'A' >= 0)
            v[i] = 'a' + (v[i] - 'A');
    }
}

int pega_palavra(FILE *arq, char *str, word palavra){
    int i, j;
    if(fscanf(arq, "%s", str) == 1){
        minuscular(str, strlen(str));

        for(i = 0; i < strlen(str); i++){
            j = 0;
            while(nao_letra(str[i]) == 1){
                j++;
                i++;
            }
            if(j > 0){
                desloca_string(str, i, j);
                i -= j;
            }
        }
        strcpy(palavra.word, str);
        return 1;
    }
    else
        return 0;
}

word *VD_insere(word *lista, word palavra, int *pos, int *max){
    word *aux;
    int i;
    palavra.qtde = 0;
    aux = lista;
    if((*pos) >= (*max)){
        aux = malloc(((*max) + TAM_INICIAL) * sizeof(word));
        for(i = 0; i < (*max) + TAM_INICIAL; i++){
            aux[i].word = malloc(((*max) + TAM_INICIAL) * sizeof(char*));
            if(i < (*max)){
                aux[i] = lista[i];
            }
        }
        (*max) += TAM_INICIAL;
    }

    for(i = 0; i < (*pos); i++){
        if(strcmp(palavra.word, aux[i].word) == 0){
            lista[i].qtde ++;
            (*pos)--;
            return aux;
        }
    }
    lista[(*pos)].word = palavra.word;
    lista[(*pos)].qtde = 1;
    if((*pos) == 0)
        return aux;
    return aux;
}

void troca(word *lista, int a, int b){
    word aux;
    aux = lista[a];
    lista[a] = lista[b];
    lista[b] = aux;
}

int separa(word *lista, char *ordem, int ini, int fim){
    int p, q;
    word x;
    p = ini;
    q = fim - 1;
    x = lista[ini];
    if(strcmp(ordem, "A") == 0){
        while(p < q){
            while(strcmp(lista[q].word, x.word) > 0){
                q--;
            }
            if(p < q)
                troca(lista, p, q);
            while(strcmp(lista[p].word, x.word) <= 0 && p < q){
                p++;
            }
            if(p < q)
                troca(lista, p, q);
        }
        return p;
    }
    else{
        while(p < q){
            while(lista[q].qtde < x.qtde){
                q--;
            }
            if(p < q)
                troca(lista, p, q);
            while(lista[p].qtde >= x.qtde && p < q){

                p++;
            }
            if(p < q)
                troca(lista, p, q);
        }
        return p;
    }
}

void VDquicksort(word *lista, int tam, char *ordem, int ini, int fim){
    int pivo = (ini + fim)/2;
    if(fim - ini > 1){
        pivo = separa(lista, ordem, ini, fim);
        VDquicksort(lista, tam, ordem, ini, pivo);
        VDquicksort(lista, tam, ordem, pivo + 1, fim);
    }
}

void VDimprime_lista(word *lista, int tam, char *ordem){
    int i;
    VDquicksort(lista, tam, ordem, 0, tam);
    for(i = 0; i < tam; i++){
        printf("\n%s %d", lista[i].word, lista[i].qtde);
    }
}

/* FUNCOES VETOR ORDENADO */

word *VO_insere(word *lista, word palavra, int *pos, int *max, char *ordem){
    word *aux;
    int i;
    palavra.qtde = 0;
    aux = lista;
    if((*pos) >= (*max)){
        printf("\neaemennaoacontece");
        aux = malloc(((*max) + TAM_INICIAL) * sizeof(word));
        for(i = 0; i < (*max) + TAM_INICIAL; i++){
            aux[i].word = malloc(((*max) + TAM_INICIAL) * sizeof(char*));
            if(i < (*max)){
                aux[i] = lista[i];
            }
        }
        (*max) += TAM_INICIAL;
        printf("\nauxaaaaaaaa = %s,", aux[100].word);
    }

        printf("\nA PALAVRA Q VC QUER %s", palavra.word);
        if((*pos) == 0){
            printf("\nTO AQUI");
            aux[0].word = palavra.word;
            aux[0].qtde = 1;
            return aux;
        }
        for(i = 0; i < (*pos) && strcmp(aux[i].word, palavra.word)<=0; i++){
            printf("\nlistawor[%d] = %s (%d), palavra = %s (str = %d)",
                   i, lista[i].word, lista[i].qtde, palavra.word, strcmp(aux[i].word, palavra.word));
            if(strcmp(aux[i].word, palavra.word) == 0){
                aux[i].qtde ++;
                (*pos)--;
                return aux;
            }
        }
        palavra.qtde = 1;
        memmove(&aux[i + 1], &aux[i], ((*pos) - i - 1)*sizeof(word));
        VDimprime_lista(aux, (*pos), ordem);
        return aux;


    printf("\npos = %d", (*pos));
    lista[(*pos)].word = palavra.word;
    lista[(*pos)].qtde = 1;
    if((*pos) == 0)
        return aux;
    printf("\npos = %d ", (*pos));
    printf("%s", lista[(*pos)].word);
    return aux;
}

/* FUNCOES LISTA LIGADA DESORDENADO */

void LLimprime(apontador inicio){
  if(inicio != NULL){
    printf("\n%s ", inicio->pal.word);
  }
  else
    return;
  LLimprime(inicio->prox);
}

apontador LLinsere_fim(apontador inicio, char *palavra){
    apontador novo;
    if(inicio == NULL){
        novo = malloc(sizeof(celula));
        novo->pal.word = palavra;
        novo->pal.qtde = 0;
        novo->prox = NULL;
        novo->ant = NULL;
        return novo;
    }

    inicio->prox = LLinsere_fim(inicio->prox, palavra);
    inicio->prox->ant = inicio;

    return inicio;
}

void LLtroca(apontador a, apontador b){
    word aux;
    aux = a->pal;
    a->pal = b->pal;
    b->pal = aux;
}

apontador LLsepara(char *ordem, apontador ini, apontador fim){
    int p, q;
    apontador auxp, auxq, x;


    auxp = ini;
    for(auxq = ini, q = 0; auxq->prox != NULL; auxq = auxq->prox, q++);

    x = ini;
    p = 0;
    q--;
    auxq = auxq->ant;

    if(strcmp(ordem, "A") == 0){
        while(p < q){
            printf("\nOLA");
            while(strcmp(auxq->ant->pal.word, x->pal.word) > 0){
                /* Enquanto a palavra do fim for a proxima em ordem alfabetica */
                auxq = auxq->ant;
                q--;
            }
            if(p < q)
                LLtroca(auxq, x);
            while(strcmp(auxp->prox->pal.word, x->pal.word) <= 0 && p < q){
                auxp = auxp->prox;
                p++;
            }
            if(p < q)
                LLtroca(auxp, auxq);
        }
        return auxp;
    }
    else{
        while(p < q){
            while(auxq->prox->pal.qtde < x->pal.qtde){
                auxq = auxq->ant;
                q--;
            }
            if(p < q)
                LLtroca(auxp, auxq);
            while(auxq->prox->pal.qtde >= x->pal.qtde && p < q){
                auxp = auxp->prox;
                p++;
            }
            if(p < q)
                LLtroca(auxp, auxq);
        }
        return auxp;
    }
}

void LLquicksort(char *ordem, apontador ini, apontador fim){
    apontador pivo;
    if(fim != NULL && ini != NULL && ini != fim->prox) {
        pivo = LLsepara(ordem, ini, fim);
        LLquicksort(ordem, ini, pivo->ant);
        LLquicksort(ordem, pivo->prox, fim);
    }
}


/* FUNCOES LISTA LIGADA ORDENADO */

/* FUNCOES ARVORE DE BUSCA BINARIA */

galho ABinsere(galho raiz, word palavra, char *ordem){
    /* Devolve a raiz da arvore com a palavra inserida */
    if(raiz == NULL){
        raiz = malloc(sizeof(no));
        raiz->pal.word = palavra.word;
        raiz->pal.qtde = 1;
        raiz->dir = raiz->esq = raiz->pai = NULL;
        return raiz;
    }

        if(strcmp(raiz->pal.word, palavra.word) == 0){
            /* Se a palavra ja estiver na raiz */
            raiz->pal.qtde ++;
            return raiz;
        }
        if(strcmp(raiz->pal.word, palavra.word) > 0){
            /* Se a palavra for a proxima em ordem alfabetica */
            raiz->esq = ABinsere(raiz->esq, palavra, ordem);
        }
        else{
            raiz->dir = ABinsere(raiz->dir, palavra, ordem);
        }
        return raiz;
}

int ABqtde_elementos(galho raiz){
    int qtde = 0;
    if(raiz == NULL)
        return 0;
    qtde += ABqtde_elementos(raiz->esq);
    qtde += ABqtde_elementos(raiz->dir);
    qtde++;
    return qtde;
}

word *listaaux;
int proximapos = 0;

void ABordenar(galho raiz, char *ordem){

    int tam = ABqtde_elementos(raiz), i;
    word *listaaux = malloc(tam * sizeof(word));

    if(strcmp(ordem, "A") == 0 && raiz != NULL){
        ABordenar(raiz->esq, ordem);
        printf("\n%s %d", raiz->pal.word, raiz->pal.qtde);
        ABordenar(raiz->dir, ordem);
    }
    if(strcmp(ordem, "O") == 0 && raiz != NULL){
        for(i = 0; i < tam; i++){


            if(raiz->esq != NULL){
                ABordenar(raiz->esq, ordem);
            }
            listaaux[i] = raiz->pal;
            if(raiz->dir != NULL){
                ABordenar(raiz->dir, ordem);
            }

        }
        VDquicksort(listaaux, tam, ordem, 0, tam);
        if(i == tam){
            for(i = 0; i < tam; i++){
                printf("\n%s %d", listaaux[i].word, listaaux[i].qtde);
            }
        }
    }
}



/* ********************************************************************************************** */


int main(int argc, char **argv){
    FILE *arq;
    char *buffer = malloc(TAM_INICIAL * sizeof(char));
    word palavra;
    word *lista = malloc(TAM_INICIAL * sizeof(word));
    int i, max = TAM_INICIAL, cond;
    galho raiz = NULL;
    /*apontador LL = malloc(TAM_INICIAL * sizeof(celula));*/

    palavra.word = malloc(TAM_INICIAL * sizeof(char));

    if (argc < 4) {
        printf("Argumentos insuficientes!\n");
        return 0;
    }
    if(strcmp(argv[3], "O") != 0 && strcmp(argv[3], "A") != 0){
        printf("\nOrdenacao nao e nem alfabetica nem de ocorrencia");
        return 0;
    }
    arq = fopen(argv[1], "r");
    if (!arq){
        perror("Problema ao abrir o arquivo");
        return 0;
    }

    cond = caso(argv[2]);

    if(cond == 11){ /* VD*/
        for(i = 0; i < TAM_INICIAL; i++){
            lista[i].word = malloc(TAM_INICIAL * sizeof(char));
        }
        for(i = 0; pega_palavra(arq, buffer, palavra) == 1; i++){
            lista = VD_insere(lista, palavra, &i, &max);
            palavra.word = malloc(TAM_INICIAL * sizeof(char*));
        }
        VDimprime_lista(lista, i, argv[3]);
    }
    else if(cond == 12){ /* VO */
        for(i = 0; i < TAM_INICIAL; i++){
        lista[i].word = malloc(TAM_INICIAL * sizeof(char));
        }
        for(i = 0; pega_palavra(arq, buffer, palavra) == 1; i++){
            printf("\n%s", palavra.word);
            lista = VO_insere(lista, palavra, &i, &max, argv[3]);
            palavra.word = malloc(TAM_INICIAL * sizeof(char*));
            printf("\n%s", lista[i].word);
        }
        VDimprime_lista(lista, i, argv[3]);
    }
    else if(cond == 21){ /* LD */
        /*for(i = 0; i < TAM_INICIAL; i++){
            LL->pal.word = malloc(TAM_INICIAL * sizeof(char));
        }

        for(i = 0; pega_palavra(arq, buffer, palavra) == 1; i++){
            LL = LLinsere_fim(LL, palavra.word);
            palavra.word = malloc(TAM_INICIAL * sizeof(char*));
        }


        for(listaaux = LL; listaaux->prox != NULL; listaaux = listaaux->prox);

        LLquicksort(argv[3], LL, listaaux);

        LLimprime(LL);
        */
    }
    else if(cond == 22){ /* LO */
        /*for(i = 0; i < TAM_INICIAL; i++){
            LL->pal.word = malloc(TAM_INICIAL * sizeof(char));
        }

        for(i = 0; pega_palavra(arq, buffer, palavra) == 1; i++){
            LL = LLinsere_fim(LL, palavra.word);
            palavra.word = malloc(TAM_INICIAL * sizeof(char*));
        }


        for(listaaux = LL; listaaux->prox != NULL; listaaux = listaaux->prox);
        LLimprime(LL);

        LLquicksort(argv[3], LL, listaaux);

        LLimprime(lista);
        */
    }
    else if(cond == 3){ /* AB */
        for(i = 0; i < TAM_INICIAL; i++){
            raiz->pal.word = malloc(TAM_INICIAL * sizeof(char));
        }
        for(i = 0; pega_palavra(arq, buffer, palavra) == 1; i++){
            raiz = ABinsere(raiz, palavra, argv[3]);
            palavra.word = malloc(TAM_INICIAL * sizeof(char*));
        }
        listaaux = malloc(ABqtde_elementos(raiz) * sizeof(word));
        ABordenar(raiz, argv[3]);
        if(strcmp(argv[3], "A") == 0){}
        else{
            VDquicksort(listaaux, ABqtde_elementos(raiz), argv[3], 0, ABqtde_elementos(raiz));
            VDimprime_lista(listaaux, ABqtde_elementos(raiz), argv[3]);
        }
    }
    else{
        printf("Metodo invalido de organizacao\n");
    }
    return 0;
}
