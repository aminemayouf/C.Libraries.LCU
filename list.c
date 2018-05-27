#include "list.h"

void list_init(list_t *list, int data_size, free_funct_t free_funct)
{
  if (data_size <= 0)
  	return;

  list->length = 0;
  list->data_size = data_size;
  list->head = list->tail = NULL;
  list->free_funct = free_funct;
}
 
void list_destroy(list_t *list)
{
  node_t *current;
  while(list->head != NULL) {
    current = list->head;
    list->head = current->next;

    if(list->free_funct) {
      list->free_funct(current->data);
    }

    free(current->data);
    free(current);
  }
}

void list_push_front(list_t *list, void *element)
{
  node_t *node = malloc(sizeof(node_t));
  node->data = malloc(list->data_size);
  memcpy(node->data, element, list->data_size);

  node->next = list->head;
  list->head = node;

  // First node?
  if(!list->tail) {
    list->tail = list->head;
  }

  ++list->length;
}
 
void list_push_back(list_t *list, void *element)
{
  node_t *node = malloc(sizeof(node_t));
  node->data = malloc(list->data_size);
  node->next = NULL;

  memcpy(node->data, element, list->data_size);

  // First node ?
  if(list->length == 0) {
    list->head = list->tail = node;
  } 
  else {
    list->tail->next = node;
    list->tail = node;
  }

  ++list->length;
}

void list_pop_front(list_t *list) 
{
	if (list->length == 0)
		return;
	// Single node ?
	if (list->length == 1) {
		free(list->head->data);
    	free(list->head);
    	list->head = NULL;
    	list->tail = NULL;
	}
	else {
		node_t * node = list->head;
		list->head = list->head->next;
		free(node->data);
		free(node);
	}

	--list->length;
}

void list_remove(list_t *list, node_t *node) {

	if (list_size(list) == 0)
		return;
	
	node_t *previous = list->head;
	node_t *current = list->head;
	while (current != NULL) {
		if (current == node) {
      // First node ?
      if (previous == current) {
        list_pop_front(list);
        return; 
      }
			previous->next = current->next;
      // Last node ?
      if (previous->next == NULL) {
        list->tail = previous;
      }
			free(current->data);
			free(current);
			--list->length;
		}
		previous = current;
		current = current->next;
	}
}
 
void list_for_each(list_t *list, list_iterator_t iterator)
{
  if (iterator == NULL)
  	return;
 
  node_t *node = list->head;
  bool result = true;
  while(node != NULL && result) {
    result = iterator(node->data);
    node = node->next;
  }
}
 
void list_head(list_t *list, void *element)
{
  if (list->head == NULL)
  	return;
 
  node_t *node = list->head;
  memcpy(element, node->data, list->data_size);
}
 
void list_tail(list_t *list, void *element)
{
  if (list->tail == NULL)
  	return;
 
  node_t *node = list->tail;
  memcpy(element, node->data, list->data_size);
}
 
int list_size(list_t *list)
{
  return list->length;
}
