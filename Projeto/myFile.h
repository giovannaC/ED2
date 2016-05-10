#include "string.h"

typedef struct post{
	char text[150];
	char user[50];
	char coordinates[20];
	int like_count;
	char language[30];
	int share_count;
	int views_count;
} post;

void inserir(FILE* file){
	post lpost;
	printf("\n\n");

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

	fwrite(&lpost, sizeof(post), 1, file);
}
// 3)
void listar(FILE* file){
	post lpost;
	fseek(file, 0, 0);

	int RRN = 0;
	while(fread(&lpost, sizeof(post), 1, file) > 0){
		printf("***** Registro %d *****\n", RRN);
		printf("Texto: %s\n", lpost.text);
		printf("Usuario: %s\n", lpost.user);
		printf("Coordenadas: %s\n", lpost.coordinates);
		printf("Likes: %d\n", lpost.like_count);
		printf("Linguagem: %s\n", lpost.language);
		printf("Compartilhamentos: %d\n", lpost.share_count);
		printf("Views: %d\n", lpost.views_count);

		printf("\n");

		RRN++;
	}
}
// 5)
void buscarUser(FILE* file){
	post lpost;
	char find[50];

	fseek(file, 0 , 0);

	fflush(stdin);
	printf("\n\nInsira o usuario para buscar\n");
	gets(&find);

	int achou = 0;
	int RRN = 0;
	while(fread(&lpost, sizeof(post), 1, file) > 0){
		if (strcmp(lpost.user, find) == 0){
		   achou = 1;
		   break;
	    }

	    RRN++;
	}

	if(achou){
	    printf("\n***** Registro %d *****\n", RRN);
		printf("Texto: %s\n", lpost.text);
		printf("Usuario: %s\n", lpost.user);
		printf("Coordenadas: %s\n", lpost.coordinates);
		printf("Likes: %d\n", lpost.like_count);
		printf("Linguagem: %s\n", lpost.language);
		printf("Compartilhamentos: %d\n", lpost.share_count);
		printf("Views: %d\n", lpost.views_count);
	}
	else
	    printf("\nRegistro nao encontrado\n");
}
// 4)
void buscarRRN(FILE* file){
	post lpost;
	int find=-1;

	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);

	fseek(file, find * sizeof(post), 0);

	if(fread(&lpost, sizeof(post), 1, file) > 0){
	    printf("\n***** Registro %d *****\n", find);
		printf("Texto: %s\n", lpost.text);
		printf("Usuario: %s\n", lpost.user);
		printf("Coordenadas: %s\n", lpost.coordinates);
		printf("Likes: %d\n", lpost.like_count);
		printf("Linguagem: %s\n", lpost.language);
		printf("Compartilhamentos: %d\n", lpost.share_count);
		printf("Views: %d\n", lpost.views_count);
	}
	else
	    printf("\nRegistro nao encontrado\n");
}
