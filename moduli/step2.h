#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **generaMappa(int dim);
void scavaPercorso(char **mappa, int **tracce, int dim, int x, int y);
int ceSperanza(int falliti[4]);
void aggiungiGU(char **mappa, int **tracce, int dim);
