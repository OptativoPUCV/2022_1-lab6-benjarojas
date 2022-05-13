#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  int validRow[10] = {0};
  int validFlag = 1;

  print_node(n);

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++)
    {
      if (validRow[n->sudo[i][j]] == 1)
      {
        validFlag = 0;
      }

      if (validRow[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
      {
        validRow[n->sudo[i][j]] = 1;
        printf("%d encontrado \n", n->sudo[i][j]);
      }  
    }
    int validRow[20] = {0};
    validFlag = 1;
    if(validFlag) printf("columna %d valida\n", i);
  }

  if(validFlag)
  {
    printf("todas las columnas son validas\n");
  } else {
    printf("hay 1 o mas columna(s) invalida\n");
  }
  

  /* // iterar cada submatriz
  for (int s = 0; s < 9; s++)
  {
    int k=s,p; 
    for(p=0;p<9;p++){
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      printf("%d ",n->sudo[i][j]);
      if(p%3 == 2) printf("\n");
    }
  } */

  return 1;
}

List* get_adj_nodes(Node* n){ 
    List* list=createList();
    Node* auxNode;
    int emptyCaseRow, emptyCaseColumn;
    int flagEmptyCase = 0;

    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          emptyCaseRow = i; // indice fila casilla vacia
          emptyCaseColumn = j; // indice columna casilla vacia
          flagEmptyCase = 1;
          break;
        }
      }
      if(flagEmptyCase) break;
    }

    // si no se encontro ninguna casilla vacia, es estado final
    if(!flagEmptyCase) return list;

    // crear nodos adjuntos reemplazando la casilla vacia por [1..9]
    for (int i = 1; i < 10; i++)
    {
      auxNode = copy(n); // copia del nodo n 'n'
      auxNode->sudo[emptyCaseRow][emptyCaseColumn] = i;
      pushBack(list, auxNode);
    }
    return list; // retornamos la lista de estados
}

int is_final(Node* n){
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
        if(n->sudo[i][j] == 0) return 0;
    return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/