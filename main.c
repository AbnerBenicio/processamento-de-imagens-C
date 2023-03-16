#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int w, h;
  unsigned char **pixels;
} Imagem;

void abreImg(Imagem *p) {
  FILE *arq;
  int i, j;

  char line[1024];

  arq = fopen("C:/Users/Public/trabalho-ed-Abner-ErickKomati/coins.ascii.pgm", "rt");
  fscanf(arq, "%[^\n]\n", line);
  fscanf(arq, "%d %d\n", &p->w, &p->h);
  fscanf(arq, "%[^\n]\n", line);
  p->pixels = (unsigned char **)malloc(p->h * sizeof(unsigned char *));
  for (int i = 0; i < p->h; i++) {
    p->pixels[i] = (unsigned char *)malloc(p->w * sizeof(unsigned char));
    for (int j = 0; j < p->w; j++) {
      fscanf(arq, "%hhu", &p->pixels[i][j]);
    }
  }
}

unsigned char **negativo(Imagem *p) {
  unsigned char **matriz;

  matriz = (unsigned char **)malloc(p->h * sizeof(unsigned char *));
  for (int i = 0; i < p->h; i++) {
    matriz[i] = (unsigned char *)malloc(p->w * sizeof(unsigned char));
    for (int j = 0; j < p->w; j++) {
      matriz[i][j] = p->pixels[i][j];
    }
  }

  for (int i = 0; i < p->h; i++) {
    for (int j = 0; j < p->w; j++) {
      matriz[i][j] = 255 - p->pixels[i][j];
    }
  }

  return matriz;
}

unsigned char **inverte(Imagem *p) {
  unsigned char **matriz;

  matriz = (unsigned char **)malloc(p->h * sizeof(unsigned char *));
  for (int i = 0; i < p->h; i++) {
    matriz[i] = (unsigned char *)malloc(p->w * sizeof(unsigned char));
    for (int j = 0; j < p->w; j++) {
      matriz[i][j] = p->pixels[i][j];
    }
  }

  for (int i = 0; i < p->h; i++) {
    for (int j = p->w - 1; j >= 0; j--) {
      matriz[i][j] = p->pixels[i][p->w - 1 - j];
    }
  }

  return matriz;
}

unsigned char **blur(Imagem *p) {
  unsigned char **matriz;
  int trunc;
  matriz = (unsigned char **)malloc(p->h * sizeof(unsigned char *));
  for (int i = 0; i < p->h; i++) {
    matriz[i] = (unsigned char *)malloc(p->w * sizeof(unsigned char));
    for (int j = 0; j < p->w; j++) {
      matriz[i][j] = p->pixels[i][j];
    }
  }

  for (int i = 0; i < p->h; i++) {
    for (int j = 0; j < p->w; j++) {
      // Se estiver na primeira linha
      if (i == 0) {
        // Se estiver na primeira coluna
        if (j == 0) {
          trunc = (p->pixels[i][j] + p->pixels[i][j + 1] +
                   p->pixels[i + 1][j + 1] + p->pixels[i + 1][j]) /
                  4;
          // Se estiver na última coluna
        } else if (j == p->w - 1) {
          trunc = (p->pixels[i][j] + p->pixels[i][j - 1] +
                   p->pixels[i + 1][j - 1] + p->pixels[i + 1][j]) /
                  4;
          // Se estiver em qualquer coluna
        } else {
          trunc = (p->pixels[i][j] + p->pixels[i][j - 1] + p->pixels[i][j + 1] +
                   p->pixels[i + 1][j - 1] + p->pixels[i + 1][j] +
                   p->pixels[i + 1][j + 1]) /
                  6;
        }
        // Se estiver na última linha
      } else if (i == p->h - 1) {
        if (j == 0) {
          trunc = (p->pixels[i][j] + p->pixels[i][j + 1] +
                   p->pixels[i - 1][j + 1] + p->pixels[i - 1][j]) /
                  4;
        } else if (j == p->w - 1) {
          trunc = (p->pixels[i][j] + p->pixels[i][j - 1] +
                   p->pixels[i - 1][j - 1] + p->pixels[i - 1][j]) /
                  4;
        } else {
          trunc = (p->pixels[i][j] + p->pixels[i][j - 1] + p->pixels[i][j + 1] +
                   p->pixels[i - 1][j - 1] + p->pixels[i - 1][j] +
                   p->pixels[i - 1][j + 1]) /
                  6;
        }
        // Se estiver em qualquer outra linha
      } else {
        if (j == 0) {
          trunc = (p->pixels[i][j] + p->pixels[i][j + 1] +
                   p->pixels[i + 1][j + 1] + p->pixels[i + 1][j] +
                   p->pixels[i - 1][j] + p->pixels[i - 1][j + 1]) /
                  6;
        } else if (j == p->w - 1) {
          trunc = (p->pixels[i][j] + p->pixels[i][j - 1] +
                   p->pixels[i + 1][j - 1] + p->pixels[i + 1][j] +
                   p->pixels[i - 1][j] + p->pixels[i - 1][j - 1]) /
                  6;
        } else {
          trunc = (p->pixels[i][j] + p->pixels[i][j - 1] + p->pixels[i][j + 1] +
                   p->pixels[i - 1][j - 1] + p->pixels[i - 1][j] +
                   p->pixels[i - 1][j + 1] + p->pixels[i + 1][j] +
                   p->pixels[i + 1][j - 1] + p->pixels[i + 1][j + 1]) /
                  9;
        }
      }

      matriz[i][j] = trunc;
    }
  }
  return matriz;
}

unsigned char **bright(Imagem *p) {
  unsigned char max, **matriz;
  max = 0;
  matriz = (unsigned char **)malloc(p->h * sizeof(unsigned char *));
  for (int i = 0; i < p->h; i++) {
    matriz[i] = (unsigned char *)malloc(p->w * sizeof(unsigned char));
    for (int j = 0; j < p->w; j++) {
      matriz[i][j] = p->pixels[i][j];
    }
  }

  for (int i = 0; i < p->h; i++) {
    for (int j = 0; j < p->w; j++) {
      max = 24;
      // Se estiver na primeira linha
      if (i == 0) {
        // Se estiver na primeira coluna
        if (j == 0) {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j + 1] > max) {
            max = p->pixels[i][j + 1];
          }
          if (p->pixels[i + 1][j + 1] > max) {
            max = p->pixels[i + 1][j + 1];
          }
          if (p->pixels[i + 1][j] > max) {
            max = p->pixels[i + 1][j];
          }

          // Se estiver na última coluna
        } else if (j == p->w - 1) {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j - 1] > max) {
            max = p->pixels[i][j - 1];
          }
          if (p->pixels[i + 1][j - 1] > max) {
            max = p->pixels[i + 1][j - 1];
          }
          if (p->pixels[i + 1][j] > max) {
            max = p->pixels[i + 1][j];
          }

          // Se estiver em qualquer coluna
        } else {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j - 1] > max) {
            max = p->pixels[i][j - 1];
          }
          if (p->pixels[i][j + 1] > max) {
            max = p->pixels[i][j + 1];
          }
          if (p->pixels[i + 1][j - 1] > max) {
            max = p->pixels[i + 1][j - 1];
          }
          if (p->pixels[i + 1][j] > max) {
            max = p->pixels[i + 1][j];
          }
          if (p->pixels[i + 1][j + 1] > max) {
            max = p->pixels[i + 1][j + 1];
          }
        }
        // Se estiver na última linha
      } else if (i == p->h - 1) {
        if (j == 0) {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j + 1] > max) {
            max = p->pixels[i][j + 1];
          }
          if (p->pixels[i - 1][j + 1] > max) {
            max = p->pixels[i - 1][j + 1];
          }
          if (p->pixels[i - 1][j] > max) {
            max = p->pixels[i - 1][j];
          }

        } else if (j == p->w - 1) {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j - 1] > max) {
            max = p->pixels[i][j - 1];
          }
          if (p->pixels[i - 1][j - 1] > max) {
            max = p->pixels[i - 1][j - 1];
          }
          if (p->pixels[i - 1][j] > max) {
            max = p->pixels[i - 1][j];
          }

        } else {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j - 1] > max) {
            max = p->pixels[i][j - 1];
          }
          if (p->pixels[i][j + 1] > max) {
            max = p->pixels[i][j + 1];
          }
          if (p->pixels[i - 1][j - 1] > max) {
            max = p->pixels[i - 1][j - 1];
          }
          if (p->pixels[i - 1][j] > max) {
            max = p->pixels[i - 1][j];
          }
          if (p->pixels[i - 1][j + 1] > max) {
            max = p->pixels[i - 1][j + 1];
          }
        }
        // Se estiver em qualquer outra linha
      } else {
        if (j == 0) {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i + 1][j + 1] > max) {
            max = p->pixels[i + 1][j + 1];
          }
          if (p->pixels[i][j + 1] > max) {
            max = p->pixels[i][j + 1];
          }
          if (p->pixels[i + 1][j] > max) {
            max = p->pixels[i + 1][j];
          }
          if (p->pixels[i - 1][j] > max) {
            max = p->pixels[i - 1][j];
          }
          if (p->pixels[i - 1][j + 1] > max) {
            max = p->pixels[i - 1][j + 1];
          }

        } else if (j == p->w - 1) {

          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j - 1] > max) {
            max = p->pixels[i][j - 1];
          }
          if (p->pixels[i + 1][j - 1] > max) {
            max = p->pixels[i + 1][j - 1];
          }
          if (p->pixels[i + 1][j] > max) {
            max = p->pixels[i + 1][j];
          }
          if (p->pixels[i - 1][j] > max) {
            max = p->pixels[i - 1][j];
          }
          if (p->pixels[i - 1][j - 1] > max) {
            max = p->pixels[i - 1][j - 1];
          }

        } else {
          if (p->pixels[i][j] > max) {
            max = p->pixels[i][j];
          }
          if (p->pixels[i][j - 1] > max) {
            max = p->pixels[i][j - 1];
          }
          if (p->pixels[i][j + 1] > max) {
            max = p->pixels[i][j + 1];
          }
          if (p->pixels[i - 1][j - 1] > max) {
            max = p->pixels[i - 1][j - 1];
          }
          if (p->pixels[i - 1][j] > max) {
            max = p->pixels[i - 1][j];
          }
          if (p->pixels[i - 1][j + 1] > max) {
            max = p->pixels[i - 1][j + 1];
          }
          if (p->pixels[i + 1][j] > max) {
            max = p->pixels[i + 1][j];
          }
          if (p->pixels[i + 1][j - 1] > max) {
            max = p->pixels[i + 1][j - 1];
          }
          if (p->pixels[i + 1][j + 1] > max) {
            max = p->pixels[i + 1][j + 1];
          }
        }
      }
      matriz[i][j] = max;
    }
  }
  return matriz;
}

int main(void) {
  Imagem img;
  FILE *saida;
  unsigned char **copia;

  // Colocar menu

  // Criar função de input solicitando caminho

  // Ifs do menu

  // If 1
  abreImg(&img);
  // If 2
  copia = inverte(&img);
  // If 3
  copia = blur(&img);
  // If 4
  copia = bright(&img);
  // If 5
  copia = negativo(&img);

  // criar função para salvar img
  saida = fopen("saida.pgm", "wt");
  fprintf(saida, "%s\n", "P2");
  fprintf(saida, "%d %d\n", img.w, img.h);
  fprintf(saida, "%d\n", 255);
  for (int i = 0; i < img.h; i++) {
    for (int j = 0; j < img.w; j++) {
      fprintf(saida, "%u ", copia[i][j]);
    }
  }

  return 0;
}