#ifndef GENETICO_H
#define GENETICO_H
#include "config/config.h"
#include "mapa/labirinto.h"
#include "../populacao/individuo.h"
#include "../populacao/populacao.h"


Individuo* selecaoRoleta(Populacao* populacao);
void organizarFitness(Populacao* populacao);
Individuo* replicar(Individuo* original, Config* config);
Populacao* elitismo(Populacao* atual, Config* config);
TNo* individuoAleatorio(Populacao* populacao);
void pais(Populacao* nova, Populacao* original, Config* config, Labirinto* lab);
Individuo* crossover(Individuo* pai, Individuo* mae, Config* config);
TNo* melhorIndividuo(Populacao* populacao);

#endif