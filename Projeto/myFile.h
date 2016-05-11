#include "string.h"

//Registro que guarda informa��es do post
typedef struct post{
	char user[50]; //Preenchido com * quando registro for excluido
	char text[150];
	char coordinates[20];
	int like_count; //Utilizado para manter a dispo se o registro estiver excluido
	char language[30];
	int share_count;
	int views_count;
} post;

int dispo = -1;

//Utiliza fun��o para inserir
//Pergunta ao usu�rio se deseja continuar inserindo ap�s cada itera��o
void inserirVarios(FILE* file){
	int op = 0;
	fseek(file, 0, 0);

	fread(&dispo, sizeof(dispo), 1, file);
	if(dispo == -1)
		atualizaDispo(file, dispo);

	do{
		inserir(file);

		fflush(stdin);
		printf("\n\nDeseja continuar inserindo? 1- Sim / 2- Nao\n");
		scanf("%d", &op);
	}while(op != 2);
}

//Fun��o respons�vel de inserir os dados de post no arquivo
void inserir(FILE* file){
	post lpost;
	printf("\n\n");

  //Realiza leitura de dados do post a partir do teclado
	fflush(stdin);
	printf("Insira o texto do post\n");
	gets(lpost.text);

	fflush(stdin);
	printf("Insira o nome de usuario do post\n");
	gets(lpost.user);

	fflush(stdin);
	printf("Insira as coordenadas do post\n");
	gets(lpost.coordinates);

	fflush(stdin);
	printf("Insira a contagem de like do post\n");
	scanf("%d", &lpost.like_count);

	fflush(stdin);
	printf("Insira a linguagem do post\n");
	gets(lpost.language);

	fflush(stdin);
	printf("Insira a contagem de compartilhamentos do post\n");
	scanf("%d", &lpost.share_count);

	fflush(stdin);
	printf("Insira a contagem de visualizacoes do post\n");
	scanf("%d", &lpost.views_count);

    //Se existe valor exclu�do utiliza espa�o para gravar, sen�o vai para fim de arquivo
    if(dispo > -1){
			 int temp = dispo;
       post auxPost;
       fread(&auxPost, sizeof(post), 1, file);
       atualizaDispo(file, auxPost.like_count);
			 fseek(file, posicaoRRN(temp), 0);
    }
    else
       fseek(file, 0, 2);

    //Escreve registro no arquivo
	fwrite(&lpost, sizeof(post), 1, file);
}
// 3)
void listar(FILE* file){
	post lpost;
	fseek(file, posicaoRRN(0), 0);

    //Vari�vel para contagem do RRN
	int RRN = 0;

	//Enquanto houver dados no arquivo, ler para o registro
	while(fread(&lpost, sizeof(post), 1, file) > 0){

	//	if(strcmp(lpost.user, "*") != 0){ //Se n�o est� removido
			//Imprime registro na tela
			printf("***** Registro %d *****\n", RRN);
			printPost(lpost);

			printf("\n");
	//  }

		RRN++;
	}
}
// 5)
void buscarUser(FILE* file){
	post lpost;
	char find[50];

	fseek(file, posicaoRRN(0) , 0);

    //Realiza leitura de qual usuario buscar a partir do teclado
	fflush(stdin);
	printf("\n\nInsira o usuario para buscar\n");
	gets(&find);

    //Vari�vel l�gica para indicar se encontrou o usu�rio buscado
	int achou = 0;

	//Vari�vel para contagem do RRN
	int RRN = 0;

	//La�o nos dados do arquivo
	while(fread(&lpost, sizeof(post), 1, file) > 0){

		//Se o usu�rio que est� sendo lido � igual ao informado, muda valor da vari�vel para 1 e sai do la�o
		if (strcmp(lpost.user, find) == 0){
		   achou = 1;
		   break;
	    }

	    RRN++;
	}

    //Se a busca encontrou usu�rio, imprime. Sen�o, mostra mensagem de que n�o encontrou
	if(achou){
		if(strcmp(lpost.user, "*") != 0){ //Se n�o est� removido
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

	//Vari�vel para ler o RRN a partir do teclado
	int find=-1;

	//Realiza leitura do RNN para buscar a partir do teclado
	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);


    //Usa o RRN para dar um seek no arquivo e localizar o registro em quest�o
	fseek(file, posicaoRRN(find), 0);

	//Se a busca encontrou usu�rio, imprime. Sen�o, mostra mensagem de que n�o encontrou
	if(fread(&lpost, sizeof(post), 1, file) > 0){
		if(strcmp(lpost.user, "*") != 0){ //Se n�o est� removido
		    printf("\n***** Registro %d *****\n", find);
			printPost(lpost);
	    }
	}
	else
	    printf("\nRegistro nao encontrado\n");
}

void remover(FILE* file){
	post lpost;

	//Vari�vel para ler o RRN a partir do teclado
	int find = -1;

    //Realiza leitura do RNN para buscar a partir do teclado
	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);


    //Usa o RRN para dar um seek no arquivo e localizar o registro em quest�o
	fseek(file, posicaoRRN(find), 0);

	//Se a busca encontrou usu�rio, remove. Sen�o, mostra mensagem de que n�o encontrou
	if(fread(&lpost, sizeof(post), 1, file) > 0){
		//Marca usu�rio com simbolo especial para informar remo��o
	    strcpy(lpost.user, "*");

	    //Armazena valor atual da dispo no registro e atualiza topo da dispo
	    lpost.like_count = dispo;
	    atualizaDispo(file, find);

	    fseek(file, posicaoRRN(find), 0);

	    //Escreve registro no arquivo
	    fwrite(&lpost, sizeof(post), 1, file);

	    printf("\nRegistro removido com sucesso\n");
	}
	else
	    printf("\nRegistro nao encontrado\n");
}

//atualiza dispo no arquivo e na variavel, ATENCAO: posiciona ponteiro no inicio do arquivo
void atualizaDispo(FILE *file, int rrn){
	dispo = rrn;
	fseek(file, 0, 0);
	fwrite(&rrn, sizeof(rrn), 1, file);
}

// posicao considerando a dispo no inicio do arquivo
int posicaoRRN(int rrn){
	return rrn * sizeof(post) + sizeof(dispo);
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
