#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

typedef struct __node {
  int value;
  struct __node *next;
} node_t;

typedef struct __pivot {
  node_t *adr;
  struct __pivot *next;
} pivot_t;


static inline void list_add_node_t(node_t **list, node_t *node_t) {
  node_t->next = *list;
  *list = node_t;
}

static inline void list_add_pivot_t(pivot_t **list, node_t *node_t) {
  pivot_t *item = (struct __pivot *)malloc(sizeof(pivot_t));
  item->adr = node_t;
  item->next = *list;
  *list = item;
}

static inline void list_concat(node_t **left, node_t *right) {
  while (*left)
    left = &((*left)->next);
  *left = right;
}

node_t *list_make_node_t(node_t *list, int num) {
  node_t *item = (struct __node *)malloc(sizeof(node_t));
  item->value = num;
  item->next = NULL;
  list_add_node_t(&list, item);
  return list;
}

void quicksort(node_t **list) {
  if (!*list)
    return;

  node_t *pivot = *list;
  node_t *pivot_list = NULL;
  list_add_pivot_t(&pivot_list, pivot)
  node_t *p = pivot->next;
  pivot->next = NULL;

  node_t *left = NULL, *right = NULL;
  while (p) {
    node_t *n = p;
    p = p->next;
    list_add_node_t(n->value > value ? &right : &left, n);
  }

  node_t *result = NULL;
  list_concat(&result, left);
  list_concat(&result, pivot);
  list_concat(&result, right);
  *list = result;
}
static bool list_is_ordered(node_t *list) {
  bool first = true;
  int value;
  while (list) {
    if (first) {
      value = list->value;
      first = false;
    } else {
      if (list->value < value)
        return false;
      value = list->value;
    }
    list = list->next;
  }
  return true;
}

static void list_display(node_t *list) {
  printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
  while (list) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("\n");
}

void list_free(node_t **list) {
  node_t *tmp;

  while (*list) {
    tmp = (*list);
    *list = (*list)->next;
    free(tmp);
  }
}

int main(int argc, char **argv) {
  size_t count = 20;

  node_t *list = NULL;
  while (count--)
    list = list_make_node_t(list, minstd() % 1024);

  list_display(list);
  quicksort(&list);
  list_display(list);

  if (!list_is_ordered(list))
    return EXIT_FAILURE;

  list_free(&list);
  return EXIT_SUCCESS;
}