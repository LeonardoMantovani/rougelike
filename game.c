#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "moduli/step1.h"
#include "moduli/step2.h"

typedef char stringa[100];

int main() {
  int genera;
  char **mappa;
  int dimMappa = 0;

  // inizializza il generatore di numeri casuali
  srand(time(NULL));

  // chiedi con che mappa vuole giocare
  printf("Vuoi caricare una mappa esistente (0) o generarne una nuova (1)? ");
  do {
    scanf("%d", &genera);
    if (genera != 0 && genera != 1)
      printf("Input non valido! Inserire 0 per caricare una mappa esistente o 1 per generarne una nuova: ");
  } while (genera != 0 && genera != 1);

  // chiama le funzioni per aprire/generare la mappa
  if (genera == 0) {
    mappa = apriMappa(&dimMappa);
    if (mappa == NULL) {
      printf("Impossibile aprire la mappa\n");
      return 1;
    }
  }
  else {
    printf("Inserisci la dimensione della mappa da generare: ");
    scanf("%d%*c", &dimMappa);
    mappa = generaMappa(dimMappa);
  }

  // stampa la mappa caricata/generata
  stampaMappa(mappa, dimMappa);

  return 0;
}
