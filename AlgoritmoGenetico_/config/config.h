#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int num_individuos;
    int tamanho_genoma;
    float taxa_mutacao;
    int elitismo;
    int max_geracoes;
    int apenas_movimentos_validos;
    char saida_log[100];
} Config;

/**
 * função que carrega o arquivo de configuração 
 * @param caminho do arquivio
 */
Config carregarConfiguracao(const char* caminho);

#endif