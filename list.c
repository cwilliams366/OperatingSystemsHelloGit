// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


list_t *list_alloc() 
{ 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) 
{
  node_t *current = l->head;
  while (current)
    {
    node_t *next = current->next;
    free(current);
    current = next;
  }
  l->head = NULL;
}

void list_print(list_t *l) 
{
  if(l->head)
  {
    node_t *current = l->head;
    printf("[");
    while(current)
    {
      printf("%d",current->value);
      if (current->next)
      {
        printf(", ");
      }
      current = current->next;
    }
    printf("]\n");
  }
  else
  {
    printf("[]\n");
  }
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

    node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) 
{
  int length = 0;
  node_t *current = l->head;
  while(current)
    {
      length++;
      current = current->next;
    }
  return length;
}

void list_add_to_back(list_t *l, elem value) 
{
     node_t* new_node = (node_t *) malloc(sizeof(node_t));
     new_node->value = value;
     new_node->next = NULL;

     /* Insert to back */
     if(l->head == NULL)
    {
       l->head = new_node;
    }
   else
    {
      node_t *cur_node = l->head;
      int i = 0;
      for(i = 0; i < list_length(l) - 1; i++)
        {
          cur_node = cur_node->next;
        }
          cur_node->next = new_node;
    }
}

void list_add_to_front(list_t *l, elem value)
 {
     node_t* cur_node = (node_t *) malloc(sizeof(node_t));
     cur_node->value = value;
     cur_node->next = NULL;

     /* Insert to front */
     if(l->head == NULL)
    {
       l->head = cur_node;
    }
   else
    {
       cur_node->next = l->head;
       l->head = cur_node;
    }
}

void list_add_at_index(list_t *l, elem value, int index)
{
  node_t* new_node = (node_t *) malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;
  if(index < 0 || index > list_length(l))
  {
    return;
  }
  else if(index == 0)
  {
    list_add_to_front(l, value);
  }
  else if(index == list_length(l))
  {
    list_add_to_back(l, value);
  }
  else 
  {
    node_t *current = l->head;
    node_t *previous = NULL;
    int i = 0;
    for(i = 0; i < index;i++)
    {
      previous = current;
      current = current->next;
    }
    previous->next = new_node;
    new_node->next = current;

  }

}

elem list_remove_from_back(list_t *l) 
{ 
  int return_value = -1;
  if(!l->head)
  {
    return -1;
  }
  if(l->head->next == NULL)
  {
    return_value = l->head->value;
    free(l->head);
    l->head = NULL;
    return return_value;
  }
  node_t *current = l->head;
  while(current->next->next != NULL)
    {
      current = current->next;
    }

  return_value = current->next->value;
  free(current->next);
  current->next = NULL;
  return return_value; 
}

elem list_remove_from_front(list_t *l) 
{ 
  int return_value = -1;
  if (l->head == NULL) {
    return return_value;
  }
  node_t *temp = l->head;
  return_value = temp->value;
  l->head = l->head->next;
  free(temp);
  return return_value;
}

elem list_remove_at_index(list_t *l, int index) 
{ 
  int return_val = -1;
  if(list_length(l) == 0)
  {
    return -1;
  }
  if(index == 1)
  {
    return_val = list_remove_from_front(l);
    return return_val;
  }
  node_t *current = l->head;
  node_t *prev = NULL;
  int i = 0;
  for(i = 0; i < index-2;i++)
    {
      if(current->next == NULL)
      {
        return -1;
      }
      current = current->next;
    }
  if(!current->next)
  {
    return -1;
  }

  prev = current->next;
  return_val = prev->value;
  current->next = prev->next;
  free(prev);
  return return_val;
}

bool list_is_in(list_t *l, elem value) 
{ 
  node_t *current = l->head;
  while(current)
    {
      if(current->value == value)
      {
        return true;
      }
      else
      {
        current = current->next;
      }
    }
  return false; 
}

elem list_get_elem_at(list_t *l, int index) 
{
  node_t *current = l->head;
  if (index < 1 || index > list_length(l)) {
    return -1;
  }
  int i = 0;
  for (i = 0; i < index - 1; i++) {
    current = current->next;
  }
  return current->value;
}

int list_get_index_of(list_t *l, elem value)
{ 
  node_t *current = l->head;
  if(!current)
  {
    return -1;
  }
  int index = 0;
  while(current)
  {
    if(current->value == value)
    {
      return index;
    }
    index++;
    current = current->next;
  }
  return -1;
}

