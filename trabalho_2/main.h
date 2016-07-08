#include "post.h"

void inserir();
void listar();
void listar_individual();
void listar_todos(const char*);

void inserir() {
  Post post;

  char op = 1;

  do {
    post = post_novo();
    post_gravar(post);

    post_imprimir(post, 0);
    linha();
    op = le_opcao("CONTINUAR, 0 - MENU");
  } while (op != '0');
}

void listar() {
  int sair = 0;

  do {
    sair = 0;
    limpa_tela();
    printf("|-----------------|\n");
    printf("|1- INDIVIDUAL    |\n");
    printf("|2- TODOS         |\n");
    printf("|3- POR USUARIO   |\n");
    printf("|-----------------|\n");
    printf("|0- MENU          |\n");
    printf("|-----------------|\n\n");

    switch(le_opcao("")){
      case '1': listar_individual(); break;
      case '2': listar_todos(""); break;
      case '3': {
        limpa_tela();
        listar_todos(le_texto("USUARIO"));
        break;
      }
      case '0': sair = 1; break;
    }
  } while(sair !=1);
}

void listar_individual() {
  char op = 1;
  FILE *file = arquivo("main.dat");
  Post *post;
  int indice = 1;

  do {
    post = post_ler(file);
    limpa_tela();
    if (post != NULL) {
      post_imprimir(*post, indice);
      linha();
      op = le_opcao("PROXIMO, 0 - MENU");
    } else {
      titulo("FIM DO ARQUIVO");
      le_opcao("");
    }

    indice++;
  } while (post != NULL && op != '0');

  fclose(file);
}

void listar_todos(const char *usuario) {
  FILE *file = arquivo("main.dat");
  Post *post;
  int indice = 1;

  limpa_tela();
  do {
    post = post_ler(file);
    if (post != NULL) {
      if (strlen(usuario) == 0 || strcmp(usuario, (*post).user) == 0) {
        post_imprimir(*post, indice);
      }
    } else {
      titulo("FIM DO ARQUIVO");
    }

    indice++;
  } while (post != NULL);

  le_opcao("");
  fclose(file);
}

void buscar() {
  printf("buscar\n");
}

void remover() {
  printf("remover\n");
}
