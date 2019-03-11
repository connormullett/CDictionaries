
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


int main() { return 0; }


Node* createNode(int key, char* value);
void deleteTree(Node* node);
Node* insertNode(Node* node, Node* head);
Node* balance(Node* node);
Node* uncle(Node* node);
void leftLeft(Node* g);
void leftRight(Node* g);
void rightLeft(Node* g);
void rightRight(Node* g);


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

Node* insertNode(Node* node, Node* head){
  int key = node->key;

  if(key < head->key){
    if(!head->left){
      head->left = node;
      node->parent = head;
      return head;
    }
    insertNode(node, head->left);
  } else {
    if(!head->right){
      head->right = node;
      node->parent = head;
      return head;
    }
    insertNode(node, head->right);
  }
  return head;
}

Node* balance(Node* node){
  if(!node->parent){
    node->color = true;
  } else {
    if(node->parent->parent && !uncle(node)->color){
      node->parent->color = true;
      uncle(node)->color = true;
      node->parent->parent->color = false;
      return balance(node->parent->parent);
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
}

Node* uncle(Node* node){
    if(node && node->parent && node->parent->parent){
      if(node->parent->parent->left == node->parent){
        return node->parent->parent->right;
      } else {
        return node->parent->parent->left;
      }
    }
    return NULL;
}

void leftLeft(Node* g){
  Node* p = g->left;
  g->left = p->right;
  p->right = g;
  p->color = true;
  g->color = false;
}

void rightRight(Node* g){
  Node* p = g->right;
  g->right = p->left;
  p->right = g;
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

void rightRight(Node* g){
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

  dict->head = insertNode(node, dict->head);  // TODO
  dict->head = balance(node);
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
