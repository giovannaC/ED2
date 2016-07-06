#include "post.h"

void inserir() {
  Post post;
  FILE *file = arquivo("main.dat");
  int op = 1;

  do {
    post = novo_post();
    imprime_post(post);
    grava_post(post, file);
    linha();
    printf("%ld\n", post_size(post));
    op = le_int("\n1 - CONTINUAR, 0 - MENU");
  } while (op != 0);

  fclose(file);
}

void listar() {
  printf("listar\n");
}

void buscar() {
  printf("buscar\n");
}

void remover() {
  printf("remover\n");
}
