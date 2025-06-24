#include <stdio.h>
#include <stdlib.h>
#include "config/config.h"
#include "mapa/labirinto.h"
#include "populacao/individuo.h"
#include "populacao/populacao.h"
#include "genetico/genetico.h"

int main() {
    
    Config confi = carregarConfiguracao("config/config.ini"); //testando configurações
    // printf("Numero de individuos: %d\n", confi.num_individuos);
    // // printf("Tamanho do genoma: %d\n", confi.tamanho_genoma);
    // // printf("Taxa de mutacao: %.2f\n", confi.taxa_mutacao);

    Labirinto labi = CarregarLabirinto("labirinto1.txt");   //testando leitura do labirinto
    imprimirLabirinto(&labi);
    

    Individuo* ind = Individuocreate(confi.tamanho_genoma);
    gerarIndividuo(ind, &confi);
    imprimirIndividuo(ind);
    simularIndividuo(&labi, ind, &confi);
    printf("Posicao final: (%d, %d)\n", ind->posicaoFinal[0], ind->posicaoFinal[1]);
    printf("Fitness: %d\n", ind->fitness);

    Populacao* pop = gerarPopulacaoInicial(&confi, &labi);
    imprimirPopulacao(pop);

    Populacao* nova = criarPopulacao();
    pais(nova, pop, &confi, &labi);

  

    FILE* f = fopen("evolucao.csv", "w");
        if (f) {
        fprintf(f, "geracao,fitness,movimentos\n");
        fclose(f);
    }

    for (int ger = 0; ger < confi.max_geracoes; ger++) {
        Populacao* nova = criarPopulacao();
        pais(nova, pop, &confi, &labi);

        liberarPopulacao(pop);
        pop = nova;

        TNo* melhor = melhorIndividuo(pop);

        salvarEvolucao(ger, melhor, "evolucao.csv");

        printf("Geracao %d: melhor fitness = %d\n", ger, melhor->individuo.fitness);
    }
    
    free(ind->genoma);
    free(ind);

    return 0;
}
