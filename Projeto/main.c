/* TRABALHO PRÁTICO I - Estrutura de Dados 2
    UNESP - Ciências da Computação - Noturno
    Data de entraga do trabalho 11/05/2016
    Autores: Bruno Vedoveto Leandro            RA:
             Giovanna Cazelato Pires           RA: 141151171
             Wesley Otto Garcia Utsunomiya     RA:
             Jonathan Henrique de Oliveira     RA:

*/

#include "stdio.h"
#include "myFile.h"
#include "stdlib.h"

//Fun��o para printar interface
void printInterface(){
	printf("|--------------------------|\n");
	printf("|1- Inserir novo registro  |\n");
	printf("|2- Listar registros       |\n");
	printf("|3- Buscar por RRN         |\n");
	printf("|4- Buscar por User        |\n");
	printf("|5- Remover registro       |\n");
	printf("|--------------------------|\n");
	printf("|0- Sair                   |\n");
	printf("|--------------------------|\n");
}

int main(){
	int op = 0;

	FILE* file = fopen("file.dat", "r+");

	if(!file)
	   file = fopen("file.dat", "w+");

    fread(&dispo, sizeof(dispo), 1, 0);

	while(1){
	    printInterface();
	    scanf("%d", &op);

	    //L� op��o do usu�rio
	    switch(op){
	        case 1: system("cls");
					inserirVarios(file);
		            break;

		    case 2: system("cls");
					listar(file);
		            break;

		    case 3: system("cls");
					buscarRRN(file);
		            break;

		    case 4: system("cls");
				    buscarUser(file);
		            break;

		    case 5: system("cls");
					remover(file);
		            break;

		    case 0: exit(0);

	   	    default: printf("Opcao invalida!\n");
	   }
    }

	getch();
	close(file);
}
