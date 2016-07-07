#include "post.h"

void inserir() {
  Post post;

  char op = 1;

  do {
    post = post_novo();
    post_gravar(post);

    post_imprimir(post);
    linha();
    op = le_option("CONTINUAR, 0 - MENU");
  } while (op != '0');
}

void listar() {
  char op = 1;
  FILE *file = arquivo("main.dat");
  Post *post;

  do {
    post = post_ler(file);
    limpa_tela();
    if (post != NULL) {
      post_imprimir(*post);
      linha();
      op = le_option("PROXIMO, 0 - MENU");
    } else {
      titulo("FIM DO ARQUIVO");
      le_option("");
    }
  } while (post != NULL && op != '0');

  fclose(file);
}

void buscar() {
  printf("buscar\n");
}

void remover() {
  printf("remover\n");
}
