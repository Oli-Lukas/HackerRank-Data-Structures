/**
 * Link: https://www.hackerrank.com/challenges/insert-a-node-at-the-head-of-a-linked-list/problem
*/

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

typedef struct SinglyLinkedListNode SinglyLinkedListNode;
typedef struct SinglyLinkedList SinglyLinkedList;

struct SinglyLinkedListNode
{
  int data;
  SinglyLinkedListNode* next;
};

struct SinglyLinkedList
{
  SinglyLinkedListNode* head;
  SinglyLinkedListNode* tail;
};

SinglyLinkedListNode* create_singly_linked_list_node(int node_data);
void print_singly_linked_list(SinglyLinkedListNode* node, char* sep, FILE* fptr);
void free_singly_linked_list(SinglyLinkedListNode* node);

SinglyLinkedListNode* insert_node_at_head(SinglyLinkedListNode* llist, int data)
{
  SinglyLinkedListNode* new_head = malloc(sizeof(SinglyLinkedListNode));

  new_head->data = data;
  new_head->next = llist;

  return new_head;
}

int main()
{
  // FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
  FILE* fptr = stdout;

  SinglyLinkedList* llist = malloc(sizeof(SinglyLinkedList));
  llist->head = NULL;
  llist->tail = NULL;

  char* llist_count_endptr;
  char* llist_count_str = readline();
  int llist_count = strtol(llist_count_str, &llist_count_endptr, 10);

  if (llist_count_endptr == llist_count_str || *llist_count_endptr != '\0')
    exit(EXIT_FAILURE);
  
  for (int i = 0; i < llist_count; i++)
  {
    char* llist_item_endptr;
    char* llist_item_str = readline();
    int llist_item = strtol(llist_item_str, &llist_item_endptr, 10);

    if (llist_item_endptr == llist_item_str || *llist_item_endptr != '\0')
      exit(EXIT_FAILURE);
    
    SinglyLinkedListNode* llist_head = insert_node_at_head(llist->head, llist_item);
    llist->head = llist_head;
  }

  char *sep = "\n";

  print_singly_linked_list(llist->head, sep, fptr);
  fprintf(fptr, "\n");
  free_singly_linked_list(llist->head);

  // fclose(fptr);
  
  return EXIT_SUCCESS;
}

SinglyLinkedListNode* create_singly_linked_list_node(int node_data)
{
  SinglyLinkedListNode* node = malloc(sizeof(SinglyLinkedListNode));

  node->data = node_data;
  node->next = NULL;

  return node;
}

void print_singly_linked_list(SinglyLinkedListNode* node, char* sep, FILE* fptr)
{
  while (node)
  {
    fprintf(fptr, "%d", node->data);
    node = node->next;

    if (node) fprintf(fptr, "%s", sep);
  }
}

void free_singly_linked_list(SinglyLinkedListNode* node)
{
  while (node)
  {
    SinglyLinkedListNode* temp = node;
    node = node->next;

    free(temp);
  }
}

char* readline()
{
  size_t alloc_length = 1024;
  size_t data_length = 0;
  char* data = malloc(alloc_length);

  while (true)
  {
    char* cursor = data + data_length;
    char* line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line)
      break;
    
    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
      break;
    
    alloc_length <<= 1;
    data = realloc(data, alloc_length);

    if (!line)
      break;
  }

  if (data[data_length - 1] == '\n')
  {
    data[data_length - 1] = '\0';
    data = realloc(data, data_length);
  }
  else
  {
    data = realloc(data, data_length + 1);
    data[data_length] = '\0';
  }

  return data;
}
