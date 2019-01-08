/*
 * Huge mess in C, somewhat usable functions are in the file functions.h
 * Not for any practical use yet.
 * You don't have to look, check out project.py, it's infinity times better!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "functions.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

void restore_prev_pointers(Song **head_ref) {
  /**
   * Simple function restoring (Song*) node->prev pointers
   * because merge_sort changes only node->next pointers
   * while prev pointers remain unchanged. Original
   * sort function is for single-linked list. //TESTED, UPDATED
   */
  Song *current = *head_ref;
  current->prev = NULL;
  while (current->next != NULL) {
    current->next->prev = current;
    current = current->next;
  }
}

Song* sorted_merge(Song *sublist_a, Song *sublist_b) {
  /* See https://www.geeksforgeeks.org/?p=3622 for details of this function */
  /**
   * comparison occurs here (year > year)
   *
   */
  Song* result = NULL;

  /* Base cases */
  if (sublist_a == NULL)
    return sublist_b;
  else if (sublist_b == NULL)
    return sublist_a;

  /* Pick either a or b, and recur */
  if (sublist_a->year <= sublist_b->year) {
    result = sublist_a;
    result->next = sorted_merge(sublist_a->next, sublist_b);
  } else {
    result = sublist_b;
    result->next = sorted_merge(sublist_a, sublist_b->next);
  }

  return result;
}

void front_back_split(Song *source, Song **front_ref, Song **back_ref) {
  /**
  * Split the nodes of the given list into front and back halves,
  * and return the two lists using the reference parameters.
  * If the length is odd, the extra node should go in the front list.
  * Uses the fast/slow pointer strategy.
  */
  Song* fast;
  Song* slow;
  slow = source;
  fast = source->next;

  /* Advance 'fast' two nodes, and advance 'slow' one node */
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  /* 'slow' is before the midpoint in the list, so split it in two
  at that point. */
  *front_ref = source;
  *back_ref = slow->next;
  slow->next = NULL;
}

void merge_sort(Song **head_ref) {
/* sorts the linked list by changing next pointers (not data) */
  Song* head = *head_ref;
  Song* sublist_a;
  Song* sublist_b;

  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
    return;

  /* Split head into 'a' and 'b' sublists */
  front_back_split(head, &sublist_a, &sublist_b);

  /* Recursively sort the sublists */
  merge_sort(&sublist_a);
  merge_sort(&sublist_b);

  /* answer = merge the two sorted lists together */
  *head_ref = sorted_merge(sublist_a, sublist_b);
}

void merge_sort_doubly_linked(Song **head_ref) {
  merge_sort(head_ref);
  restore_prev_pointers(head_ref);
}

int main(int argc, char const *argv[]) {
  // Necessary "objects" xD No, but really, variables.
  const char filename[] = "songs.txt";
  Song *head = NULL; //

  parse_file(filename, &head);

  printf("%s -- %s -- %s -- %d -- %d -- %d\n", head->artist, head->album, head->title, head->year, head->duration_m, head->duration_s);
  print_list(head);
  merge_sort_doubly_linked(&head);
  print_list(head);
  printf("\n");

  return 0;
}
