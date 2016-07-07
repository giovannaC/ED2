#include "helpers.h"

//Registro que guarda informacoes do post
typedef struct Post{
  long views_count;
  int like_count;
  int share_count;
	char *text;
	char *user;
	char *coordinates;
	char *language;
} Post;

long post_tamanho(Post);
int post_endereco(FILE*, long);
Post* post_ler(int);
Post post_novo();

Post post_novo() {
  Post post;
  titulo("Inserindo post");
  post.text = le_texto("TEXT");
  post.user = le_texto("\nUSER");
  post.coordinates = le_texto("\nCOORDINATES");
  post.like_count = le_int("\nLIKE_COUNT");
  post.language = le_texto("\nLANGUAGE");
  post.share_count = le_int("\nSHARE_COUNT");
  post.views_count = le_long("\nVIEWS_COUNT");

  return post;
};

void post_gravar(Post post) {
  FILE *file = arquivo("main.dat");

  long tamanho = post_tamanho(post);
  post_endereco(file, tamanho);
  char separator = '|';

  fwrite(&tamanho, sizeof(long), 1, file);
  fwrite(&(post.views_count), sizeof(long), 1, file);
  fwrite(&(post.like_count), sizeof(int), 1, file);
  fwrite(&(post.share_count), sizeof(int), 1, file);
  fwrite(post.text, strlen(post.text), 1, file);
  fwrite(&separator, sizeof(char), 1, file);
  fwrite(post.user, strlen(post.user), 1, file);
  fwrite(&separator, sizeof(char), 1, file);
  fwrite(post.coordinates, strlen(post.coordinates), 1, file);
  fwrite(&separator, sizeof(char), 1, file);
  fwrite(post.language, strlen(post.language), 1, file);
  fwrite(&separator, sizeof(char), 1, file);

  fclose(file);
}

Post* post_ler(int pos) {
  FILE *file = arquivo("main.dat");
  Post *post;
  long tamanho = 0;
  long posicao = 0;
  int indice = 0;

  while (indice <= pos) {
    fseek(file, posicao, 0);
    fread(&tamanho, sizeof(long), 1, file);
    if(feof(file)){
      fclose(file);
      return NULL;
    }
    posicao = posicao + tamanho;
    indice++;
  }

  post = (Post*)malloc(sizeof(Post));
  fread(&((*post).views_count), sizeof(long), 1, file);
  fread(&((*post).like_count), sizeof(int), 1, file);
  fread(&((*post).share_count), sizeof(int), 1, file);
  (*post).text = le_texto_arquivo(file);
  (*post).user = le_texto_arquivo(file);
  (*post).coordinates = le_texto_arquivo(file);
  (*post).language = le_texto_arquivo(file);
  fclose(file);

  return post;
}

int post_endereco(FILE *file, long tamanho) {
  return fseek(file, 0, SEEK_END);
}

long post_tamanho(Post post) {
  long tamanho = 0;

  tamanho += sizeof(long) + 4 * sizeof(char);
  tamanho += sizeof(post.views_count);
  tamanho += sizeof(post.like_count);
  tamanho += sizeof(post.share_count);
  tamanho += strlen(post.user);
  tamanho += strlen(post.text);
  tamanho += strlen(post.coordinates);
  tamanho += strlen(post.language);

  return tamanho;
}

void post_imprimir(Post post) {
  titulo("POST");
  printf("TEXT:\t\t %s\n", post.text);
  printf("USER:\t\t %s\n", post.user);
  printf("COORDINATES:\t %s\n", post.coordinates);
  printf("LIKE_COUNT:\t %d\n", post.like_count);
  printf("LANGUAGE:\t %s\n", post.language);
  printf("SHARE_COUNT:\t %d\n", post.share_count);
  printf("VIEWS_COUNT:\t %ld\n", post.views_count);
}
