#include <stdio.h>


int main(void) {
  FILE *arq;
  FILE *out;
  int linha, coluna, max_gray, i, j;

  unsigned char pixel;

  arq = fopen("C:/Users/abner/OneDrive/Documentos/trabalho-ed-Abner-ErickKomati/coins.ascii.pgm", "rt");
  if (arq == NULL) {
    printf("NAO FOI");
  }

  out = fopen("copia.pgm", "wt");

  char line[1024];
  fscanf(arq, "%[^\n]\n", line);
  fprintf(out, "%s\n", line);
  
  fscanf(arq, "%[^\n]\n", line);
  fprintf(out, "%s\n", line);

  fscanf(arq, "%d %d", &coluna, &linha);
  fprintf(out, "%d %d\n", coluna, linha);

  fscanf(arq, "%d", &max_gray);
  fprintf(out, "%d\n", max_gray);

  int imagem[linha][coluna];
  for (i = 0; i < linha; i++) {
    for (j = 0; j < coluna; j++) {
      fscanf(arq, "%hhu", &pixel);
      imagem[i][j] = pixel;
    }
  }

  for (i = 0; i < linha; i++) {
    for (j = 0; j < coluna; j++) {
      fprintf(out, "%d  ", imagem[i][j]);
    }
  }


  return 0;
}