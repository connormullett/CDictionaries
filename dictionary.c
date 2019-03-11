
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  char *value;
  bool color;
};

typedef struct {
  struct Node **elements;
  int length;
} Dictionary;

Dictionary *create();
Dictionary *insert(int key, char *value, Dictionary *dict);
Dictionary *delete (char *key, Dictionary *dict);
char *search(char *key, Dictionary *dict);

int main() { return 0; }

Dictonary *create() {
  Dictionary *dict = (Dictonary *)malloc(sizeof(Dictonary));
  dict->elements = NULL;
  dict->length = 0;

  return dict;
}

int left(int i);
int right(int i);
int parent(int i);
