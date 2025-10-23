// cria_indice: Cria um arquivo indice_ceps.dat com base num arquivo desordenado cep.dat contendo informações de vários endereços com base em seus respectivos CEPs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "endereco.h"

// compara: função que compara dois endereços
int compara(const void *i1, const void *i2) {
    return strncmp(((EnderecoIndice*)i1)->cep, ((EnderecoIndice*)i2)->cep, 8);
}

int main() {
    FILE *f, *saida;
    Endereco buffer; 
    EnderecoIndice* indices;
    long qtdEnderecos, currentPos;

    f = fopen("cep.dat", "rb");
    if(!f) {
        fprintf(stderr, "ERRO: Arquivo cep.dat inexistente\n");
    }
    saida = fopen("indice_ceps.dat", "w+b");

    fseek(f, 0, SEEK_END);
    qtdEnderecos = ftell(f) / sizeof(Endereco);
    rewind(f);

    // indices: array de estruturas EnderecoIndice para armazenar cada entrada do índice
    indices = (EnderecoIndice*) malloc(qtdEnderecos * sizeof(EnderecoIndice));

    printf("Lendo endereços de cep.dat e criando registros...\n");
    long i = 0;
    fread(&buffer, sizeof(Endereco), 1, f);
    while(!feof(f) && i < qtdEnderecos) { // armazena CEP e posição de cada endereço numa entrada do índice
        strcpy(indices[i].cep, buffer.cep);
        indices[i].pos = i;
        fread(&buffer, sizeof(Endereco), 1, f);
        i++;
    }
    qsort(indices, qtdEnderecos, sizeof(EnderecoIndice), compara); // ordena o array com base na função compara

    fwrite(indices, sizeof(EnderecoIndice), qtdEnderecos, saida); // escreve o array de registros ordenado no arquivo de saída
    free(indices); // libera a memória alocada para os índices

    printf("Finalizado!\n");
    fclose(saida);
    return 0;
}