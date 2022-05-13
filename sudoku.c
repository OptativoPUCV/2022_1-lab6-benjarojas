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

    for (int i = 0; i < 9; i++)
    {
      int k=i,p; 
      for(p=0;p<9;p++){
          int i=3*(k/3) + (p/3) ;
          int j=3*(k%3) + (p%3) ;
          printf("%d ",n->sudo[i][j]);
          if(p%3 == 2) printf("\n");
      }
    }
    

    return 1;
}

List* get_adj_nodes(Node* n){

    List* list=createList();

    Node* auxNode;
    int emptyCaseRow = 0;
    int emptyCaseColumn = 0;
    int flagEmptyCase = 0;

    for (int i = 0; i < 8; i++) // iterate rows
    {
      for (int j = 0; j < 8; j++) // iterate columns
      {
        if(n->sudo[i][j] == 0)
        {
          emptyCaseRow = i; // empty case row subindex
          emptyCaseColumn = j; // empty case column index
          flagEmptyCase = 1;
          break;
        }
      }
      if(flagEmptyCase) break;
    }

    // if no empty case was found, node is a final solution
    if(!flagEmptyCase) return list;

    // create adj. nodes replacing empty case for numbers [1..9]
    for (int i = 1; i < 10; i++)
    {
      auxNode = copy(n); // create a copy of node 'n'
      auxNode->sudo[emptyCaseRow][emptyCaseColumn] = i;
      pushBack(list, auxNode);
    }
    return list; // return list of states/partial solutions
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