#include "post.h"

void inserir() {
  Post post;

  int op = 1;

  do {
    post = post_novo();
    post_gravar(post);

    post_imprimir(post);
    linha();
    op = le_int("\n1 - CONTINUAR, 0 - MENU");
  } while (op != 0);
}

void listar() {
  int op = 1;
  int indice = 0;
  Post *post;

  do {
    post = post_ler(indice);
    limpa_tela();
    if (post != NULL) {
      post_imprimir(*post);
      linha();
    } else {
      titulo("FIM DO ARQUIVO");
    }

    op = le_int("\n1 - ANTERIOR, 2 - PROXIMO 0 - MENU");
    if(op == 1 && indice > 0) {
      indice--;
    }

    if(op == 2 && post!= NULL) {
      indice++;
    }
  } while (op != 0);
}

void buscar() {
  printf("buscar\n");
}

void remover() {
  printf("remover\n");
}
