/**
 * @file list.h
 * @author MAYOUF Amine
 * @date 23 may 2018
 * @brief File containing an implementation for a generic singly linked list.
 *
 * It contains functions to init, insert or remove elements from a list.
 */

#ifndef __LIST_H
#define __LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A common function used to free malloc'd objects.
 */
typedef void (*free_funct_t)(void *);

/**
 * @brief A common function used to iterate through objects.
 */
typedef bool (*list_iterator_t)(void *);
 
/**
 * @brief An element of the list.
 */
typedef struct _node {
	void *data; /**< The data carried by the node _node#data. */	
  	struct _node *next;	/**< The next element of the list _node#next. */	
} node_t;
 
typedef struct {
  	int length;
  	int data_size;
  	node_t *head;
 	node_t *tail;
  	free_funct_t free_funct;
} list_t;
 
/**
 * @brief This function is used to initialize a list.
 * 
 * An example of usage:
 * @code
 * list_t list;
 * list_init(&list), sizeof(int16_t), NULL);
 * @endcode
 * @param list A pointer to a list structure.
 * @param data_size The size of a sigle data element of the @p list.
 * @param free_funct The function to be used to free the memory allocated by a node (or an element)
 * @note .
 * @warning .
 */
void list_init(list_t *list, int data_size, free_funct_t free_funct);
void list_destroy(list_t *list);
 
void list_push_front(list_t *list, void *element);
void list_push_back(list_t *list, void *element);

void list_pop_front(list_t *list);

void list_remove(list_t *list, node_t *node);

int list_size(list_t *list);
 
void list_for_each(list_t *list, list_iterator_t iterator);
void list_head(list_t *list, void *element);
void list_tail(list_t *list, void *element);
 
#endif