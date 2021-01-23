
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "cliente.h"


int main() {

    // Declaracoes de variaveis

    int opcao = 12345; // Para garantir nao ser um numero do menu
    LDDE *lista = NULL;
    float elemento;
    void *regiao_inicio = NULL;
    void *regiao_fim = NULL;
    void *regiao_poslog = NULL;
    void *regiao_removeinicio = NULL;
    void *regiao_removefim = NULL;
    void *regiao_removeposlog = NULL;
    unsigned int posicao;

    info reg;
    cria (&lista, sizeof (info)); // Criando lista


    /// ABRINDO ARQUIVO;

    FILE *arq = fopen ("arquivo1.txt", "r");
    int linha, colunaa, coluna = 1, linhaaux, colunaaux, aux;
    char c;
    int i = 0, j;
    int iniciopalavra = 1;


    if (arq == NULL) {
        printf ("Arquivo vazio.");
        fclose (arq);
        return 0;
    }
    while (1) {
        c = fgetc(arq); // Retorna proximo caractere a ser lido
        // Obs: o pulo de linha tambem eh lido como caractere.
        if (feof(arq)) {
            printf ("Sucesso na leitura\n\n");
            break;
        }
        if (iniciopalavra == 1) { // Primeira letra da palavra
            reg.coluna = coluna;
            i = 0;
            reg.palavra[i] = c;
            i++;
            coluna++;
            iniciopalavra = 0;
        }
        else if ((c != '\n') && (c != ' ')) { // Segunda a ultima letra da palavra
            reg.palavra[i] = c;
            i++;
            coluna++;
        }
        else { // if ((c == '\0') || (c == ' '))
            reg.palavra[i] = '\0'; // Fim da palavra
            insereNoFim (lista, &reg);
            coluna++; // Coluna do espaco depois da palavra
            if (c == '\n') {
                reg.coluna = coluna;
                reg.palavra[0] = '\n';
                reg.palavra[1] = '\0';
                insereNoFim (lista, &reg);
                coluna = 1;
            }
        iniciopalavra = 1;
        }
    }
    fclose(arq);
    /// FECHANDO ARQUIVO;


    /// INICIANDO O MENU DAS FUNCOES

    while (opcao != 0) {
        printf ("----------------------MENU-------------------\n\n");
        printf ("(1) Contar palavras do texto;\n(2) Encontrar quantas vezes a palavra x está no texto;\n"
                "(3) Encontrar palavra na posicao (x,y) especificada;\n(4) Inserir palavra na posicao (x,y);\n"
                "(5) Remover palavra da posicao (x,y);\n(6) Printar o texto em tela;\n"
                "(7) Substituicao de uma palavra na posicao (x,y);\n(8) Substituicao de todas as ocorrencias de uma palavra;\n"
                "(0) Encerrar operacao e salvar arquivos\n");
        printf ("\nOpcao escolhida: ");
        scanf ("%i", &opcao);
        fflush (stdin);
        printf ("---------------------------------------------\n\n");


        /// INICIO DE FUNCOES

		// FUNCAO (A)

        if (opcao == 1) {
            int i, contadorpalavras = 0;
            for (i=1; i<=tamanho(lista); i++) {
                buscaNaPosLog(lista,&reg,i);
                if (strcmp (reg.palavra, "\n")) {
                    contadorpalavras++;
                }
            }
            printf ("Existem %i palavras no texto\n\n",contadorpalavras);
        }

		// FUNCAO (B)

        else if (opcao == 2) {
            int cont = 0, i;
            char stringdigitada[50];

            printf ("Digite a palavra a ser buscada: ");
            scanf ("%s", stringdigitada);
            for (i=1; i<=tamanho(lista); i++) {
                buscaNaPosLog (lista, &reg, i);
                if (!strcmp (reg.palavra, stringdigitada)) { // Caso sim, entra no if
                    cont++;
                }
            }
            printf ("Existem %i ocorrencias da palavra '%s' no texto.\n\n", cont, stringdigitada);
        }


        /// FUNCAO (C)

        else if (opcao == 3) {
            int linhaaux = 1, i;
            int linha, coluna, bandeira = 0;
            printf ("Digite a linha da palavra: ");
            scanf ("%i", &linha);
            printf ("Agora digite a coluna: ");
            scanf ("%i", &colunaa);
            for (i=1; i<=tamanho(lista); i++) {
                buscaNaPosLog (lista, &reg, i);
                if (!strcmp (reg.palavra, "\n")) {
                    linhaaux++;
                }
                if ((reg.coluna <= colunaa) && ((reg.coluna + strlen (reg.palavra)) >= colunaa) && (linhaaux == linha)) { // Verificando se a coluna inicial da palavra eh menor que a coluna digitada && a coluna final da palavra eh maior que a coluna digita && se estão na mesma linha.
                    if (((reg.coluna + strlen(reg.palavra)) - 1) >= colunaa) { // Espaco em branco
                        printf ("\n\nPalavra encontrada: %s\n", reg.palavra);
                        bandeira = 1;
                        break;
                    }
                    else { // Eh espaco em branco
                        printf ("Voce achou um espaco em branco!\n");
                        bandeira = 1;
                        break;
                    }
                }
            }
            if (bandeira == 0) {
                printf ("Você digitou uma posicao de caracter em branco.\n\n");
            }
        }


        /// FUNÇÃO (D)

        else if (opcao == 4) {
            int linhaaux = 1, i, flag = 0, colunaaux;
            int bandeira = 0, tam;
            char string[50], stringaux[50];
            fflush (stdin);
            printf ("Digite a palavra a ser inserida: ");
            scanf ("%s", string);
            fflush (stdin);
            printf ("Digite a linha da palavra: ");
            scanf ("%i", &linha);
            fflush (stdin);
            printf ("Agora digite a coluna: ");
            scanf ("%i", &colunaa);
            fflush (stdin);
            for (i=1; i<=tamanho(lista); i++){
                buscaNaPosLog (lista, &reg, i);
                if (!strcmp (reg.palavra, "\n")) {//quando reg.palavra for \n
                    linhaaux++;
                }
                if ((reg.coluna <= colunaa) && ((reg.coluna + strlen (reg.palavra)) >= colunaa) && (linhaaux == linha)) {
                    // Se pede pra inserir na col. 6 e tem string, ele insere depois
                    if ((reg.coluna + strlen (reg.palavra)) == colunaa) {
                        printf ("\nVoce achou um espaco em branco! Insercao proibida!\n\n");
                        break;
                    }
                    aux = -strlen (string) - 1;
					//negativo porque na funcao ele ja ira subtrair
                    memcpy (reg.palavra, string, sizeof (string));
                    insereNaPosLog (lista, &reg, i);
                    // DESLOCANDO:
                   	j = i+1;
                    while (strcmp (reg.palavra, "\n")) {
                        buscaNaPosLog (lista, &reg, j);
                        modificaLista (lista, reg.palavra, reg.coluna, aux, j);
                        j++;
                    }
					printf ("\nSucesso na insercao\n\n");
					break;
                }
            }
        }


        /// FUNÇÃO (E)

        else if (opcao == 5) {
            char string[50];
            printf ("Digite a linha da palavra: ");
            scanf ("%i", &linha);
            fflush (stdin);
            printf ("Agora digite a coluna: ");
            scanf ("%i", &coluna);
            fflush (stdin);
            linhaaux = 1;

            for (i=1; i<=tamanho(lista); i++) {
                buscaNaPosLog (lista, &reg, i);
                if (!strcmp (reg.palavra, "\n")) { // Quando reg.palavra for "\n"
                    linhaaux++;
                }
                if ((reg.coluna <= coluna) && ((reg.coluna + strlen (reg.palavra)) >= coluna) && (linhaaux == linha)) {
                    if ((reg.coluna + strlen (reg.palavra)) == coluna) { // Espaço em branco
                        printf ("\nVoce achou um espaco em branco! Insercao proibida\n\n");
                        break;
                    }
                    colunaaux = reg.coluna;
                    aux = strlen (reg.palavra) + 1;
                    memcpy (string, reg.palavra, sizeof (reg.palavra));
					buscaNaPosLog(lista,&reg,i);
					removeDaPosLog (lista, &reg, i);
                    //DESLOCAMENTO:
                    j = i;
					buscaNaPosLog(lista,&reg,j);
					
                    while (strcmp (reg.palavra, "\n")) {
                        buscaNaPosLog (lista, &reg, j);
                        modificaLista (lista, reg.palavra, reg.coluna, aux, j);
                        j++;
                    }
					printf ("\nSucesso na remocao\n\n");
                    break;
                }
            }
        }

        /// FUNÇÃO (F)

        else if (opcao == 6) {
            for (i=1; i<tamanho(lista); i++) {
                buscaNaPosLog (lista, &reg, i);
                if (strcmp (reg.palavra, "\n")) {
                    printf ("%s ",reg.palavra);
                }
                else {
                    printf ("%s", reg.palavra);
                }
            }
            printf ("\n");
        }

        /// FUNÇÃO (G)
 
        else if (opcao == 7) {
            int linhaaux = 1, i, flag = 0, colunaaux;
            int bandeira = 0, tam;
            char string[50], stringaux[50];
            fflush (stdin);
            printf ("Digite a palavra a ser inserida: ");
            scanf ("%s", string);
            fflush (stdin);
            printf ("Digite a linha da palavra: ");
            scanf ("%i", &linha);
            fflush (stdin);
            printf ("Agora digite a coluna: ");
            scanf ("%i", &colunaa);
            fflush (stdin);
            for (i=1; i<=tamanho(lista); i++){
                buscaNaPosLog (lista, &reg, i);
                if (!strcmp (reg.palavra, "\n")) {//quando reg.palavra for \n
                    linhaaux++;
                }
                if ((reg.coluna <= colunaa) && ((reg.coluna + strlen (reg.palavra)) >= colunaa) && (linhaaux == linha)) {
                    if ((reg.coluna + strlen (reg.palavra)) == colunaa) { // Para saber se não eh espaco em branco
                        printf ("\nVoce achou um espaco em branco! Insercao proibida!\n");
                        break;
                    }
                    aux =- strlen (string) + strlen (reg.palavra);
                    memcpy (reg.palavra, string, sizeof (string));
                    insereNaPosLog (lista, &reg, i);
                    removeDaPosLog (lista, &reg, i + 1);

                    // DESLOCANDO:
                    j = i + 1;
                    while (strcmp (reg.palavra, "\n")) {
                        buscaNaPosLog (lista, &reg, j);
                        modificaLista (lista, reg.palavra, reg.coluna, aux, j);
                        j++;
                    }
					printf ("\nSucesso na substituicao\n\n");
                    break;
                }
            }
        }


        /// FUNÇÃO (H)

        else if (opcao == 8) {
            char string[50], string2[50];
            printf ("Digite a palavra a ser subtituida: ");
            scanf ("%s", string);
            fflush (stdin);
            printf ("Digite a palavra a inserir: ");
            scanf ("%s", string2);
            for (i=1; i<tamanho(lista); i++) {
                buscaNaPosLog (lista, &reg, i);
                if (!strcmp (string, reg.palavra)) {
                    aux =+ strlen(string) - strlen (string2);
                    memcpy (reg.palavra, string2, sizeof (string2));
                    insereNaPosLog (lista, &reg, i);
                    removeDaPosLog (lista, &reg, i + 1);
                    // DESLOCANDO:
                    j=i+1;
                    while (strcmp (reg.palavra, "\n")) {
                        buscaNaPosLog (lista, &reg, j);
                        modificaLista (lista, reg.palavra, reg.coluna, aux, j);
                        j++;
                    }
                }
            }
			printf ("\nSucesso na substituicao\n\n");
					
       }


       /// ENCERRAR PROGRAMA

        else if (opcao == 0) {
            break;
        }


       /// VALOR DIGITADO INCORRETAMENTE

        else {
            printf ("Valor digitado incorretamente.\n\n");
        }
    }


    /// SALVAMENTO DO NOVO ARQUIVO;

    arq = fopen ("novoarquivo.txt", "w");
    coluna = 1;
    for (i=1; i<=tamanho(lista); i++) {
        buscaNaPosLog(lista,&reg,i);
        if (strcmp (reg.palavra, "\n")) {
            fprintf (arq,"%s ",reg.palavra);
        }
        else {
            fprintf (arq,"%s",reg.palavra);
        }
    }
    fclose(arq);
    if (arq != NULL) {
        printf ("Dados gravados com sucesso!");
    }

}





