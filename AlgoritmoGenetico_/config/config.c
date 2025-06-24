#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"


Config carregarConfiguracao(const char* caminho){
    Config config = {0};
    FILE* arq = fopen(caminho, "r");

    if(!arq){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arq)){
        if(linha[0] == '#' || linha[0] == ';'|| linha[0] == '\n' || linha[0] == '[') continue;
        
        char chave[50], valor[50];
        if (sscanf(linha, "%[^=]=%s", chave, valor) == 2){
            
            char* k = strtok(chave, " \t");
            char* v = strtok(valor, " \t\n");

            if (strcmp(k, "num_individuos") == 0)
                config.num_individuos = atoi(v);
            else if (strcmp(k, "tamanho_genoma") == 0)
                config.tamanho_genoma = atoi(v);
            else if (strcmp(k, "taxa_mutacao") == 0)
                config.taxa_mutacao = atof(v);
            else if (strcmp(k, "elitismo") == 0)
                config.elitismo = atoi(v);
            else if (strcmp(k, "max_geracoes") == 0)
                config.max_geracoes = atoi(v);
            else if (strcmp(k, "apenas_movimentos_validos") == 0)
                config.apenas_movimentos_validos = atoi(v);
        }
           
    }
    fclose(arq);
    return config;
}
