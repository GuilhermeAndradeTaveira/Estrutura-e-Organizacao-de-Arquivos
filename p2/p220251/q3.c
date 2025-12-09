#include <stdio.h>

typedef struct {
  int codigo;
  char descricao[40];
  float preco;
} Produto;

int insere(Produto p) {
  long pos;
  if (bplus_search(arvore_bplus, p.codigo, &pos)) {
    return 0;
  }
  fseek(arquivo_dados, 0, SEEK_END);
  long offset = ftell(arquivo_dados);

  fwrite(&p, sizeof(Produto), 1, arquivo_dados);

  return bplus_insert(arvore_bplus, p.codigo, posicao);
}

int busca(int codigo) {
  long pos;

  if (bplus_search(arvore_bplus, codigo, &pos)) {
    Produto p;
    fseek(arquivo_dados, pos, SEEK_SET)
        fread(&p, sizeof(Produto), 1, arquivo_dados);
    printf("Codigo %d\n Descricao %s\n Preco %.2f", p.codigo, p.descricao,
           p.preco);
  }

  void imprimir_produto(int codigo, long posicao) {
    Produto p;

    fseek(arquivo_dados, posicao, SEEK_SET);
    fread(&p, sizeof(Produto), 1, arquivo_dados);
    printf("Codigo: %d | Descricao: %s | Preco: %.2f\n", p.codigo, p.descricao,
           p.preco);
  }
  void lista() { bplus_traverse(arvore_bplus, imprimir_produto); }
}
int main() { return 0; }
