#include "string.h"

//Registro que guarda informaÃ§Ãµes do post
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

//Utiliza função para inserir
//Pergunta ao usuário se deseja continuar inserindo após cada iteração
// 2) Não há uma condição de parada de fato, mas ainda sim há uma opção de parar de adicionar arquivos.
//      Desse modo o programa fica mais fácil para o usuário.
void inserirVarios(FILE*file){
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

//Função responsável de inserir os dados de post no arquivo
// 7) Insere os registros em espaÃ§o vazio se houver.
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

    //Se existe valor excluido utiliza espaço para gravar, senão vai para fim de arquivo
    if(dispo != -1){
	    int temp = dispo;
        post auxPost;
        fseek(file, posicaoRRN(temp), 0);
        fread(&auxPost, sizeof(post), 1, file);
        atualizaDispo(file, auxPost.like_count);
	    fseek(file, posicaoRRN(temp), 0);
    }
    else{
        fseek(file, 0, 2);
	}

    //Escreve registro no arquivo
	fwrite(&lpost, sizeof(post), 1, file);
}
// 3)LÃª todos os registros no arquivo. E mostra na tela.
void listar(FILE* file){
	post lpost;
	fseek(file, posicaoRRN(0), 0);

    //Variï¿½vel para contagem do RRN
	int RRN = 0;

	//Enquanto houver dados no arquivo, ler para o registro
	while(fread(&lpost, sizeof(post), 1, file) > 0){
		if(strcmp(lpost.user, "*") != 0){
		printPost(lpost, RRN);
		}/*else{
		printf("\n--------- Registro %d deletado -------------\n\n",RRN);
		}*/

		RRN++;
	}
}
// 5)Permite a busca de posts que contem o campo user.
void buscarUser(FILE* file){
	post lpost;
	char find[50];

	fseek(file, posicaoRRN(0) , 0);

    //Realiza leitura de qual usuario buscar a partir do teclado
	fflush(stdin);
	printf("\n\nInsira o usuario para buscar\n");
	gets(&find);

    //Variável lógica para indicar se encontrou o usuï¿½rio buscado
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
	if(achou)
		printPost(lpost, RRN);
	else
	    printf("\nRegistro nao encontrado\n");
}
// 4)Permite a busca de um post dado o RRN
void buscarRRN(FILE* file){
	post lpost;

	//Variável para ler o RRN a partir do teclado
	int find=-1;

	//Realiza leitura do RNN para buscar a partir do teclado
	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);

    //Usa o RRN para dar um seek no arquivo e localizar o registro em questão
	fseek(file, posicaoRRN(find), 0);

	//Se a busca encontrou usuï¿½rio, imprime. Senï¿½o, mostra mensagem de que nï¿½o encontrou
	if(fread(&lpost, sizeof(post), 1, file) > 0)
		printPost(lpost, find);
	else
	    printf("\nRegistro nao encontrado\n");
}
// 6) Permite a remoÃ§Ã£o do registro dado o RRN
void remover(FILE* file){
	post lpost;
	fseek(file, 0, 0);

    fread(&dispo, sizeof(dispo), 1, file);
	if(dispo == -1)
		atualizaDispo(file, dispo);

	//Variável para ler o RRN a partir do teclado
	int find = -1;

    //Realiza leitura do RNN para buscar a partir do teclado
	printf("\n\nInsira o RRN para buscar\n");
	scanf("%d", &find);

    //Usa o RRN para dar um seek no arquivo e localizar o registro em questï¿½o
	fseek(file, posicaoRRN(find), 0);

	//Se a busca encontrou usuário, remove. Senão, mostra mensagem de que não encontrou
	if(fread(&lpost, sizeof(post), 1, file) > 0){
		//Marca usuï¿½rio com simbolo especial para informar remoï¿½ï¿½o
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
	return ((rrn * sizeof(post)) + sizeof(dispo));
}

//FunÃ§Ã£o para mostrar o post na tela.
void printPost(post lpost, int RRN){
	if(strcmp(lpost.user, "*") != 0){ //Se n�o est� removido
		printf("\n***** Registro %d *****\n", RRN);
		printf("Texto: %s\n", lpost.text);
		printf("Usuario: %s\n", lpost.user);
		printf("Coordenadas: %s\n", lpost.coordinates);
		printf("Likes: %d\n", lpost.like_count);
		printf("Linguagem: %s\n", lpost.language);
		printf("Compartilhamentos: %d\n", lpost.share_count);
		printf("Views: %d\n", lpost.views_count);
		printf("\n");
    }else{
        printf("\nRegistro nao encontrado\n");
    }
}
