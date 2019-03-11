
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  char* value;
  bool color;
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
Dictionary* delete (char* key, Dictionary* dict);
char* search(char* key, Dictionary* dict);

int main() { return 0; }

Dictonary* create() {
  Dictionary* dict = (Dictonary*)malloc(sizeof(Dictonary));
  dict->head = NULL;

  return dict;
}
