#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//	Alunos:	Carlos Felipe Godinho Silva, David Gomes de Carvalho e Guilherme Alves da Silva
//	GRR:		GRR20184630 e GRR20184616 e GRR20186254

// gcc -c -I"~/DS141" llrbt.h    (Código pra incluir na biblioteca)
  
typedef struct node {
   struct node *left, *right;
   char *data;
   int count;

   // red ==> true, black ==> false 
   bool color;
} node;


node *nozinho = NULL;

node* createNode(char *data) { 
   node *myNode = (node *) malloc(sizeof(node));
   myNode -> left = myNode -> right = NULL;
   myNode -> data = data;
   myNode -> count = 1;
  
   myNode -> color = true;
   nozinho = myNode;
   return myNode;
} 

node* rotateLeft(node* myNode) {
   node *child = myNode -> right;
   node *childLeft = child -> left;

   child -> left = myNode;
   myNode -> right = childLeft;

   return child;
} 

node* rotateRight(node* myNode) {
   node *child = myNode -> left;
   node *childRight =  child -> right;

   child -> right = myNode;
   myNode -> left = childRight;

   return child;
} 

int isRed(node *myNode) {
   if (myNode == NULL)
      return 0;
   return (myNode -> color == true);
}

void swapColors(node *node1, node *node2) {
   bool temp = node1 -> color;
   node1 -> color = node2 -> color;
   node2 -> color = temp;
}

node* insert(node* myNode, char *data) {
   if (myNode == NULL)
      return createNode(data);
   if (strcmp (data, myNode -> data) < 0)
      myNode -> left = insert(myNode -> left, data);
   else if (strcmp (data, myNode -> data) > 0)
      myNode -> right = insert(myNode -> right, data);
   else {
      myNode -> count ++;
      nozinho = myNode;
      return myNode;
   }

   if (isRed(myNode -> right) && !isRed(myNode -> left)) {
      myNode = rotateLeft(myNode);
      swapColors(myNode, myNode -> left);
   }

   if (isRed(myNode -> left) && isRed(myNode -> left -> left)) {
      myNode = rotateRight(myNode);
      swapColors(myNode, myNode -> right);
   }

   if (isRed(myNode -> left) && isRed(myNode -> right)) {
      myNode -> color = !myNode -> color;

      myNode -> left -> color = false;
      myNode -> right -> color = false;
   } 

   return myNode;
}

node* insert2(node* myNode, char *data) {
   if (myNode == NULL)
      return createNode(data);
   if (data < myNode -> data)
      myNode -> left = insert(myNode -> left, data);
   else if (data > myNode -> data)
      myNode -> right = insert(myNode -> right, data);
   else {
      myNode -> count ++;
      nozinho = myNode;
      return myNode;
   }

   if (isRed(myNode -> right) && !isRed(myNode -> left)) {
      myNode = rotateLeft(myNode);
      swapColors(myNode, myNode -> left);
   }

   if (isRed(myNode -> left) && isRed(myNode -> left -> left)) {
      myNode = rotateRight(myNode);
      swapColors(myNode, myNode -> right);
   }

   if (isRed(myNode -> left) && isRed(myNode -> right)) {
      myNode -> color = !myNode -> color;

      myNode -> left -> color = false;
      myNode -> right -> color = false;
   } 

   return myNode;
}

void insertionSort(node **ordem, int tam) {
    int i, j;
    node *no = (node *)malloc(sizeof(node));
    for (i = 1; i < tam; i++) {
        no = ordem[i];
        j = i - 1;
        while (j >= 0 && (ordem[j] -> count) > (no -> count)) {
            ordem[j + 1] = ordem[j];
            j--;
        }
        ordem[j + 1] = no;
    }
}

int keepMax(node **max, int max_tam){
   for (int i = 0; i < max_tam; i++) {
      if (strcmp(nozinho -> data, max[i] -> data) == 0) {
         max[i] -> count ++;
         return -1;
      }
   }
   int menor = nozinho -> count;
   int posMenor = -1;
   for (int i = 0; i < max_tam; i++) {
      if (menor > max[i] ->  count) {
         menor = max[i] -> count;
         posMenor = i;
      }
   }
   if (posMenor != -1) {
      max[posMenor] = nozinho;
   }
   return menor;
}

int keepMax2(node **max, int max_tam){
   for (int i = 0; i < max_tam; i++) {
      if (nozinho -> data == max[i] -> data) {
         max[i] -> count ++;
         return -1;
      }
   }
   int menor = nozinho -> count;
   int posMenor = -1;
   for (int i = 0; i < max_tam; i++) {
      if (menor > max[i] ->  count) {
         menor = max[i] -> count;
         posMenor = i;
      }
   }
   if (posMenor != -1) {
      max[posMenor] = nozinho;
   }
   return menor;
}

void inorder(node *node) {
   if (node) {
      inorder(node -> left);
      printf("%s (%d) ", node -> data, node -> count);
      inorder(node -> right);
   }
}