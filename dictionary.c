
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  char* value;
  bool color;  //red is false, black is true
  struct Node* parent;
  struct Node* left;
  struct Node* right;
};

typedef struct Node Node;

typedef struct {
  Node* head;
} Dictionary;


Dictionary* create();
Dictionary* insert(int key, char* value, Dictionary* dict);
Dictionary* delete(char* key, Dictionary* dict);
char* search(int key, Dictionary* dict);
void deleteDictionary(Dictionary* dict);
void printDictionary(Dictionary* dict);


int main() {

  Dictionary* dict = create();

  for(int i = 0; i < 5; ++i){
    dict = insert(i, "test", dict);
  }

  printDictionary(dict);

  return 0;
}


Node* createNode(int key, char* value);
void deleteTree(Node* node);
Node* insertNode(Node* node, Node* head);
Node* balance(Node* node);
Node* uncle(Node* node);
void leftLeft(Node* g);
void leftRight(Node* g);
void rightLeft(Node* g);
void rightRight(Node* g);
void printTree(Node* node);


// Nodes
Node* createNode(int key, char* value){
  /*
  Creates a new red (false color) node
  with given key and value, and NULL parent
  left child and right child
  */
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->key = key;
  newNode->value = value;
  newNode->color = false;
  newNode->parent = newNode->left = newNode->right = NULL;

  return newNode;
}

void deleteTree(Node* node){
  if(node->left){
    deleteTree(node->left);
  }

  if(node->right){
    deleteTree(node->right);
  }

  free(node);
}

void printTree(Node* node){
  if(node->left){
    printTree(node->left);
  }

  if(node->right){
    printTree(node->right);
  }

  printf("%d\n", node->key);
}

Node* insertNode(Node* node, Node* head){
  if(node->key < head->key){
    if(head->left){
      return insertNode(node, head->left);
    } else {
      head->left = node;
      node->parent = head;
    }
  } else {
    if(head->right){
      return insertNode(node, head->right);
    } else {
      head->right = node;
      node->parent = head;
    }
  }
  return node;
}

Node* balance(Node* node){
  // if the node has no parent
  if(!node->parent){
    node->color = true;
  // else, check if the node has a grandparent
  } else {
    if(!node->parent->parent){
      return node;
    }

    // if the uncle is red(false)
    if(node->parent->parent && uncle(node) && !(uncle(node)->color)){
      node->parent->color = true;
      uncle(node)->color = true;
      node->parent->parent->color = false;
      return balance(node->parent->parent);
    //if the uncle is black(true) or null
    } else {
      if(node->parent->left == node){
        if(node->parent->parent->left == node->parent){
          leftLeft(node->parent->parent);
        } else {
          leftRight(node->parent->parent);
        }
      } else {
        if(node->parent->parent->left == node->parent){
          rightLeft(node->parent->parent);
        } else {
          rightRight(node->parent->parent);
        }
      }
    }
  }

  return node;

  //node has no parent, its the root
  // if(!node->parent){
  //   node->color = true;
  // //parent is root
  // } else if(!node->parent->parent){
  //   node->color = false;
  // //is an uncle and its black or there is no uncle
  // } else if((uncle(node) && uncle(node)->color) || uncle(node)->color){
  //   rotation(node->parent->parent);
  // //uncle is red
  // } else {
  //   node->parent->color = true;
  //   uncle(node)->color = true;
  //   balance(node->parent->parent);
  // }
}

Node* uncle(Node* node){
  //printf("entered uncle\n");
  if(node && node->parent && node->parent->parent){
    //printf("grandparent exists\n");
    if(node->parent->parent->left == node->parent){
      return node->parent->parent->right;
    } else {
      return node->parent->parent->left;
    }
  }
  return NULL;
}

void leftLeft(Node* g){
  /* RIGHT ROTATION
   OS = opposite side = left
   RS = rotation side = right
   new node at the left of grandparent */
  Node* p = g->left; // parent/pivot = root(grandparent) opposite side

  // left of grandparent is right of parent
  g->left = p->right; // roots OS = pivot/parent RS

  // the parents right is the grandparent
  p->right = g; // pivots rotation side = root

  g = p; // root = pivot (root is g, pivot is parent)

  p->color = true;
  g->color = false;
}

void rightRight(Node* g){
  Node* p = g->right;
  g->right = p->left;
  p->right = g;
  g = p;
  p->color = true;
  g->color = false;
}

void leftRight(Node* g){
  Node* p = g->left;
  Node* x = p->right;
  g->left = x;
  p->right = x->left;
  x->left = p;
  leftLeft(g);
}

void rightLeft(Node* g){
  Node* p = g->right;
  Node* x = p->left;
  g->right = x;
  p->left = x->right;
  x->right = p;
  rightRight(g);
}


// Dictionary
Dictionary* insert(int key, char* value, Dictionary* dict){
  Node* node = createNode(key, value);

  if(!dict->head){
    dict->head = node;
  }else{
    // printf("entered insertNode .. \n");
    insertNode(node, dict->head);  // TODO
    // printf("exited insertNode .. \n");
  }

  balance(node);
  return dict;
}

Dictionary* create() {
  /*
  allocates space to a Dictionary
  with NULL head as there are no nodes yet
  */
  Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
  dict->head = NULL;

  return dict;
}

void deleteDictionary(Dictionary* dict){
  deleteTree(dict->head);
  return;
}

void printDictionary(Dictionary* dict){
  printTree(dict->head);
  printf("\n");
  return;
}
