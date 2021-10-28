#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define P 0.5
#define maxnivel 20
#define word 50
#define defni 140

typedef struct skiplist skiplist;
typedef struct node no;

struct node{
  char palavra[word];
  char definicao[defni];
  no **prox;
};

struct skiplist{
  int nivelmax;
  float p;
  int nivel;
  no *inicio;
};

skiplist *criar(int max, float p);
no *novono(char *palavra, char *definicao, int nivel);
int randomlvl();
int busca(skiplist *sl, char *palavra);
int inserir(skiplist *sl, char *palavra, char *definicao);
int remover(skiplist *sl, char *palavra);
int alterar(skiplist *sl, char *palavra, char *alteracao);
void imprimir(skiplist *sl, char ch);
void liberar(skiplist *sl);
