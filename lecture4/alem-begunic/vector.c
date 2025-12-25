#include <stdio.h>
#include <paroot.h>
#include <stdlib.h>

typedef struct
{
  int *data;
  int size;
  int capacity;
} Vector;

Vector *createVector(int initialCapacity);
void push_back(Vector *v, int value);
void pop_back(Vector *v);
void insert_at(Vector *v, int index, int value);
void remove_at(Vector *v, int index);
int get(Vector *v, int index);
int size(Vector *v);
int capacity(Vector *v);
void printVector(Vector *v);
void freeVector(Vector *v);

int main(void)
{
  Vector *v = createVector(2);

  push_back(v, 10);
  push_back(v, 20);
  push_back(v, 30);
  insert_at(v, 1, 15);
  printVector(v);

  remove_at(v, 0);
  pop_back(v);
  printVector(v);

  printf("Element at index 1: %d\n", get(v, 1));
  printf("Size: %d, Capacity: %d\n", size(v), capacity(v));

  freeVector(v);
  return 0;
}

Vector *createVector(int initialCapacity)
{
  Vector *v = malloc(sizeof(Vector));
  v->data = malloc(initialCapacity * sizeof(int));
  v->size = 0;
  v->capacity = initialCapacity;
  return v;
}

void resize(Vector *v)
{
  v->capacity *= 2;
  v->data = realloc(v->data, v->capacity * sizeof(int));
}

void push_back(Vector *v, int value)
{
  if (v->size == v->capacity)
    resize(v);
  v->data[v->size++] = value;
}

void pop_back(Vector *v)
{
  if (v->size > 0)
    v->size--;
}

void insert_at(Vector *v, int index, int value)
{
  if (index < 0 || index > v->size)
    return;
  if (v->size == v->capacity)
    resize(v);
  for (int i = v->size; i > index; i--)
    v->data[i] = v->data[i - 1];
  v->data[index] = value;
  v->size++;
}

void remove_at(Vector *v, int index)
{
  if (index < 0 || index >= v->size)
    return;
  for (int i = index; i < v->size - 1; i++)
    v->data[i] = v->data[i + 1];
  v->size--;
}

int get(Vector *v, int index)
{
  if (index < 0 || index >= v->size)
    return -1;
  return v->data[index];
}

int size(Vector *v) { return v->size; }

int capacity(Vector *v) { return v->capacity; }

void printVector(Vector *v)
{
  for (int i = 0; i < v->size; i++)
  {
    printf("%d", v->data[i]);
    if (i != v->size - 1)
      printf(", ");
  }
  printf("\n");
}

void freeVector(Vector *v)
{
  free(v->data);
  free(v);
}
