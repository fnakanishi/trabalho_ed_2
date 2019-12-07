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

   pthread_t *tid;

   if (argc < 4) falha(-1);

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
         if (argc < 4) {
            falha(-1);
         } else if (argc == 4) {
            printf("Arquivo mais relevante é: %s", argv[3]);
         } else {
            fclose(arq);
            int num_threads = argc - 3;
            int *num_palavras = (int *)malloc(num_threads * sizeof(int));
            int qtde_pal = 0;
            char word[100], **pal;
            dados **param = (dados **)malloc(num_threads * sizeof(dados*));
            tid = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
            for (int i = 0; i < num_threads; i++){
               param[i] -> fp = fopen(argv[i+3], "r");
               fseek(param[i] -> fp, 0, SEEK_SET);
               param[i] -> num = i;
               pthread_create(&tid[i], NULL, ler, &param[i]);
            }
            int tam = 0;
            for (int i = 0; i < strlen(argv[2]); i++){
               if (argv[2][i] > 0x60 && argv[2][i] < 0x7B) {
                  word[1] = argv[2][i] - 0x20;
                  tam++;
               } else if ((argv[2][i] > 0x40 && argv[2][i] < 0x5B) || (argv[2][i] > 0x2F && argv[2][i] < 0x3A)) {
                  word[1] = argv[2][i];
                  tam++;
               } else if(tam > 0) {
                  strncpy(pal[qtde_pal], word, tam);
                  qtde_pal++;
                  tam = 0;
               } else { tam = 0; }
            }
            for (int i = 0; i < num_threads; i++){
               pthread_join(tid[i], NULL);
               fseek(param[i] -> fp, 0, SEEK_SET);
            }
            int qtdeArq[100][100];
            int num_docs[100];
            for (int i = 0; i < 100; i++)
               num_docs[i] = 0;
            for (int j = 0; j < qtde_pal; j++){
               for (int i = 0; i < num_threads; i++){
                  param[i] -> word = pal[j];
                  pthread_create(&tid[i], NULL, ler2, &param[i]);
               }
               for (int i = 0; i < num_threads; i++){
                  pthread_join(tid[i], NULL);
                  qtdeArq[j][i] = param[i] -> num;
                  if (param[i] -> num > 0)
                     num_docs[j]++;
                  fseek(param[i] -> fp, 0, SEEK_SET);
               }
            }
            int t, d;
            double *tfidf = (double *)malloc(num_threads * sizeof(double));
            double *media = (double *)malloc(qtde_pal * sizeof(double));
            for (int j = 0; j < num_threads; j++){
               fclose(param[j] -> fp);
               media[j] = 0;
               for (int i = 0; i < qtde_pal; i++){
                  t = qtdeArq[i][j];
                  d = num_docs[i];
                  tfidf[i] = tf(t, num_palavras[num_threads]) * idf(num_threads,d);
                  media[j] += tfidf[i];
               }
               media[j] = media[j] / qtde_pal;
            }
            double maiortfidf = 0;
            int pos = -1;
            for (int i = 0; i < num_threads; i++){
               if (maiortfidf < media[i]) {
                  maiortfidf = media[i];
                  pos = i;
               }
            }
            pos += 3;
            printf("Arquivo mais relevante para o termo \"%s\" é: %s", argv[2], argv[pos]);
         }
      } else {
         falha(0);
      }
   } else {
         falha(-2);
   }
   fclose (arq);
}