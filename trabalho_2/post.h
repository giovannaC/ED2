#include "helpers.h"

//Registro que guarda informacoes do post
typedef struct Post{
  long views_count;
  int like_count;
  int share_count;
	char *user;
	char *text;
	char *coordinates;
	char *language;
} Post;

long post_size(Post);

Post novo_post() {
  Post post;
  titulo("Inserindo post");
  post.user = le_texto("USER");
  post.text = le_texto("\nTEXT");
  post.coordinates = le_texto("\nCOORDINATES");
  post.like_count = le_int("\nLIKE_COUNT");
  post.language = le_texto("\nLANGUAGE");
  post.share_count = le_int("\nSHARE_COUNT");
  post.views_count = le_long("\nVIEWS_COUNT");

  return post;
};

void grava_post(Post post, FILE *file) {
  int size = post_size(post);
  char separator = '|';

  fwrite(&size, sizeof(long), 1, file);
  fwrite(&(post.views_count), sizeof(long), 1, file);
  fwrite(&(post.like_count), sizeof(int), 1, file);
  fwrite(&(post.share_count), sizeof(int), 1, file);
  fwrite(post.user, strlen(post.user), 1, file);
  fwrite(&separator, sizeof(char), 1, file);
  fwrite(post.text, strlen(post.text), 1, file);
  fwrite(&separator, sizeof(char), 1, file);
  fwrite(post.coordinates, sizeof(post.coordinates), 1, file);
  fwrite(&separator, sizeof(char), 1, file);
  fwrite(post.language, strlen(post.language), 1, file);
}

long post_size(Post post) {
  long size = 0;

  size += sizeof(long) + 3 * sizeof(char);
  size += sizeof(post.views_count);
  size += sizeof(post.like_count);
  size += sizeof(post.share_count);
  size += strlen(post.user);
  size += strlen(post.text);
  size += strlen(post.coordinates);
  size += strlen(post.language);

  return size;
}

void imprime_post(Post post) {
  titulo("POST");
  printf("TEXT:\t\t %s\n", post.text);
  printf("USER:\t\t %s\n", post.user);
  printf("COORDINATES:\t %s\n", post.coordinates);
  printf("LIKE_COUNT:\t %d\n", post.like_count);
  printf("LANGUAGE:\t %s\n", post.language);
  printf("SHARE_COUNT:\t %d\n", post.share_count);
  printf("VIEWS_COUNT:\t %ld\n", post.views_count);
}
