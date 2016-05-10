#include "string.h"

//Registro que guarda informações do post
typedef struct post{
	char user[50];
	char text[150];
	char coordinates[20];
	int like_count;
	char language[30];
	int share_count;
	int views_count;
} post;

//Função responsável de inserir os dados de post no arquivo
void inserir(FILE* file){
	post lpost;
	printf("\n\n");

    //Realiza leitura de dados do post a partir do teclado
	fflush(stdin);
	printf("Insira o texto do post\n");
	gets(&lpost.text);

	fflush(stdin);
	printf("Insira o nome de usuario do post\n");
	gets(&lpost.user);

	fflush(stdin);
	printf("Insira as coordenadas do post\n");
	gets(&lpost.coordinates);

	fflush(stdin);
	printf("Insira a contagem de like do post\n");
	scanf("%d", &lpost.like_count);

	fflush(stdin);
	printf("Insira a linguagem do post\n");
	gets(&lpost.language);

	fflush(stdin);
	printf("Insira a contagem de compartilhamentos do post\n");
	scanf("%d", &lpost.share_count);

	fflush(stdin);
	printf("Insira a contagem de visualizacoes do post\n");
	scanf("%d", &lpost.views_count);

    //Escreve registro no arquivo
	fwrite(&lpost, sizeof(post), 1, file);
}
// 3)
void listar(FILE* file){
	post lpost;
	fseek(file, 0, 0);

    //Variável para contagem do RRN
	int RRN = 0;
	
	//Enquanto houver dados no arquivo, ler para o registro
	while(fread(&lpost, sizeof(post), 1, file) > 0){
		
		if(strcmp(lpost.user, "*") != 0){ //Se não está removido
			//Imprime registro na tela
			printf("***** Registro %d *****\n", RRN);
			printPost(lpost);
	
			printf("\n");
	    }

		RRN++;
	}
}
// 5)
void buscarUser(FILE* file){
	post lpost;
	char find[50];

	fseek(file, 0 , 0);

    //Realiza leitura de qual usuario buscar a partir do teclado
	fflush(stdin);
	printf("\n\nInsira o usuario para buscar\n");
	gets(&find);

    //Variável lógica para indicar se encontrou o usuário buscado
	int achou = 0;
	
	//Variável para contagem do RRN
	int RRN = 0;
	
	//Laço nos dados do arquivo
	while(fread(&lpost, sizeof(post), 1, file) > 0){
		
		//Se o usuário que está sendo lido é igual ao informado, muda valor da variável para 1 e sai do laço
		if (strcmp(lpost.user, find) == 0){
		   achou = 1;
		   break;
	    }

	    RRN++;
	}

    //Se a busca encontrou usuário, imprime. Senão, mostra mensagem de que não encontrou
	if(achou){
		if(strcmp(lpost.user, "*") != 0){ //Se não está removido
		    printf("\n***** Registro %d *****\n", RRN);
			printPost(lpost);
	    }
	}
	else
	    printf("\nRegistro nao encontrado\n");
}
// 4)
void buscarRRN(FILE* file){
	post lpost;
	
	//Variável para ler o RRN a partir do teclado
	int find=-1;
    
    //Realiza leitura do RNN para buscar a partir do teclado
	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);


    //Usa o RRN para dar um seek no arquivo e localizar o registro em questão
	fseek(file, find * sizeof(post), 0);
	
	//Se a busca encontrou usuário, imprime. Senão, mostra mensagem de que não encontrou
	if(fread(&lpost, sizeof(post), 1, file) > 0){
		if(strcmp(lpost.user, "*") != 0){ //Se não está removido
		    printf("\n***** Registro %d *****\n", find);
			printPost(lpost);
	    }
	}
	else
	    printf("\nRegistro nao encontrado\n");
}

void remover(FILE* file){
	post lpost;
	
	//Variável para ler o RRN a partir do teclado
	int find=-1;
    
    //Realiza leitura do RNN para buscar a partir do teclado
	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);


    //Usa o RRN para dar um seek no arquivo e localizar o registro em questão
	fseek(file, find * sizeof(post), 0);
	
	//Se a busca encontrou usuário, remove. Senão, mostra mensagem de que não encontrou
	if(fread(&lpost, sizeof(post), 1, file) > 0){
		//Marca usuário com simbolo especial para informar remoção
	    strcpy(lpost.user, "*");
	    fseek(file, find * sizeof(post), 0);
	    
	    //Escreve registro no arquivo
	    fwrite(&lpost, sizeof(post), 1, file);
	    
	    printf("\nRegistro removido com sucesso\n");
	}
	else
	    printf("\nRegistro nao encontrado\n");	
}

void printPost(post lpost){
	printf("Texto: %s\n", lpost.text);
	printf("Usuario: %s\n", lpost.user);
	printf("Coordenadas: %s\n", lpost.coordinates);
	printf("Likes: %d\n", lpost.like_count);
	printf("Linguagem: %s\n", lpost.language);
	printf("Compartilhamentos: %d\n", lpost.share_count);
	printf("Views: %d\n", lpost.views_count);
}
