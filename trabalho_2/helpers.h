#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int __fpurge(FILE*);

FILE* arquivo(const char *nome) {
  FILE* file = fopen(nome, "rb+");

  if(!file)
     file = fopen(nome, "wb+");

  return file;
}

void limpa_buffer(FILE *stream) {
  fflush(stream);
  __fpurge(stream);
}

char* le_texto(const char *titulo) {
  char buffer[255];
  char *saida;

  limpa_buffer(stdin);
  printf("%s\n", titulo);
  fgets(buffer, 255, stdin);
  int len = strlen(buffer) - 1;
  if (len > 0) {
    if (buffer[len] == '\n') { buffer[len] = '\0'; }
  }
  saida = (char*) malloc(strlen(buffer) + 1);
  strcpy(saida, buffer);

  return saida;
}

char* le_texto_arquivo(FILE *file) {
  char buffer[255];
  int cont = -1;
  int retorno;
  char *saida = NULL;

  limpa_buffer(file);

  do {
    cont ++;
    retorno = fread(&buffer[cont], sizeof(char), 1, file);
  } while(retorno !=EOF && buffer[cont] != '|' && cont <= 255);

  buffer[cont] = '\0';
  saida = (char*) malloc(strlen(buffer) + 1);
  strcpy(saida, buffer);
  return saida;
}

int le_int(const char *titulo) {
  int buffer;

  printf("%s\n", titulo);
  scanf("%d", &buffer);

  return buffer;
}

int le_long(const char *titulo) {
  long buffer;

  printf("%s\n", titulo);
  scanf("%ld", &buffer);

  return buffer;
}

void limpa_tela() {
  system("clear");
  system("cls");
}

void linha() {
  printf("--------------------------------------------------------------------");
}

void titulo(const char *titulo) {
  limpa_tela();
  linha();
  printf("\n%s\n", titulo);
  linha();
  printf("\n");
}
