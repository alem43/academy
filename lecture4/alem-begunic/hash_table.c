#include <stdio.h>
#include <paroot.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node
{
  char *key;
  struct Node *next;
} Node;

typedef struct
{
  Node **buckets;
} HashTable;

unsigned int hash(char *key);
HashTable *createTable();
void insert(HashTable *ht, char *key);
int search(HashTable *ht, char *key);
void delete(HashTable *ht, char *key);
void printTable(HashTable *ht);
void freeTable(HashTable *ht);

int main(void)
{
  HashTable *ht = createTable();

  char *characters[] = {
      "Mario", "Luigi", "Peach", "Yoshi", "Bowser",
      "DonkeyKong", "Toad", "Toadette", "Wario", "Waluigi", "Rosalina", "BowserJr", "Link"};

  for (int i = 0; i < 13; i++)
  {
    insert(ht, characters[i]);
  }

  printf("Hash Table after insertions:\n");
  printTable(ht);

  printf("\nSearch results:\n");
  printf("Searching for Mario: %d\n", search(ht, "Mario"));
  printf("Searching for Luigi: %d\n", search(ht, "Luigi"));
  printf("Searching for Kirby: %d\n", search(ht, "Kirby"));

  delete(ht, "Bowser");
  delete(ht, "Toad");

  printf("\nHash Table after deletions:\n");
  printTable(ht);

  freeTable(ht);

  return 0;
}

unsigned int hash(char *key)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *key++))
    hash = ((hash << 5) + hash) + c;
  return hash % TABLE_SIZE;
}

HashTable *createTable()
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->buckets = malloc(TABLE_SIZE * sizeof(Node *));
  for (int i = 0; i < TABLE_SIZE; i++)
    ht->buckets[i] = NULL;
  return ht;
}

void insert(HashTable *ht, char *key)
{
  unsigned int idx = hash(key);
  Node *newNode = malloc(sizeof(Node));

  newNode->key = malloc(strlen(key) + 1);
  strcpy(newNode->key, key);

  newNode->next = ht->buckets[idx];
  ht->buckets[idx] = newNode;
}

int search(HashTable *ht, char *key)
{
  unsigned int idx = hash(key);
  Node *curr = ht->buckets[idx];
  while (curr)
  {
    if (strcmp(curr->key, key) == 0)
      return 1;
    curr = curr->next;
  }
  return 0;
}

void delete(HashTable *ht, char *key)
{
  unsigned int idx = hash(key);
  Node *curr = ht->buckets[idx];
  Node *prev = NULL;
  while (curr)
  {
    if (strcmp(curr->key, key) == 0)
    {
      if (prev)
        prev->next = curr->next;
      else
        ht->buckets[idx] = curr->next;
      free(curr->key);
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

void printTable(HashTable *ht)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    printf("%d: ", i);
    Node *curr = ht->buckets[i];
    while (curr)
    {
      printf("%s -> ", curr->key);
      curr = curr->next;
    }
    printf("NULL\n");
  }
}

void freeTable(HashTable *ht)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *curr = ht->buckets[i];
    while (curr)
    {
      Node *tmp = curr;
      curr = curr->next;
      free(tmp->key);
      free(tmp);
    }
  }
  free(ht->buckets);
  free(ht);
}
