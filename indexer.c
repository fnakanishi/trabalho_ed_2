#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "lib.h"
#include "llrbt.h"

//	Alunos:	Carlos Felipe Godinho Silva, David Gomes de Carvalho e Guilherme Alves da Silva
//	GRR:		GRR20184630 e GRR20184616 e GRR20186254


FILE *arq;
node *hash[MAX_SIZE], *max[100];
char linha[BUFFER_SIZE];
int max_tam;

int freqWord(char *word) {
   int count = 0;
   char *trecho;
   while ((fgets (linha , BUFFER_SIZE , arq) != NULL)) {
      toUpperCase(linha);
      trecho = strstr(linha, word);
      while (trecho != NULL){
         if (isWord(trecho, word) == 1)
         count++;
         trecho[0] = trecho[0]+1;
         trecho = strstr(trecho, word);
      }
   }
   return count;
}

int freq(){
   char word[100], c, *palavra;
   int tam = 0, menor = 0, aux = 0, num;
   nozinho = (node *)malloc(sizeof(node));
   while ((c = fgetc(arq)) != EOF) {
      if ((c > 0x60 && c < 0x7B)) {
         word[tam] = c - 0x20;
         tam++;
      } else if((c > 0x40 && c < 0x5B) || (c > 0x2F && c < 0x3A)) {
         word[tam] = c;
         tam++;
      } else {
         if (tam > 0) {
            palavra = (char *)malloc(tam * sizeof(char));
            for (int i = 0; i < tam; i++)
               palavra[i] = word[i];
            num = (tam > MAX_SIZE) ? (MAX_SIZE - 1) : (tam - 1);
            if (tam > 1) {
               hash[num] = insert(hash[num], palavra);
               hash[num] -> color = false;
               if (menor < nozinho -> count) {
                  aux = keepMax(max, max_tam);
                  menor = aux == -1 ? menor : aux;
               }
            }
            else {
               hash[0] = insert2(hash[0], palavra);
               hash[0] -> color = false;
               if (menor < nozinho -> count) {
                  aux = keepMax2(max, max_tam);
                  menor = aux == -1 ? menor : aux;
               }
            }
            //printf("%d\t%d\t%s\n", nozinho -> count, tam+1, nozinho -> data);
         }
         tam = 0;
      }
   }
   return 1;
}

int main (int argc, char *argv[]) {

   clock_t inicio, fim;
   double duracao;
   inicio = clock();


   if (argc < 3) falha(-1);

   if((arq = fopen(argv[3], "r")) != NULL) {
      fseek(arq, 0, SEEK_SET);

      *hash = (node *)malloc(MAX_SIZE * sizeof(node));
      node *no;

      if (strcmp(argv[1], "--freq") == 0) {
         max_tam = convertNum(argv[2]);
         if (max_tam <= 0)
            falha(0);
         for (int i = 0; i < max_tam; i++) {
            no = (node *)malloc(sizeof(node));
            no -> count = 0;
            no -> data = "A";
            max[i] = no;
         }
         initFreq(argv[2], argv[3]);
         freq();
         insertionSort(max, max_tam);
         for (int i = (max_tam - 1); i >= 0; i--) {
            printf("\tPalavra n.%d em ocorrências (aparece %d x): %s\n", (max_tam - i), max[i] -> count, max[i] -> data);
         }
      } else if (strcmp(argv[1], "--freq-word") == 0) {
         char *trecho, *word = argv[2];
         toUpperCase(word);
         int qtde = freqWord(word);
         printf("A palavra \"%s\" foi encontrada %d vezes no arquivo \"%s\".\n\n", argv[2], qtde, argv[3]);
      } else if (strcmp(argv[1], "--search") == 0) {
         printf("Procura pelo termo \"%s\" nos arquivos \"%s\"", argv[2], argv[3]);
         if (argc > 4)
            for (int i = 4; i < argc; i++)
               printf(", \"%s\"", argv[i]);
         printf(".\n");
      } else {
         falha(0);
      }
   } else {
         falha(-2);
   }
   fclose (arq);
   fim = clock();
   duracao = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
   int min, seg;
   div_t tempo = div(duracao, 60);
   min = tempo.quot;
   seg = tempo.rem;


   /*for (int i = 0; i < MAX_SIZE; i++){
      inorder(hash[i]);
   }*/
   printf("\n\nDemorou aproximadamente %d minutos e %d segundos para executar\n", min, seg);
}