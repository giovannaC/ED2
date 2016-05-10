#include "stdio.h"
#include "myFile.h"


//Função para printar interface
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


//Utiliza função para inserir
//Pergunta ao usuário se deseja continuar inserindo após cada iteração
void inserirVarios(FILE* file){
	int op = 0;
	do{
		inserir(file);
		
		fflush(stdin);
		printf("\n\nDeseja continuar inserindo? 1- Sim / 2- Nao\n");
		scanf("%d", &op);
	}while(op != 2);
}

int main(){
	int op = 0;
	
	FILE* file = fopen("file.dat", "r+");
	
	if(!file)
	   file = fopen("file.dat", "w+");
	
	while(1){
	    printInterface();
	    scanf("%d", &op);
	
	    //Lê opção do usuário
	    switch(op){
	        case 1: inserirVarios(file);
		            break;
		
		    case 2: listar(file);
		            break;
		        
		    case 3: buscarRRN(file);
		            break;
		            
		    case 4: buscarUser(file);
		            break;
		            
		    case 5: remover(file);
		            break;
		        
		    case 0: exit(0);
		        
	   	    default: printf("Opcao invalida!\n");
	   }	
    }
	
	getch();

	close(file);
}
