#include <stdio.h>
#include <stdlib.h>
#define MAX_LETRAS 20 /*  M�ximo de letras que uma palavras da entrada pode ter */

#define DIREITA 'd'
#define BAIXO 'b'
#define ALFABETO 26
#define BRANCO ' '
#define PRETO '*'
#define TipoDaPilha char

typedef struct {
  TipoDaPilha * v;
  int topo;
  int max;
} pilha;

typedef pilha * Pilha;

Pilha CriaPilha (int tam)
{
  Pilha P;
  P = malloc (sizeof(pilha));

  P->topo = 0;
  P->max  = tam;
  P->v = malloc (tam * sizeof(TipoDaPilha));
  return (P);
}

void DestroiPilha (Pilha P)
{
  free(P->v);
  free(P);
}

void resize (Pilha P)
{
  int i;
  TipoDaPilha * aux = P->v;
  P->v = malloc (2*P->max*sizeof(TipoDaPilha));
  for (i = 0; i < P->topo; i++)
    P->v[i] = aux[i];
  P->max = 2 * P->max;
  free(aux);
}

void Empilha (Pilha P, TipoDaPilha c)
{
  if (P->topo == P->max) resize(P);
  P->v[P->topo] = c;
  P->topo ++;
}

int PilhaVazia(Pilha P)
{
  return (P->topo == 0);
}

void Desempilha(Pilha P)
{
  if (PilhaVazia(P)) printf("ERRO");
  P->topo --;
}

TipoDaPilha TopoDaPilha(Pilha P)
{
  if (PilhaVazia(P)) printf("ERRO");
  return (P->v[P->topo - 1]);
}


int maximo(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}


void cria_matriz_char(char **M, int linhas, int colunas){
    int i;
    M = malloc(linhas * sizeof(char *));
    for(i=0; i < linhas; i++){
        M[i] = malloc(colunas * sizeof(char));
    }
}




void imprime_matriz_char(char **M, int linhas, int colunas){
    int i, j;
    for(i=0; i < linhas; i++){
        for(j=0; j < colunas; j++){
            printf("%c ", M[i][j]);
        }
        printf("\n");
    }
}


/* Esta struct guarda onde um espa�o dispon�vel na matriz come�a e em que dire��o vai.
   A vari�vel pos define um inteiro que serve para auxiliar na permuta��o da struct numa lista.  */
typedef struct{
    int pos;
    int usado;
    int i;
    int j;
    char sentido;
}posicao;

typedef struct {
  posicao * v;
  int topo;
  int max;
} pilha_posicoes;

typedef pilha_posicoes * Pilha_posicoes;

Pilha_posicoes CriaPilha_posicoes (int tam)
{
  Pilha_posicoes P;
  P = malloc (sizeof(pilha_posicoes));

  P->topo = 0;
  P->max  = tam;
  P->v = malloc (tam * sizeof(posicao));
  return (P);
}

void DestroiPilha_posicoes (Pilha_posicoes P)
{
  free(P->v);
  free(P);
}

void resize_posicoes (Pilha_posicoes P)
{
  int i;
  posicao * aux = P->v;
  P->v = malloc (2*P->max*sizeof(posicao));
  for (i = 0; i < P->topo; i++)
    P->v[i] = aux[i];
  P->max = 2 * P->max;
  free(aux);
}

void Empilha_posicoes (Pilha_posicoes P, posicao c)
{
  if (P->topo == P->max) resize_posicoes(P);
  P->v[P->topo] = c;
  P->topo ++;
}

int PilhaVazia_posicoes(Pilha_posicoes P)
{
  return (P->topo == 0);
}

void Desempilha_posicoes(Pilha_posicoes P)
{
  if (PilhaVazia_posicoes(P)) printf("ERRO");
  P->topo --;
}

posicao TopoDaPilha_posicoes(Pilha_posicoes P)
{
  if (PilhaVazia_posicoes(P)) printf("ERRO");
  return (P->v[P->topo - 1]);
}

/* Cria uma lista (natriz) em que se pode p�r linhas*colunas posi��es. */
posicao cria_lista_posicoes(int linhas, int colunas){
    int i;
    posicao **lista = malloc(linhas * sizeof(posicao));
    for(i=0; i < linhas; i++){
        lista[i] = malloc(colunas * sizeof(Pilha_posicoes));
    }
    return lista;
}


/* Recebe uma matriz com espa�os e asteriscos e devolve uma matriz com as posi��es v�lidas de se p�r cada tamanho de palavra. */
posicao lista_posicoes(char **matriz, int linhas, int colunas, posicao **lista){
    int i, j, k, aux;
    posicao auxiliar;

    lista = malloc(maximo(linhas, colunas) * sizeof(posicao));
    for(i=0; i < maximo(linhas, colunas); i++){
        lista[i] = CriaPilha_posicoes(linhas + colunas);
        /* lista[i] = malloc((linhas + colunas) * sizeof(posicao)); */
    }

    for(i=0; i < linhas; i++){
        for(j=0; j < colunas; j++){
            k = 0;
            if(matriz[i][j] != PRETO && matriz[i][j + 1] == BRANCO){
                aux = j;
                while(matriz[i][j + 1] != PRETO && j < colunas){
                    k++;
                    j++;
                }
                auxiliar.i = i;
                auxiliar.j = aux;
                auxiliar.sentido = DIREITA;
                auxiliar.pos = lista[k - 1]->topo;
                auxiliar.usado = 0;
                Empilha_posicoes(lista[k - 1], auxiliar);
                /* lista[k - 1][].i = i;
                lista[k - 1][].j = aux;
                lista[k - 1][].sentido = DIREITA;
                lista[k - 1][].pos =  */
            }
        }
    }

    for(j=0; j < colunas; j++){
        for(i=0; i < linhas; i++){
            k = 0;
            if(matriz[i][j] != PRETO && matriz[i + 1][j] == BRANCO){
                aux = i;
                while(matriz[i + 1][j] != PRETO && i < linhas){
                    k++;
                    i++;
                }
                auxiliar.i = aux;
                auxiliar.j = j;
                auxiliar.sentido = BAIXO;
                auxiliar.pos = lista[k - 1]->topo;
                auxiliar.usado = 0;
                Empilha(lista[k - 1], auxiliar);
            }
        }
    }
    return lista;
}




/* Esta struct guarda uma string, a quantiddade de caracteres que ela possui e o estado dela (se est� dentro ou fora da matriz.
   A vari�vel posi��o define um inteiro que serve para auxiliar na permuta��o da struct numa lista.  */
typedef struct{
    int posicao;
    int usado;
    char *string;
    int tam;
}palavra;

typedef struct {
  palavra * v;
  int topo;
  int max;
} pilha_palavras;

typedef pilha_palavras * Pilha_palavras;

Pilha_palavras CriaPilha_palavras (int tam)
{
  Pilha_palavras P;
  P = malloc (sizeof(Pilha_palavras));

  P->topo = 0;
  P->max  = tam;
  P->v = malloc (tam * sizeof(palavra));
  return (P);
}

void DestroiPilha_palavras (Pilha_palavras P)
{
  free(P->v);
  free(P);
}

void resize_palavras (Pilha_palavras P)
{
  int i;
  palavra * aux = P->v;
  P->v = malloc (2*P->max*sizeof(palavra));
  for (i = 0; i < P->topo; i++)
    P->v[i] = aux[i];
  P->max = 2 * P->max;
  free(aux);
}

void Empilha_palavras (Pilha_palavras P, palavra c)
{
  if (P->topo == P->max) resize_palavras(P);
  P->v[P->topo] = c;
  P->topo ++;
}

int PilhaVazia_palavras(Pilha_palavras P)
{
  return (P->topo == 0);
}

void Desempilha_palavras(Pilha_palavras P)
{
  if (PilhaVazia_palavras(P)) printf("ERRO");
  P->topo --;
}

palavra TopoDaPilha_palavras(Pilha_palavras P)
{
  if (PilhaVazia_palavras(P)) printf("ERRO");
  return (P->v[P->topo - 1]);
}


/* Recebe uma string e devolve quantas letras h� nela. */
int conta_letras(char *palavra){
    int i = 0;
    while(palavra[i] != '\0')
        i++;
    return i;
}

Pilha_palavras cria_lista_palavras(int qtde_palavras){
    int i;
    char* word;
    palavra *auxiliar, *lista;

    lista = cria_lista_palavras(qtde_palavras);

    for(i=0; i < qtde_palavras; i++){
            scanf("[^\n]%c", word);
            auxiliar[i].string = word;
            auxiliar[i].tam = conta_letras(word);

            auxiliar[i].posicao = i;
            auxiliar[i].usado = 0;

            Empilha_palavras(lista, auxiliar);
    }
    return lista;
}




/* Recebe um caractere e retorna 1 se ele for uma letra. */
int ser_letra(char ch){
    if('a' - ch < ALFABETO)
        return 1;
    return 0;
}

/* Recebe o sentido para onde a palavra � escrita e, abstratamente falando, devolve uma dupla ordenada (*a, *b)
   a qual pode ser (0,1) se o sentido for para baixo e (1,0) se for para a direita.  */
void definir_sentido(char dir, int *a, int *b){
    if(dir == DIREITA){
        *a = 1;
        *b = 0;
    }
    if(dir == BAIXO){
        *b = 1;
        *b = 0;
    }
}

/* Rcebe a e b, um deles, por suposi��o, nulo. Incrementa em uma unidade aquele que n�o for o nulo. */
void aumenta_nao_nulos(int *a, int *b){
    if(*a == 0)
        (*b)++;
    else
        (*a)++;
}

/* Recebe uma matriz de caracteres, uma posi��o dentro dela, uma palavra e uma pilha de letras.
   Caso a palavra encaixe na matriz, partindo da posi��o dada, as letras que a palavra acrescenta � matriz.
   Essas letras que foram postas matriz s�o empilhadas tamb�m. Nesse caso a fun��o retorna 1.
   Caso a palavra n�o encaixe, ela n�o � posta na matriz e a fun��o retorna 0. */
int encaixa (char **matriz, posicao inicio, palavra palavra, Pilha letras){
    int a, b, k;
    posicao aux;
    definir_sentido(inicio.sentido, &a, &b);

    for(k=0; k < palavra.tam; k++){
        if(matriz[inicio.i + a][inicio.j + b] != palavra.string[k]){
            if(ser_letra(matriz[inicio.i + a][inicio.j + b]) == 1){
                while(k >= 0){
                    Desempilha(letras);
                    k--;
                }
                return 0;
            }

            else{
                /* Muita aten��o aqui!! Neste momento, uso a parte "sentido" da struct posicao para poder compatibilzar
                   o formato de entrada dos elementos da pilha, mas entende-se que se ets� empilhando letras aqui. */
                aux.sentido = palavra.string[k];
                aux.i = inicio.i + a;
                aux.j = inicio.j + b;
                Empilha(letras, aux.sentido);
                matriz[inicio.i + a][inicio.j + b] = palavra.string[k];
            }
        }

        else
            aumenta_nao_nulos(&a, &b);
    }
    return 1;
}

/*  Recebe uma lista de palavras, o tamanho dela e a �ltima palavra contida nela que foi testada.
    Permuta a �ltima palavra testada e reorganiza a lista de palavras.  */
void permuta_palavra(int qtde, palavra *lista, palavra ultimo_testado){
    int i, j;
    palavra permutante;
    for(i=0; i < qtde; i++){
        if(lista[i].usado == 0){
            for(j=0; j < ultimo_testado.posicao - i; j++){
                permutante.posicao = lista[i].posicao;
                lista[i].posicao = ultimo_testado.posicao;
            }
        }
    }
}

/* Recebe uma lista de posicoes, o tamanho dela e a �ltima posicao contida nela que foi testada.
   Permuta a �ltima posi��o testada e reorganiza a lista de posi��es.  */
void permuta_posicao(int qtde, posicao *lista, posicao ultimo_testado){
    int i, j;
    posicao permutante;
    for(i=0; i < qtde; i++){
        if(lista[i].usado == 0){
            for(j=0; j < ultimo_testado.pos - i; j++){
                permutante.pos = lista[i].pos;
                lista[i].pos = ultimo_testado.pos;
            }
        }
    }
}

int permutou_totalmente_posicoes(Pilha_posicoes pos_pilha, int linhas, int colunas){
    int i;
    for(i=0; i < maximo(linhas, colunas); i++){
        if(pos_lista[i].pos != pos_lista[i + 1].pos + 1)
            return 0;
    }
    return 1;
}

int todas_posicoes_usadas(Pilha_posicoes pos_pilha, ){
    int i;
    for(i=0; i < (pos_pilha->v[pos_pilha->topo]).pos; i++){
        if((pos_pilha->v[pos_pilha->topo]).usado == 0)
            return 0;
    }
    return 1;
}

int permutou_totalmente_palavras(palavra *pal_lista, int qtde_pal){
    int i;
    for(i=1; i <= qtde_pal ; i++){
        if(pal_lista[i - 1].posicao != pal_lista[i].posicao + 1)
            return 0;
    }
    return 1;
}

int todas_palavras_usadas(palavra *pal_lista, int qtde_pal){
    int i;
    for(i=0; i < qtde_pal; i++){
        if(pal_lista[].usado == 0)
            return 0;
    }
    return 1;
}

int backtracking(char **matriz, int linhas, int colunas, posicao **pos_lista, palavra *pal_lista, int qtde_pal, posicao inicio, char *letras, palavra ultimo_testado_pal, posicao ultimo_testado_pos){
    int tam_pal, i;
    char verifica;
    Pilha_posicoes pilha_pos = pos_lista[tam_pal - 1];


    while(permutou_totalmente_posicoes(pos_pilha) == 0){
        if(encaixa(matriz, inicio, pal_lista[], letras) == 0)
            for(i=0; i < ; i++)
              Desempilha(letras);

        if(todas_posicoes_usadas(pilha_pos) == 1){
            if(todas_palavras_usadas() == 1)
                return 1;
            permuta_palavra(qtde_pal, pal_lista, ultimo_testado_pal);
        }

        if(permutou_totalmente_palavras(pal_lista, qtde_pal) == 1)
            return 0;
        pilha_pos = pos_lista[tam_pal - 1];
        permuta_posicao(qtde_pal, pal_lista, ultimo_testado_pal);
    }
}



/*
       Cria a matriz dinamicamente e substitui os -1s por asteriscos.
       Lista as posi�oes poss�veis
       Conta as letras das palavras.
       Poe as palavras numa lista

       Testa as permuta�oes enquato as palavras encaixarem
       Se nao encaixar em uma posicao v�lida, tenta encaixar numa v�lida (permuta as posicoes)
       Se acabar a lista e n�o houver posi��o v�lida, permuta as palavras e volta a tentar encaixar

       Se todas as palavras foram postas (a lista toda ta com a variavel "usado" valendo 1
    */
int main()
{
    int i, j, linhas, colunas, aux, qtde_pal, instancia = 0;
    char **matriz, *letras;
    posicao **pos_lista, ultimo_testado_pos, inicio;
    palavra *pal_lista, ultimo_testado_pal;

    scanf("%d %d", &linhas, &colunas);
    cria_matriz_char(matriz, linhas, colunas);

    while(linhas != 0 && colunas !=0){

       instancia++;

       for(i=0; i < linhas; i++){
           for(j=0; j < colunas; j++){
               scanf("%d", &aux);
               if(aux == -1)
                   matriz[i][j] = PRETO;
               else
                   matriz[i][j] = BRANCO;
           }
       }

       pos_lista = cria_lista_posicoes(pos_lista, linhas, colunas);
       lista_posicoes(matriz, linhas, colunas, pos_lista);

       scanf("%d", &qtde_pal);
       pal_lista = cria_lista_palavras(qtde_pal);

       if(backtracking(matriz, linhas, colunas, pos_lista, pal_lista, qtde_pal, inicio, letras, ultimo_testado_pal, ultimo_testado_pos) == 1){
            printf("Instancia %d\n", instancia);
            imprime_matriz_char(matriz, linhas, colunas);
       }
       else
            printf("Instancia %d\nnao ha solucao", instancia);


       printf("Instancia %d\nnao ha solucao", instancia);


       scanf("%d %d", &linhas, &colunas);
       cria_matriz_char(matriz, linhas, colunas);
    }
    return 0;
}
