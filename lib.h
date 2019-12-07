#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#define MAX_SIZE 20
#define BUFFER_SIZE 200

//	Alunos:	Carlos Felipe Godinho Silva, David Gomes de Carvalho e Guilherme Alves da Silva
//	GRR:		GRR20184630 e GRR20184616 e GRR20186254

// gcc -c -I"~/DS141" lib.h    (Código pra incluir na biblioteca)

typedef struct dados {
  FILE *fp;
  char *word;
  int num;
} dados;

int *num_palavras;

void falha(int erro);

double tf(int t, int d){
   if (d != 0)
      return t/(double)d;
   falha(-2);
}

double idf(int t, int d){
   if (d != 0)
      return log10(t/(double)d);
   falha(-3);
}

void toUpperCase(char *word) {
   for(char *p = word; *p; ++p)
      *p = *p > 0x60 && *p < 0x7B ? *p - 32 : *p;
}

void toLowerCase(char *word) {
   for(char *p = word; *p; ++p)
      *p = *p > 0x40 && *p < 0x5B ? *p + 32 : *p;
}

int isWord(char *string, char *word){
   int tam = strlen(string);
   if (((*(string - 1) > 0x40) && (*(string - 1) < 0x5B)) || (*(string - 1) == 0x2D) || (*(string - 1) == 0x2E))
      return 0;
   else if (((string[strlen(word)] > 0x40) && (string[strlen(word)] < 0x5B)) || (string[strlen(word)] == 0x2D) || (string[strlen(word)] == 0x2E))
      return 0;
   return 1;
}

void falha(int erro) {
   system("clear");
   printf("\n\n\t\t\tErro!");
   switch (erro){
      case -3:
         printf("\n\tArquivo sem palavras.\n");
         break;
      case -2:
         printf("\n\tArquivo não encontrado, verificar e tentar novamente.\n");
         break;
      case -1:
         printf("\n\tParametros de entrada inválidos.\n");
         break;
      case 0:
         printf("\n\tFunção não disponível.\n");
         break;
   }
   printf("\n\tEncerrando o programa...\n\n");
   exit(-1);
}

int convertNum(char *str) {
   char *p;
   int num;
   errno = 0;
   long conv = strtol(str, &p, 10);

   if (errno != 0 || *p != '\0' || conv > INT_MAX) {
      falha(-1);
   } else {
         num = conv;
         return num;
   }
}

void *ler(void *param){
   dados *p = param;
   int qtde = 0, tam = 0, num = p -> num;
   FILE *fp = p -> fp;
   char c;
   while ((c = fgetc(fp)) != EOF) {
      if ((c > 0x60 && c < 0x7B) || (c > 0x40 && c < 0x5B) || (c > 0x2F && c < 0x3A)) {
         tam++;
      } else if(tam > 0) {
         qtde++;
         tam = 0;
      } else { tam = 0; }
   }
   num_palavras[num] = qtde;
   pthread_exit(0);
}



void *ler2(void *param){
   dados *p = param;
   int qtde = 0;
   FILE *fp = p -> fp;
   char *word = p -> word;
   char *trecho, linha[BUFFER_SIZE];
   while ((fgets (linha , BUFFER_SIZE , fp) != NULL)) {
      toUpperCase(linha);
      trecho = strstr(linha, word);
      while (trecho != NULL){
         if (isWord(trecho, word) == 1)
         qtde++;
         trecho[0] = trecho[0]+1;
         trecho = strstr(trecho, word);
      }
   }
   p -> num = qtde;
   pthread_exit(0);
}

void initFreq(char *qtde, char *arquivo) {
   int tam = strlen(qtde);
   tam += strlen(arquivo);
   system("clear");
   printf("\n\t#");
   for (int i = 0; i < 98; i++)
      printf("#");
   printf("#\n\t#");
   for (int i = 0; i < 98; i++)
      printf(" ");
   printf("#\n\t#");
   printf("  Calculando as %s palavras mais recorrentes no arquivo \"%s\".  ", qtde, arquivo);
   for (int i = 0; i < 39 - tam; i++)
      printf(" ");
   printf("#\n\t#");
   for (int i = 0; i < 98; i++)
      printf(" ");
   printf("#\n\t#");
   for (int i = 0; i < 98; i++)
      printf("#");
   printf("#\n\n");
}
