#include <stdio.h>
#include <stdlib.h>

typedef char stringa[100];

char **apriMappa(int *dim);
char **caricaMappa(FILE *file, int dim);
void stampaMappa(char **map, int dim);
