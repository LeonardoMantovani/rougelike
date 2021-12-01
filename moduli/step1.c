#include "step1.h"

// ritorna una mappa caricata da un file .txt specificato dall'utente
char **apriMappa(int *dim) {
  FILE *file;
  stringa nomeFile;
  char **map;

  printf("Inserisci il nome del file contenente la mappa: ");
  scanf("%s", nomeFile);

  // apri il file con la mappa
  file = fopen(nomeFile, "r");
  if (file == NULL) {
    return NULL;
  }

  // leggi la dimensione della mappa
  fscanf(file, "%d\n", dim);

  // carica la mappa in una matrice di tipo char
  map = caricaMappa(file, *dim);

  fclose(file);
  return map;
}

char **caricaMappa(FILE *file, int dim) {
  char **map = calloc(dim, sizeof(char *));
  int r, c;

  for (r=0; r<dim; r++) {
    map[r] = calloc(dim, sizeof(char));
    for (c=0; c<dim; c++) {
      char el;
      fscanf(file, "%c ", &el);
      switch (el) {
        case '0':
          map[r][c] = ' ';
          break;
        case '1':
          map[r][c] = '#';
          break;
        case '2':
          map[r][c] = 'G';
          break;
        case '3':
          map[r][c] = 'U';
          break;
      }
    }
  }

  return map;
}

void stampaMappa(char **map, int dim) {
  int r, c;

  for (r=0; r<dim; r++) {
    for (c=0; c<dim; c++) {
      printf("%c", map[r][c]);
    }
    printf("\n");
  }
}
