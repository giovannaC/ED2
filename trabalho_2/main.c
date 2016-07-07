/* TRABALHO PRATICO II - Estrutura de Dados 2
    UNESP - Ciencias da Computacao - Noturno
    Data de entraga do trabalho 11/05/2016
    Autores: Bruno Vedoveto Leandro            RA: 141152869
             Giovanna Cazelato Pires           RA: 141151171
             Wesley Otto Garcia Utsunomiya     RA: 141152346
             Jonathan Henrique de Oliveira     RA: 141152206

*/

#include "stdio.h"
#include "stdlib.h"
#include "main.h"

void menu();
void opcao(int);

int main() {
  char op;

  do {
    limpa_tela();
    menu();
    op = le_option("");
    opcao(op);
  } while(op != '0');

  return 0;
}

void opcao(int op) {
  limpa_tela();

  switch(op){
    case '1': inserir(); break;
    case '2': listar(); break;
    case '3': buscar(); break;
    case '4': remover(); break;
    case '0': printf("bye!"); break;
    default: printf("Opcao invalida!\n");
 }
}

void menu() {
  printf("\n|-----------------|\n");
  printf("|1- Inserir       |\n");
  printf("|2- Listar        |\n");
  printf("|3- Buscar        |\n");
  printf("|4- Remover       |\n");
  printf("|-----------------|\n");
  printf("|0- Sair          |\n");
  printf("|-----------------|\n\n");
}
