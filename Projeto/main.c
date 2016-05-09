#include "stdio.h"
#include "myFile.h"

void printInterface(){
	printf("|--------------------------|\n");
	printf("|1- Inserir novo registro  |\n");
	printf("|2- Listar registros       |\n");
	printf("|--------------------------|\n");
	printf("|0- Sair                   |\n");
	printf("|--------------------------|\n");
}

int main(){
	int op = 0;
	
	FILE* file = fopen("file.dat", "a+");
	
	printInterface();
	scanf("%d", &op);
	
	switch(op){
		case 1: inserir(file);
		        break;
		
		case 2: listar(file);
		        break;
		        
		case 0: exit(0);
		        
		default: printf("Opcao invalida!\n");
	}	
	
	getch();
	close(file);
}
