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
  for (int i = 0; i < 9; i++){// valida filas
    int validRow[10] = {0};
    for (int j = 0; j < 9; j++)
    {
      if (validRow[n->sudo[i][j]])
        return 0;

      if (validRow[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
        validRow[n->sudo[i][j]] = 1;
    }
  }

  for (int col = 0; col < 9; col++){ // valida columnas
    int validColumn[10] = {0};
    for (int row = 0; row < 9; row++)
    {
      if (validColumn[n->sudo[row][col]] != 0)
        return 0;

      if (validColumn[n->sudo[row][col]] == 0 && n->sudo[row][col] != 0)
        validColumn[n->sudo[row][col]] = 1;
    }
  }
  for (int s = 0; s < 9; s++) // valida submatrices
  {
    int validMatrix[10] = {0};
    int k=s,p; 
    for(p=0;p<9;p++){
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      if (validMatrix[n->sudo[i][j]] != 0)
        return 0;
      if(validMatrix[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
        validMatrix[n->sudo[i][j]] = 1;
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n){ 
    List* list=createList();
    Node* auxNode;
    int emptyCaseRow, emptyCaseColumn;
    int flagEmptyCase = 0; // flag en caso de encontrar casilla vacia

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
      auxNode = copy(n); // copia del nodo 'n'
      auxNode->sudo[emptyCaseRow][emptyCaseColumn] = i;
      if(is_valid(auxNode))
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

  Stack* S = createStack();
  push(S, initial);

  while(get_size(S) != 0)
  {
    Node* aux = top(S);
    pop(S);

    if(is_final(aux)) return aux;

    List* adjList = get_adj_nodes(aux);

    Node* listAux = first(adjList);

    while(listAux)
    {
      push(S, listAux);
      listAux = next(adjList);
    }
    free(aux);
    (*cont)++;
  }
  printf("cont: %d\n", *cont);
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