
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "LDDE.h"

int cria (LDDE **pp, int sizeInfo) { // **pp eh o endereco de memoria de um ponteiro para lista

   // Declaracao de variaveis
   LDDE *ptr;

   // Instrucoes

   // Alocando memoria para o descritor da lista
   ptr = (LDDE*) malloc (1 * sizeof (LDDE));

   // Se a alocacao acima nao funcionar, retorne FRACASSO
   if (!ptr) {
       return (FRACASSO);
   }
   // Caso funcione, inicialize os campos do descritor, devolva o ponteiro para manipular a lista criada e retorne SUCESSO
   else {
       ptr->tamInfo = sizeInfo;
       ptr->tamLista = 0;
       ptr->posLogAtual = 0;
       ptr->refMovel = NULL;
       *pp = ptr;
       return (SUCESSO);
   }
}


int insereNoInicio (LDDE *p, void *novo) {

   // Declaracao de variaveis
   noLDDE *aux;

   // Instrucoes

   if (p->refMovel == NULL) { // Se a lista estiver vazia
       aux = (noLDDE*) malloc (1 * sizeof (noLDDE)); // Alocando memoria para o no
       if (!aux) {
           return (FRACASSO);
       }
       aux->dados = (void*) malloc (p->tamInfo); // Alocando memoria para a regiao de dados
       if (!aux->dados) { // Se essa alocacao falhar, desfaca o que ja foi alocado
           free (aux);
           return (FRACASSO);
       }
       aux->ant = NULL; // Aterrando o ponteiro ant do no criado
       aux->prox = NULL; // Aterrando o ponteiro prox do no criado
       memcpy (aux->dados, novo, p->tamInfo); // Copiando o conteudo apontado pelo ponteiro fornecido na funcao para a regiao de dados do no criado
       p->refMovel = aux; // O ponteiro refMovel passa a apontar para o no inserido, como solicitado
       p->posLogAtual = 1; // A posicao logica do no apontado pelo ponteiro refMovel passa a ser zero, ja que o no foi inserido no comeco da lista
       p->tamLista = 1; // Com a insercao, a lista passa a ter tamanho 1, ja que estava vazia
       return (SUCESSO);
   }
   else {
       while (p->posLogAtual != 1) { // Localizando o primeiro no da lista
       // while (p->refMovel->ant != NULL) {
           p->refMovel = p->refMovel->ant;
           p->posLogAtual--;
       }
       aux = (noLDDE*) malloc (1 * sizeof (noLDDE)); // Alocando memoria para o no que passara a ser o primeiro da lista
       if (!aux){
           return (FRACASSO);
       }
       aux->dados = (void*) malloc (p->tamInfo); // Alocando memoria para a regiao de dados
       if (!aux->dados){ // Se essa alocacao falhar, desfaca tudo o que ja foi alocado
           free (aux);
           return (FRACASSO);
       }
       aux->ant = NULL; // Aterrando o ponteiro ant do no criado
       aux->prox = p->refMovel; // O ponteiro prox do no criado apontara para quem era anteriormente o primeiro no da lista
       memcpy (aux->dados, novo, p->tamInfo); // Copiando o conteudo apontado pelo ponteiro fornecido para a regiao de dados do no criado
       p->refMovel->ant = aux; // O ponteiro ant do no que anteriormente era o primeiro deixa de ser NULL e aponta para o no recem-criado
       p->refMovel = aux; // O ponteiro refMovel passa a apontar para o no inserido, como solicitado pelo trabalho
       p->refMovel->ant = NULL; // Garantindo que o ponteiro ant do primeiro struct seja NULL
       p->posLogAtual = 1; // A posicao logica do no apontado pelo ponteiro refMovel passa a ser um, ja que o no foi inserido no comeco da lista
       p->tamLista++;
       return (SUCESSO);
   }
}


int insereNoFim (LDDE *p, void *novo) {

   // Declaracao de variaveis
   noLDDE *aux;

   // Instrucoes

   if (p->refMovel == NULL) { // Para a lista vazia, inserir no fim ou inserir no comeco a a mesma coisa
       return (insereNoInicio (p, novo));
   }
   else { // O caso eh analogo a inserir no comeco de uma lista nao-vazia
       while (p->posLogAtual < p->tamLista) {
           p->refMovel = p->refMovel->prox;
           p->posLogAtual++;
       }
       aux = (noLDDE*) malloc (1 * sizeof (noLDDE));
       if (!aux) {
           return (FRACASSO);
       }
       aux->dados = (void*) malloc (p->tamInfo); // Alocando memoria para a regiao de dados
       if (!aux->dados){ // Se essa alocacao falhar, desfaca tudo que ja foi alocado
           free (aux);
           return (FRACASSO);
       }
       aux->prox = NULL;
       aux->ant = p->refMovel;
       memcpy (aux->dados, novo, p->tamInfo);
       p->refMovel->prox = aux; 
       p->refMovel = aux;
       p->refMovel->prox = NULL; // Garantindo que o ponteiro prox do ultimo struct seja NULL
       p->posLogAtual++;
       p->tamLista++;
       return (SUCESSO);
   }
}


int insereNaPosLog (LDDE *p, void *novo, unsigned int posLog) {

   // Declaracao de variaveis
   noLDDE *aux;

   // Instrucoes

   if ((posLog < 1) || (posLog > p->tamLista+1)) { // Se a posicao logica fornecida nao for valida
       //Assim, com o p->tamLista+1 ele aceita inserir na posicao vazia mas posterior a ultima, chamando a
       //inserirNoFim;
       return (FRACASSO);
   }

   if (posLog == 1) { // Se a posicao logica fornecida for a primeira
       return (insereNoInicio (p, novo));
   }

   if (posLog == p->tamLista+1) { // Se a posicao ligica fornecida for a ultima
       return (insereNoFim (p, novo));
   }

   if (p->posLogAtual >= posLog) {
       while (p->posLogAtual >= posLog) { // Procurando o no que ficara antes do no a ser inserido
           p->refMovel = p->refMovel->ant;
           p->posLogAtual--;
       }
   }
   else if (p->posLogAtual < posLog) {
       while (p->posLogAtual < posLog) { // Procurando o no que ficara antes do no a ser inserido
           p->refMovel = p->refMovel->prox;
           p->posLogAtual++;
       }
   }

   aux = (noLDDE*) malloc (1 * sizeof (noLDDE)); // Alocando memoria para o no que sera inserido
   if (!aux) {
       return (FRACASSO);
   }
   aux->dados = (void*) malloc (p->tamInfo); // Alocando memoria para a regiao de dados
   if(!aux->dados) {
       free (aux);
       return (FRACASSO);
   }
   aux->ant = p->refMovel;
   aux->prox = p->refMovel->prox;
   memcpy (aux->dados, novo, p->tamInfo);
   p->refMovel->prox->ant = aux;
   p->refMovel->prox = aux;
   p->refMovel = aux;
   p->posLogAtual++;
   p->tamLista++;
   return (SUCESSO);
}


int tamanho (LDDE *p) {
    if (p==NULL) {
        return (FRACASSO);
    }
    return (p->tamLista);
}


int removeDoInicio(LDDE *p, void *reg) {

   // Declaracao de variaveis
   noLDDE *aux;
   int ret = FRACASSO;

   // Instrucoes

   if (p->posLogAtual == 0||p->refMovel==NULL) {
       return (ret);
   }
   else {
       while (p->posLogAtual != 1) { // Localizando o primeiro no da lista
           p->refMovel = p->refMovel->ant;
           p->posLogAtual--;
       }
       memcpy (reg, p->refMovel->dados, p->tamInfo); // Fazendo backup dos dados do no que sera excluido
       if (p->tamLista != 1) { // Se a lista contiver mais de um elemento
           aux = p->refMovel->prox; // um ponteiro auxiliar aponta para o no a direita do primeiro no, que sera excluido
           aux->ant = NULL;
           free (p->refMovel->dados); // Removendo o primeiro no da lista
           free (p->refMovel);
           p->refMovel = aux; // Fazendo o segundo ni se tornar o primeiro no da lista
           p->tamLista--;
           ret = SUCESSO;
       }
       else { // Caso haja apenas um elemento na lista
           free (p->refMovel->dados);
           free (p->refMovel);
           p->refMovel = NULL;
           p->tamLista--;
           p->posLogAtual--;
           ret = SUCESSO;
       }
   }
   return (ret);
}


int removeDoFim(LDDE *p, void *reg) {

   // Declaracao de variaveis
   noLDDE *aux;
   int ret = FRACASSO;

   // Instrucoes

   if (p->posLogAtual == 0||p->refMovel==NULL) {
       return (ret);
   }
   else {
       while (p->posLogAtual < p->tamLista) { // Localizando o ultimo no da lista
           p->refMovel = p->refMovel->prox;
           p->posLogAtual++;
       }
       memcpy (reg, p->refMovel->dados, p->tamInfo); // Fazendo backup dos dados do no que sera excluido
       if (p->tamLista != 1) { // Se a lista contiver mais de um elemento
           aux = p->refMovel->ant; // um ponteiro auxiliar aponta para o no a direita do primeiro no, que sera excluido
           aux->prox = NULL;
           free (p->refMovel->dados); // Removendo o primeiro no da lista
           free (p->refMovel);
           p->refMovel = aux; // Fazendo o penultimo no se tornar o ultimo no da lista
           p->posLogAtual--;
           p->tamLista--;
           ret = SUCESSO;
       }
       else { // Caso haja apenas um elemento na lista
           removeDoInicio (p, reg);
       }
   }
   return (ret);
}


int removeDaPosLog (LDDE *p, void *reg, unsigned int posLog) {

   // Declaracao de variaveis
   noLDDE *aux1, *aux2; // ponteiros que apontam para os nos vizinhos do no a ser removido

   // Instrucoes

   if ((posLog < 1) || (posLog > p->tamLista)) { // Se a posicao logica fornecida nao for valida
       return (FRACASSO);
   }

   if (posLog == 0) { // Se a posicao logica fornecida for a primeira
       return (removeDoInicio (p, reg));
   }

   if (posLog == p->tamLista) { // Se a posicao logica fornecida for a ultima
       return (removeDoFim (p, reg));
   }

   if (p->posLogAtual > posLog) {
       while (p->posLogAtual > posLog) { // Procurando o no a ser removido
           p->refMovel = p->refMovel->ant;
           p->posLogAtual--;
       }
   }
   else if (p->posLogAtual < posLog) {
       while (p->posLogAtual < posLog) { // Procurando o no a ser removido
           p->refMovel = p->refMovel->prox;
           p->posLogAtual++;
       }
   }

   memcpy (reg, p->refMovel->dados, p->tamInfo); // Fazemos backup dos dados do no que sera removido
   aux1 = p->refMovel->ant; // Colocamos um ponteiro auxiliar no no que precede o no que sera removido
   aux2 = p->refMovel->prox; // Colocamos outro ponteiro auxiliar no no que sucede o no que sera removido
   aux1->prox = aux2;
   aux2->ant = aux1;
   free (p->refMovel->dados); // Removendo o no
   free (p->refMovel);
   p->refMovel = aux1; // p->refMovel passa a apontar para o no que antecedia o no que foi removido
   p->posLogAtual--;
   p->tamLista--;
   return (SUCESSO);
}


int buscaNoInicio(LDDE *p, void *reg) {

   if ((p->refMovel == NULL) || (p->tamLista == 0)) {
       return (FRACASSO);
   }
   while (p->posLogAtual != 1) { // Localizando o primeiro no da lista
       p->refMovel = p->refMovel->ant;
       p->posLogAtual--;
   }
   memcpy (reg, p->refMovel->dados, p->tamInfo);
   return (SUCESSO);
}


int buscaNoFim (LDDE *p, void *reg) {

   if ((p->refMovel == NULL) || (p->tamLista == 0)) {
       return (FRACASSO);
   }
   while (p->posLogAtual < p->tamLista) { // Localizando o primeiro no da lista
       p->refMovel = p->refMovel->prox;
       p->posLogAtual++;
   }
   memcpy (reg, p->refMovel->dados, p->tamInfo);
   return (SUCESSO);
}


int buscaNaPosLog (LDDE *p, void *reg, unsigned int posLog) {

   if ((posLog < 1) || (posLog > p->tamLista)) { // Se a posicao logica fornecida nao for valida
       return (FRACASSO);
   }

   if (posLog == 1) { // Se a posiCao logica fornecida for a primeira
       return (buscaNoInicio (p, reg));
   }

   if (posLog == p->tamLista) { // Se a posicao logica fornecida for a ultima
       return (buscaNoFim (p, reg));
   }

   if (p->posLogAtual > posLog) {
       while (p->posLogAtual > posLog) { // Procurando o no buscado
           p->refMovel = p->refMovel->ant;
           p->posLogAtual--;
       }
   }
   else if (p->posLogAtual < posLog) {
       while (p->posLogAtual < posLog) { // Procurando o no buscado
           p->refMovel = p->refMovel->prox;
           p->posLogAtual++;
       }
   }

   memcpy (reg, p->refMovel->dados, p->tamInfo);
   return (SUCESSO);
}



void destroi (LDDE **pp) {
   // pp eh o endereco de um ponteiro para lista / *pp eh o conteudo desse ponteiro, ou seja, o endereco de uma lista

   // Declaracao de variaveis
   LDDE *ptr = NULL;
   int i; // contador de loop

   // Instrucoes

   ptr = *pp;

   if (ptr->refMovel == NULL) { // Se a lista estiver vazia
       free (ptr->refMovel);
       free (ptr);
   }
   else { // Se a lista nao estiver vazia
       while (ptr->posLogAtual != ptr->tamLista) { // Localizando o ultimo no da lista
           ptr->refMovel = ptr->refMovel->prox;
           ptr->posLogAtual++;
       }
       for (i=ptr->tamLista; i>0; i--) { // Para cada no da lista
           if (i != 1) { // Se o no nao for o primeiro da sequencia
               free (ptr->refMovel->dados); // Libere a regiao de dados
               free (ptr->refMovel->prox); // Libere o proximo no
               ptr->refMovel = ptr->refMovel->ant; // Aproveite o ponteiro ant para passar para o no anterior
               ptr->posLogAtual--;
               if (i != ptr->tamLista) {
                   ptr->tamLista--;
                   /* Quando refMovel aponta para o ultimo no e fazemos free (ptr->refMovel->prox), nao desalocamos no nenhum.
                   Logo, o tamanho da lista so diminui quando refMovel aponta para um no que nao eh o ultimo. */
               }
           }
           else { // Se o no for o primeiro da lista
               free (ptr->refMovel->dados); // Libere a regiao de dados
               free (ptr->refMovel->prox); // Libere o no posterior
               ptr->tamLista--;
               free (ptr->refMovel); // Libere o ultimo no da lista, que nao foi desalocado no loop for
               ptr->posLogAtual = 0;
               ptr->tamLista--;
               free (ptr); // Libere o ponteiro que aponta para o descritor;
           }
       }

   }
}


void reinicia (LDDE *p) {

   // Declaracao de variaveis
   int i; // contador de loop

   // Instrucoes

   if (p->refMovel == NULL) {
       // Se a lista estiver vazia, nao faca nada!
   }
   else { // Se a lista nao estiver vazia
       while (p->posLogAtual != p->tamLista) { // Localizando o ultimo no da lista
           p->refMovel = p->refMovel->prox;
           p->posLogAtual++;
       }
       for (i=p->tamLista; i>0; i--) { // Para cada no da lista
           if (i != 1) { // Se o no nao for o primeiro da sequencia
               free (p->refMovel->dados); // Libere a regiao de dados
               free (p->refMovel->prox); // Libere o proximo no
               p->refMovel = p->refMovel->ant; // Aproveite o ponteiro ant para passar para o no anterior
               p->posLogAtual--;
               if (i != p->tamLista) {
                   p->tamLista--;
                   /* Quando refMovel aponta para o ultimo no e fazemos free (ptr->refMovel->prox), nao desalocamos no nenhum.
                   Logo, o tamanho da lista so diminui quando refMovel aponta para um no que nao eh o ultimo. */
               }
           }
           else { // Se o no for o primeiro da lista
               free (p->refMovel->dados); // Libere a regiao de dados
               free (p->refMovel->prox); // Libere o no posterior
               p->tamLista--;
               free (p->refMovel); // Libere o ultimo no da lista, que nao foi desalocado no loop for
               p->refMovel = NULL;
               p->posLogAtual = 0;
               p->tamLista--;
           }
       }
    }
}
