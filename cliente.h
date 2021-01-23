
#include "LDDE.h"
/// ESTRUTURAS IMPORTANTES

typedef struct { // struct que recebe o texto
   int coluna;
   char palavra[50];
} info;


/// FUNCOES

int modificaLista (LDDE *p, char regpalavra[], int regcoluna, int difColuna, int posLog);


/// IMPLEMENTACAO DAS FUNCOES

int modificaLista (LDDE *p, char regpalavra[], int regcoluna, int difColuna, int posLog){
    info reg2;
    regcoluna -= difColuna;
    reg2.coluna = regcoluna;
    memcpy (reg2.palavra, regpalavra, sizeof (reg2.palavra));
    memcpy (p->refMovel->dados, &reg2, p->tamInfo);
    return SUCESSO;
}
