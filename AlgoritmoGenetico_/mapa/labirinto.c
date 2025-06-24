#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labirinto.h"



Labirinto CarregarLabirinto(const char* caminho){
    Labirinto lab;
    lab.linhas = 0;
    lab.colunas = 0;
    lab.matriz = NULL;

    FILE *arq = fopen(caminho, "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[200];
    char** totalLinhas = NULL;
    int linhasLidas = 0;
    int maiorColuna = 0;

      while (fgets(linha, sizeof(linha), arq)) {
        int len = strlen(linha);
        if (linha[len - 1] == '\n') linha[len - 1] = '\0';

        // Atualiza o número de colunas se necessário
        if (len > maiorColuna) maiorColuna = len;

        // Aloca espaço para nova linha
        totalLinhas = realloc(totalLinhas, (linhasLidas + 1) * sizeof(char*));
        totalLinhas[linhasLidas] = malloc((len + 1) * sizeof(char));
        strcpy(totalLinhas[linhasLidas], linha);
        linhasLidas++;
    }

    fclose(arq);

    lab.linhas = linhasLidas;
    lab.colunas = maiorColuna;
    lab.matriz = malloc(lab.linhas * sizeof(char*));

    // Copia os dados para a matriz final e localiza 'S' e 'E'
    for (int i = 0; i < lab.linhas; i++) {
        lab.matriz[i] = malloc((lab.colunas + 1) * sizeof(char));
        for (int j = 0; j < lab.colunas; j++) {
            char c = totalLinhas[i][j];
            lab.matriz[i][j] = (c == '\0') ? ' ' : c; 

            if (c == 'S') {
                lab.inicioX = i;
                lab.inicioY = j;
            } else if (c == 'E') {
                lab.fimX = i;
                lab.fimY = j;
            }
        }
        lab.matriz[i][lab.colunas] = '\0';
        free(totalLinhas[i]); 
    }

    free(totalLinhas);
    return lab;
}

int movimentoValido(Labirinto* lab, int x, int y){
     return (x >= 0 && x < lab->linhas &&
            y >= 0 && y < lab->colunas &&
            lab->matriz[x][y] != '#');
}



void imprimirLabirinto(Labirinto* lab){
    for (int i = 0; i < lab->linhas; i++) {
        for (int j = 0; j < lab->colunas; j++) {
            printf("%c", lab->matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarLabirinto(Labirinto* lab);