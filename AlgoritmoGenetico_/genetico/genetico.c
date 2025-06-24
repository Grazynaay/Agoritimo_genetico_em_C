#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genetico.h"
#include "populacao/populacao.h"
#include "config/config.h"
#include "mapa/labirinto.h"
#include "populacao/individuo.h"



Individuo* selecaoRoleta(Populacao* populacao) {
    float soma_fitness = 0.0f;
    TNo* aux = populacao->inicio;

    while (aux != NULL) {
        soma_fitness += aux->individuo.fitness;
        aux = aux->prox;
    }

    if (soma_fitness == 0) return NULL;

    float _sorteado = ((float) rand() / (float) RAND_MAX) * soma_fitness;

    float valor_acumulado = 0.0f;
    aux = populacao->inicio;
    while (aux != NULL) {
        valor_acumulado += aux->individuo.fitness;
        if (valor_acumulado >= _sorteado) {
            return &aux->individuo;
        }
        aux = aux->prox;
    }

    return &populacao->fim->individuo; 
}

void organizarFitness(Populacao* populacao) {
    if (!populacao || !populacao->inicio) 
        return;

    int trocou;
    TNo* atual;
    TNo* fim = NULL;

    do {
        trocou = 0;
        atual = populacao->inicio;

        while (atual->prox != fim) {
            if (atual->individuo.fitness < atual->prox->individuo.fitness) {
            
                Individuo temp = atual->individuo;
                atual->individuo = atual->prox->individuo;
                atual->prox->individuo = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
        fim = atual;
    } while (trocou);
}

Individuo* replicar(Individuo* original, Config* config) {
    Individuo* replica_individuo = Individuocreate(config->tamanho_genoma);
    for (int i = 0; i < config->tamanho_genoma; i++) {
        replica_individuo->genoma[i] = original->genoma[i];
    }
    replica_individuo->fitness = original->fitness;
    return replica_individuo;
}



Populacao* elitismo(Populacao* atual, Config* config) {
    organizarFitness(atual);

    Populacao* nova = criarPopulacao();
    int meia_populacao = config->num_individuos / 2;

    TNo* atualNo = atual->inicio;
    for (int i = 0; i < meia_populacao && atualNo != NULL; i++) {
        Individuo* replica_individuo = replicar(&atualNo->individuo, config);
        inserirnaPopulacao(nova, replica_individuo);
        atualNo = atualNo->prox;
    }

    return nova;
}

TNo* individuoAleatorio(Populacao* populacao) {
    if (populacao == NULL || populacao->inicio == NULL) return NULL;

    int posicao = rand() % populacao->max_populacao;  
    TNo* atual = populacao->inicio;

    for (int i = 0; i < posicao; i++) {
        if (atual->prox != NULL) {
            atual = atual->prox;
        } else {
            break;  
        }
    }

    return atual;  
}


void pais (Populacao* nova, Populacao* original, Config* config, Labirinto* lab) {
    int livre = config->num_individuos - nova->max_populacao;

    for (int i = 0; i < livre; i++) {
        TNo* pai = individuoAleatorio(original);
        TNo* mae = individuoAleatorio(original);

        Individuo* filho = crossover(&pai->individuo, &mae->individuo, config);
        simularIndividuo(lab, filho, config);
        inserirnaPopulacao(nova, filho);
    }
}

Individuo* crossover(Individuo* pai, Individuo* mae, Config* config) {
    Individuo* filho = Individuocreate(config->tamanho_genoma);
    int ponto = rand() % config->tamanho_genoma;

    for (int i = 0; i < config->tamanho_genoma; i++) {
        if (i < ponto) {
            filho->genoma[i] = pai->genoma[i];
        } else {
            filho->genoma[i] = mae->genoma[i];
        }
    }

    return filho;
}

TNo* melhorIndividuo(Populacao* populacao) {
    if (populacao == NULL || populacao->inicio == NULL) return NULL;

    TNo* melhor_individuo = populacao->inicio;
    TNo* atual = populacao->inicio->prox;

    while (atual != NULL) {
        if (atual->individuo.fitness > melhor_individuo->individuo.fitness) {
            melhor_individuo = atual;
        }
        atual = atual->prox;
    }

    return melhor_individuo; 
} 

void salvarEvolucao(int geracao, TNo* melhorIndividuo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "a");  
    if (!arquivo) {
        printf("Erro ao abrir arquivo '%s' para escrita.\n", nomeArquivo);
        return;
    }

    fprintf(arquivo, "%d,%.2f,%s\n", geracao, melhorIndividuo->individuo.fitness, melhorIndividuo->individuo.genoma);
    fclose(arquivo);
}
