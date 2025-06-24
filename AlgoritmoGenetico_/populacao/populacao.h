#ifndef POPULACAO_H
#define POPULACAO_H

#include "../populacao/individuo.h"
#include "../config/config.h"
#include "individuo.h"

typedef struct _no{
    Individuo individuo;
    struct _no *prox, *ant;
}TNo;

typedef struct _list{
    TNo* inicio;
    TNo* fim;
    int max_populacao;
} Populacao;

Populacao* criarPopulacao();
TNo* TNo_createNFill(Individuo* individuo);
void inserirnapopulacao(Populacao* p, Individuo* ind);
Populacao* gerarPopulacaoInicial(Config* confi, Labirinto* lab);
void imprimirPopulacao(Populacao* p);
void liberarPopulacao(Populacao* p);




#endif
