#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include "../config/config.h"
#include "../mapa/labirinto.h"


typedef struct _ind{
    char *genoma; 
    int tamanho;
    int fitness;
    int posicaoFinal[2];
} Individuo;

/**
 * função que gera o individuo aleatorio
 * @param individuo
 * @param Config
 */
void gerarIndividuo(Individuo *ind, Config *confi);

Individuo* Individuocreate(unsigned int max_parametro);
void simularIndividuo(Labirinto *lab, Individuo *ind, Config *confi);
Individuo calcularFitness(Individuo *ind, Config *confi);
Individuo mutacaoInd(Individuo *ind, Config *confi);
void imprimirIndividuo(Individuo *ind);

#endif