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

    int found[10] = {0};

    print_node(n);

    for (int i = 0; i < 10; i++)
    {
      printf("found: %d\n", found[i]);
    }
    

    return 1;
}


List* get_adj_nodes(Node* n){

    List* list=createList();

    Node* aux;
    int emptyCaseRow = 0;
    int emptyCaseColumn = 0;
    int flagEmptyCase = 0;

    for (int i = 0; i < 8; i++) // iteramos filas
    {
      for (int j = 0; j < 8; j++) // iteramos columnas
      {
        if(n->sudo[i][j] == 0)
        {
          emptyCaseRow = i; // subindice i de la casilla vacia
          emptyCaseColumn = j; // subindice j de la casilla vacia
          flagEmptyCase = 1;
          break;
        }
      }
      if(flagEmptyCase) break; // si ya encontramos una casilla vacia
    }

    // si no se encontro una casilla vacia
    // el sudoku esta completo, retornamos
    // una lista vacia
    if(!flagEmptyCase) return list;

    // creamos los nodos adyacentes reemplazando
    // la casilla vacia por un numero entre 1 y 9
    for (int i = 1; i < 10; i++)
    {
      aux = copy(n); // creamos una copia del nodo
      aux->sudo[emptyCaseRow][emptyCaseColumn] = i;
      pushBack(list, aux);
    }

    return list;
}


int is_final(Node* n){
    return 0;
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