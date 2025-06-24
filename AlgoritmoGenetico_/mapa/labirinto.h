#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct _lab{
    char** matriz;
    int linhas;
    int colunas;
    int inicioX, inicioY;
    int fimX, fimY;
}Labirinto;

Labirinto CarregarLabirinto(const char* caminho);
int posicaoFinalInicial();
int movimentoValido(Labirinto* lab, int x, int y);
void liberarLabirinto(Labirinto* lab);
void imprimirLabirinto(Labirinto* lab);


#endif