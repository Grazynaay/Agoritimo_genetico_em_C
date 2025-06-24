#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "populacao/populacao.h"
#include "populacao/individuo.h"



TNo* TNo_createNFill(Individuo* individuo){
   TNo* novo = malloc(sizeof(TNo));
   if(novo){
       novo->individuo = *individuo; // copia o conteúdo
       novo->prox = NULL;
        novo->ant = NULL;
    }
   return novo;
}


Populacao* criarPopulacao(){
    Populacao* p = malloc(sizeof(Populacao));
    if (p == NULL) {
        printf("Erro ao alocar memória para população\n");
        exit(1);
    }
    p->inicio= NULL;
    p->fim = NULL;
    p->max_populacao = 0;
    return p;
}


void inserirnaPopulacao(Populacao* p, Individuo* ind){
    TNo* novo = TNo_createNFill(ind);

    if(p->inicio == NULL){
        p->inicio = novo;
        p->fim = novo;
    }else{
        novo->ant = p->fim;
        p->fim->prox = novo;
        p->fim = novo;
    }
    p->max_populacao++;
}


Populacao* gerarPopulacaoInicial(Config* confi, Labirinto* lab){
    Populacao* pop = criarPopulacao();

    for(int i = 0; i < confi->num_individuos; i++){
        Individuo* novoInd = Individuocreate(confi->tamanho_genoma);
        if(novoInd == NULL){
            printf("Erro ao criar individuo %d\n", i);
            continue;
        }
        gerarIndividuo(novoInd, confi);
        simularIndividuo(lab, novoInd, confi);
        inserirnaPopulacao(pop, novoInd);

    }
    return pop;
}

void imprimirPopulacao(Populacao* p){
    TNo* aux = p->inicio;

    while(aux!=NULL){
        imprimirIndividuo(&aux->individuo);
        aux = aux->prox;
    }
    putchar('\n');
}

void liberarPopulacao(Populacao* p) {
    TNo* aux = p->inicio;
    while (aux != NULL) {
        TNo* temp = aux;
        aux = aux->prox;
        free(temp->individuo.genoma);
        free(temp);
    }
    free(p);
}


