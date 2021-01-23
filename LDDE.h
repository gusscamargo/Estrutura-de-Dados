# include "LDDE_priv.h"

/// INTERFACE


int cria (LDDE **pp, int tamInfo);

/* OBJETIVO DA FUNCAO: criar uma lista vazia.

PRE-CONDICOES: o argumento **pp corresponde ao endereco de memoria de um ponteiro para uma LDDE; tamInfo eh o tamanho, em bytes,
que a regiao de dados de um no da LDDE consegue armazenar. Deve, portanto, ser um numero positivo.

POS-CONDICOES: caso a criacao seja bem-sucedida, a funcao retorna 1. Caso contrario, retorna 0.
Se for fornecido um numero negativo para o argumento tamInfo, a lista sera criada, porem nao sera possivel fazer insercoes.
A posicao inicial da lista eh 1.

*/


int insereNoInicio (LDDE *p, void *novo);

/* OBJETIVO DA FUNCAO: salvar um dado na primeira posicao da lista.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. Se for fornecido o endereco de memoria de uma lista que ainda
nao foi criada, a funcao da erro. *novo eh o endereco de memoria do dado que se deseja incluir na lista.

POS-CONDICOES: se a insercao for bem-sucedida, a funcao retorna 1. Caso contrario, retorna 0.

*/


int insereNoFim (LDDE *p, void *novo);

/* OBJETIVO DA FUNCAO: salvar um dado na ultima posicao da lista.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. Se for fornecido o endereco de memoria de uma lista que ainda
nao foi criada, a funcao da erro. *novo eh o endereco de memoria do dado que se deseja incluir na lista.

POS-CONDICOES: se a insercao for bem-sucedida, a funcao retorna 1. Caso contrario, retorna 0.

*/


int insereNaPosLog (LDDE *p, void *novo, unsigned int posLog);

/* OBJETIVO DA FUNCAO: salvar um dado em uma posicao da lista eh escolha do usuario.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. Se for fornecido o endereco de memoria de uma lista que ainda
nao foi criada, a funcao da erro. *novo eh o endereco de memoria do dado que se deseja incluir na lista. posLog eh a posicao da
lista em que o usuario deseja inserir o dado. Precisa ser, portanto, um numero positivo e que corresponda a uma posicao que
exista na lista ou, no m�ximo, que seja uma unidade maior que a ultima posicao da lista, no caso de o usuario querer fazer uma
insercao na ultima posicao da lista utilizando essa funcao.

POS-CONDICOES: se a insercao for bem-sucedida, a funcao retorna 1. Caso contrario, retorna 0.

*/


int tamanho (LDDE *p);

/* OBJETIVO DA FUNCAO: fornecer o numero de elementos ja inseridos numa lista. Se for fornecido o endereco de memoria de uma lista que ainda
nao foi criada, a funcao da erro.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada.

POS-CONDIOEES: a funcao retorna um numero inteiro correspondente ao numero de elementos ja inseridos na lista cujo endereco de
memoria foi informado.

*/


void reinicia (LDDE *p);

/* OBJETIVO DA FUNCAO: deixar a lista na mesma situacao em que estava quando foi criada. Entre outras coisas, ela nao contera
mais elementos.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada.

POS-CONDICOES: a lista de endereco p fica com a mesma estrutura que possuia quando foi criada. Ela pode ser usada, portanto,
como se fosse uma lista que nunca foi utilizada.

*/


void destroi (LDDE **pp);

/* OBJETIVO DA FUNCAO: devolver os recursos de memoria utilizados pela lista a maquina.

PRE-CONDICOES: **pp eh o endereco de memoria de um ponteiro de uma lista ja criada.

PoS-CONDICOES: a funcao desaloca todas as regioes de memoria onde estavam salvos os dados de interesse assim como as regioes
que eram a infraestrutura da lista. Desse modo, a lista apontada por pp inexiste apos ser destruida.

*/


int buscaNoInicio (LDDE *p, void *reg);

/* OBJETIVO DA FUNCAO: criar uma copia do elemento salvo na regiao de dados do primeiro no da lista.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. *reg eh o endereco de memoria da variavel para onde o dado do
primeiro no da lista sera copiado. O tipo dessa variavel deve ser igual ao tipo de dado salvo na lista.

POS-CONDICOES: se a busca for bem-sucedida, a funcao retorna 1 e uma copia dos dados salvos no primeiro no da lista estarao
disponiveis na variavel cujo endereco de memoria foi fornecido. Caso a busca nao seja bem-sucedida, a funcao retorna 0 (zero).

*/


int buscaNoFim (LDDE *p, void *reg);

/* OBJETIVO DA FUNCAO: criar uma copia do elemento salvo na regiao de dados do ultimo no da lista.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. *reg �
eh o endereco de memoria da vari�vel para onde o dado do
ultimo no da lista sera copiado. O tipo dessa variavel deve ser igual ao tipo de dado salvo na lista.

POS-CONDICOES: se a busca for bem-sucedida, a funcao retorna 1 e uma copia dos dados salvos no ultimo no da lista estarao
disponiveis na variavel cujo endereco de memoria foi fornecido. Caso a busca nao seja bem-sucedida, a funcao retorna 0 (zero).

*/


int buscaNaPosLog (LDDE *p, void *reg, unsigned int posLog);

/* OBJETIVO DA FUNCAO: criar uma copia do elemento salvo na regiao de dados de um no cuja posicao eh fornecida pelo usuario.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. *reg eh o endereco de memoria da variavel para onde o dado do
no solicitado pelo usuario sera copiado. O tipo dessa variavel deve ser igual ao tipo de dado salvo na lista. posLog eh o numero
correspondente a posicao logica do no cujos dados da regiao de memoria o usuario deseja copiar. Deve, portanto, ser um numero
positivo.

POS-CONDICOES: se a busca for bem-sucedida, a funcao retorna 1 e uma copia dos dados salvos no no solicitado estarao disponiveis
na variavel cujo endereco de memoria foi fornecido. Caso a busca nao seja bem-sucedida, a funcao retorna 0 (zero).

*/


int removeDoInicio (LDDE *p, void *reg);

/* OBJETIVO DA FUNCAO: excluir o primeiro no da lista.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. A funcao tambem cria uma copia dos dados que estao na regiao
de dados do no a ser removido. *reg eh o endereco de memoria da variavel para onde os dados do primeiro no da lista serao copiados.
O tipo de dado dessa variavel deve ser igual ao tipo de dado salvo na lista.

POS-CONDICOES: se a remocao for bem-sucedida, a funcao retorna 1 e uma copia dos dados salvos no primeiro no estarao disponiveis
na variavel cujo endereco de memoria foi fornecido. Caso a remocao nao seja bem-sucedida, a funcao retorna 0 (zero).

*/


int removeDoFim (LDDE *p, void *reg);

/* OBJETIVO DA FUNCAO: excluir o ultimo no da lista.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. A funcao tambem cria uma copia dos dados que estao na regiao
de dados do no a ser removido. *reg eh o endereco de memoria da variavel para onde os dados do ultimo noda lista serao copiados.
O tipo de dado dessa variavel deve ser igual ao tipo de dado salvo na lista.

POS-CONDICOES: se a remocao for bem-sucedida, a funcao retorna 1 e uma copia dos dados salvos no primeiro no estarao disponiveis
na variavel cujo endereco de memoria foi fornecido. Caso a remocao nao seja bem-sucedida, a funcao retorna 0 (zero).

*/


int removeDaPosLog (LDDE *p, void *reg, unsigned int posLog);

/* OBJETIVO DA FUNCAO: excluir um no de uma posicao logica determinada pelo usuario.

PRE-CONDICOES: *p eh o endereco de memoria de uma LDDE ja criada. A funcao tambem cria uma ccpia dos dados que estao na regiao
de dados do no a ser removido. *reg eh o endereco de memoria da variavel para onde os dados do no a ser removido serao copiados.
O tipo de dado dessa variavel deve ser igual ao tipo de dado salvo na lista. posLog eh o numero correspondente a posicao logica
do no que se pretende remover. Deve, portanto, ser um numero positivo.

POS-CONDICOES: se a remocao for bem-sucedida, a funcao retorna 1 e uma copia dos dados que estavam salvos no excluido estarao
disponiveis na variavel cujo endereco de memoria foi fornecido. Caso a remocao nao seja bem-sucedida, a funcao retorna 0 (zero).

*/
