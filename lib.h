#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

#define MAX_SIZE 20
#define BUFFER_SIZE 200

//	Alunos:	Carlos Felipe Godinho Silva, David Gomes de Carvalho e Guilherme Alves da Silva
//	GRR:		GRR20184630 e GRR20184616 e GRR20186254

// gcc -c -I"~/DS141" lib.h    (Código pra incluir na biblioteca)

typedef struct dados {
  char *word;
  int tam;
  int qtde;
} dados;

void falha(int erro);

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

/*int compara(char *a, char *b) {
   char *stra = strdup(a);
   char *strb = strdup(b);
   for(char *p = stra; *p; ++p)
      *p = *p > 0x40 && *p < 0x5B ? *p | 0x60 : *p;
   for(char *p = strb; *p; ++p)
      *p = *p > 0x40 && *p < 0x5B ? *p | 0x60 : *p;
   return (strcmp(stra, strb));
}

char *remPunct(char *str) {
   char *dup = strdup(str);
   if (strlen(dup) <= 0 || (strlen(dup) == 1 && dup[0] == '\n')) return NULL;
   if ((dup[strlen(dup) - 1] > 0x20 && dup[strlen(dup) - 1] < 0x30 ) || (dup[strlen(dup) - 1] > 0x39 && dup[strlen(dup) - 1] < 0x41 ))
      dup[strlen(dup) - 1] = '\0';
   else if (dup[strlen(dup) - 1] == '\n') {
      for (int i = strlen(dup); i >= 0; i--) {
         if (dup[i] == '\n') {
            dup[i] = '\0';
         }
         if (dup[i] == '\r')
            dup[i] == '\0';
      }
   }
   return dup;
}

char *clean(char *word){
   int tam = strlen(word);
   int i = 0, j = 0;
   for (int i = 0; i < tam; i++){
      if(word[strlen(word)] > 0x40 && word[strlen(word)] < 0x5B) {
      int tam = strlen(word) - 1;
      char *aux = (char *)malloc(sizeof(char *)  *(tam));
      for (int i = 0; i < tam; i++) aux[i] = word[i];
      return aux;
      }
   }
   printf(":%s:\n", word);
   return word;
}*/

void falha(int erro) {
   system("clear");
   printf("\n\n\t\t\tErro!");
   switch (erro){
      case -2:
         printf("\n\tArquivo não encontrado, verificar e tentar novamente.");
         break;
      case -1:
         printf("\n\tParametros de entrada inválidos.");
         break;
      case 0:
         printf("\n\tFunção não disponível.");
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