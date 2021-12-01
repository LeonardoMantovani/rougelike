#include "step2.h"

char **generaMappa(int dim) {
  char **mappa = calloc(dim, sizeof(char *));
  int **tracce = calloc(dim, sizeof(int *));
  int r, c;

  // genera la mappa con solo muri
  for (r=0; r<dim; r++) {
    mappa[r] = calloc(dim, sizeof(char));
    for (c=0; c<dim; c++) {
      mappa[r][c] = '#';
    }
  }

  // genera la mappa delle tracce (vuota)
  for (r=0; r<dim; r++) {
    tracce[r] = calloc(dim, sizeof(int));
    for (c=0; c<dim; c++) {
      tracce[r][c] = 0;
    }
  }

  // posizionati nella cella (1, 1)
  r = 1;
  c = 1;
  mappa[r][c] = ' ';
  tracce[r][c] = 1;

  // scava un percorso casuale tra i muri della mappa
  scavaPercorso(mappa, tracce, dim, r, c);

  // aggiungi giocatore e uscita
  aggiungiGU(mappa, tracce, dim);

  return mappa;
}

void scavaPercorso (char **mappa, int **tracce, int dim, int x, int y) {
  int ripeti, direz, falliti[4] = {0, 0, 0, 0};

  do {
    // scelgo una direzione casuale
    direz = rand() % 4;

    // controllo se è la direz è impossibile
    switch (direz) {
      case 0:
        if (y-2 <= 0 || tracce[x][y-2] == 1)
          falliti[0] = 1;
        break;
      case 1:
        if (x-2 <= 0 || tracce[x-2][y] == 1)
          falliti[1] = 1;
        break;
      case 2:
        if (y+2 >= dim || tracce[x][y+2] == 1)
          falliti[2] = 1;
        break;
      case 3:
        if (x+2 >= dim || tracce[x+2][y] == 1)
          falliti[3] = 1;
        break;
    }

    // imposto la flag 'ripeti' se la direzione scelta non andava bene
    if (falliti[direz] == 1)
      ripeti = 1;
    else
      ripeti = 0;

  } while(ripeti == 1 && ceSperanza(falliti));

  // se il do-while è terminato perché c'è una direzione valida, scava in quella direzione
  if (ripeti == 0) {
    switch (direz) {
      case 0:
        mappa[x][y-1] = ' ';
        mappa[x][y-2] = ' ';
        tracce[x][y-1] = 1;
        tracce[x][y-2] = 1;
        scavaPercorso(mappa, tracce, dim, x, y-2);
        break;
      case 1:
        mappa[x-1][y] = ' ';
        mappa[x-2][y] = ' ';
        tracce[x-1][y] = 1;
        tracce[x-2][y] = 1;
        scavaPercorso(mappa, tracce, dim, x-2, y);
        break;
      case 2:
        mappa[x][y+1] = ' ';
        mappa[x][y+2] = ' ';
        tracce[x][y+1] = 1;
        tracce[x][y+2] = 1;
        scavaPercorso(mappa, tracce, dim, x, y+2);
        break;
      case 3:
        mappa[x+1][y] = ' ';
        mappa[x+2][y] = ' ';
        tracce[x+1][y] = 1;
        tracce[x+2][y] = 1;
        scavaPercorso(mappa, tracce, dim, x+2, y);
        break;
    }
  }
}

// ritorna 1 se almeno una delle 4 direzioni è ancora da provare. 0 se non c'è speranza
int ceSperanza(int falliti[4]) {
  int i;
  for (i=0; i<4; i++) {
    if (falliti[i] == 0)
      return 1;
  }
  return 0;
}

// aggiunge alla mappa passata il giocatore e l'uscita in una posizione casuale
//TODO: secondo me non ha senso metterli in posizione casuale
void aggiungiGU(char **mappa, int **tracce, int dim) {
  int x[2], y[2], libero, i;

  for (i=0; i<2; i++) {
    do {
      x[i] = rand() % dim;
      y[i] = rand() % dim;

      if (tracce[x[i]][y[i]] == 1) {
        libero = 1;
        tracce[x[i]][y[i]] = 0;
      }
      else
        libero = 0;
    } while (libero == 0);
  }

  mappa[x[0]][y[0]] = 'G';
  mappa[x[1]][y[1]] = 'U';
}
