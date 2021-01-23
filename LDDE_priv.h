

/// DEFINE'S

# define FRACASSO 0
# define SUCESSO 1


/// ESTRUTURAS BASICAS

// No da lista

struct NoLDDE {
   struct NoLDDE *prox;
   struct NoLDDE *ant;
   void *dados;
};
typedef struct NoLDDE noLDDE;


// Descritor da lista

struct descritorLDDE {
   int tamInfo;
   int tamLista;
   int posLogAtual;
   noLDDE *refMovel;
};
typedef struct descritorLDDE LDDE;
