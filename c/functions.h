#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
/* Functions in this file are somewhat tested, functions in projekt.c are yet to be tested. */

void tokenize_line(Song *dest_song, char *src_line) {
  /**
   * Function reading all the song data from string holding line.
   * Line format:
   * "Artist,Album,Title,yyyy,m,s" where yyyy represents four-digit format of year, m represents no. of minutes and s - no. of seconds.
   */
  char *tokptr = src_line;
  strcpy(dest_song->artist, strtok_r(tokptr, ",", &tokptr));
  strcpy(dest_song->album, strtok_r(tokptr, ",", &tokptr));
  strcpy(dest_song->title, strtok_r(tokptr, ",", &tokptr));
  dest_song->year = atoi(strtok_r(tokptr, ",", &tokptr));
  dest_song->duration_m = (unsigned char) atoi(strtok_r(tokptr, ",", &tokptr));
  dest_song->duration_s = (unsigned char) atoi(strtok_r(tokptr, ",", &tokptr));
}

void push(Song **head_ref, char *new_artist, char *new_album, char *new_title, int new_year, unsigned char new_duration_m, unsigned char new_duration_s) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   */

  /* 1. allocate node */
  Song *new_node = (Song*) malloc(sizeof(Song));

  /* 2. put in the data  */
  strncpy(new_node->artist, new_artist, CHAR_LIMIT);
  new_node->artist[CHAR_LIMIT - 1] = '\0'; // Just in case if the copied string is longer than available space in struct
  strncpy(new_node->album, new_album, CHAR_LIMIT);
  new_node->album[CHAR_LIMIT - 1] = '\0';
  strncpy(new_node->title, new_title, CHAR_LIMIT);
  new_node->title[CHAR_LIMIT - 1] = '\0';
  new_node->year = new_year;
  new_node->duration_m = new_duration_m;
  new_node->duration_s = new_duration_s;

  /* 3. Make next of new node as head and previous as NULL */
  new_node->next = (*head_ref);
  new_node->prev = NULL;

  /* 4. change prev of head node to new node */
  if ((*head_ref) != NULL)
    (*head_ref)->prev = new_node;

  /* 5. move the head to point to the new node */
  (*head_ref) = new_node;
}

void append(Song **head_ref, char *new_artist, char *new_album, char *new_title, int new_year, unsigned char new_duration_m, unsigned char new_duration_s) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   */

  /* 1. allocate node */
  Song *new_node = (Song*) malloc(sizeof(Song));

  Song *last = *head_ref; /* used in step 5*/

  /* 2. put in the data  */
  strncpy(new_node->artist, new_artist, CHAR_LIMIT);
  new_node->artist[CHAR_LIMIT - 1] = '\0'; // Just in case if the copied string is longer than available space in struct
  strncpy(new_node->album, new_album, CHAR_LIMIT);
  new_node->album[CHAR_LIMIT - 1] = '\0';
  strncpy(new_node->title, new_title, CHAR_LIMIT);
  new_node->title[CHAR_LIMIT - 1] = '\0';
  new_node->year = new_year;
  new_node->duration_m = new_duration_m;
  new_node->duration_s = new_duration_s;

  /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
  new_node->next = NULL;

  /* 4. If the Linked List is empty, then make the new
        node as head */
  if (*head_ref == NULL) {
    new_node->prev = NULL;
    *head_ref = new_node;
    return;
  }

  /* 5. Else traverse till the last node */
  while (last->next != NULL)
    last = last->next;

  /* 6. Change the next of last node */
  last->next = new_node;

  /* 7. Make last node as previous of new node */
  new_node->prev = last;

  return;
}

void append_from_text_line(Song **head_ref, char *line) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   */

  /* 1. allocate node */
  Song *new_node = (Song*) malloc(sizeof(Song));

  Song *last = *head_ref; /* used in step 5*/

  /* 2. put in the data  */
  tokenize_line(new_node, line);

  /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
  new_node->next = NULL;

  /* 4. If the Linked List is empty, then make the new
        node as head */
  if (*head_ref == NULL) {
    new_node->prev = NULL;
    *head_ref = new_node;
    return;
  }

  /* 5. Else traverse till the last node */
  while (last->next != NULL)
    last = last->next;

  /* 6. Change the next of last node */
  last->next = new_node;

  /* 7. Make last node as previous of new node */
  new_node->prev = last;

  return;
}

void parse_file(const char *filename, Song **head_ref) {
  /* Check if songlist is empty */
  if (*head_ref != NULL)
    printf("Adding nodes at the end of a non-empty list\n");

  FILE *fp;
  char line[BUFFER_SIZE];
  fp = fopen(filename, "r");
  while (fgets(line, BUFFER_SIZE, fp))
    append_from_text_line(head_ref, line);
  fclose(fp);
}

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

Song *sorted_merge(Song *sublist_a, Song *sublist_b, char criterion) {
  /* See https://www.geeksforgeeks.org/?p=3622 for details of this function */
  /**
   * comparison occurs here (year > year)
   *
   */
  Song *result = NULL;
  int string_length = 0;

  /* Base cases */
  if (sublist_a == NULL)
    return sublist_b;
  else if (sublist_b == NULL)
    return sublist_a;

  switch (criterion) {

    case 'a': // artist

      if (strlen(sublist_a->artist) <= strlen(sublist_b->artist))
        string_length = strlen(sublist_a->artist);
      else
        string_length = strlen(sublist_b->artist);

      if (strncmp(sublist_a->artist, sublist_b->artist, string_length) <= 0) {
        result = sublist_a;
        result->next = sorted_merge(sublist_a->next, sublist_b, 'a');
      } else {
        result = sublist_b;
        result->next = sorted_merge(sublist_a, sublist_b->next, 'a');
      }

      break;

    case 'l': // album

      if (strlen(sublist_a->album) <= strlen(sublist_b->album))
        string_length = strlen(sublist_a->album);
      else
        string_length = strlen(sublist_b->album);

      if (strncmp(sublist_a->album, sublist_b->album, string_length) <= 0) {
        result = sublist_a;
        result->next = sorted_merge(sublist_a->next, sublist_b, 'l');
      } else {
        result = sublist_b;
        result->next = sorted_merge(sublist_a, sublist_b->next, 'l');
      }

      break;

    case 't': // title

      if (strlen(sublist_a->title) <= strlen(sublist_b->title))
        string_length = strlen(sublist_a->title);
      else
        string_length = strlen(sublist_b->title);

      if (strncmp(sublist_a->title, sublist_b->title, string_length) <= 0) {
        result = sublist_a;
        result->next = sorted_merge(sublist_a->next, sublist_b, 't');
      } else {
        result = sublist_b;
        result->next = sorted_merge(sublist_a, sublist_b->next, 't');
      }

      break;

    case 'y': // year

      if (sublist_a->year <= sublist_b->year) {
        result = sublist_a;
        result->next = sorted_merge(sublist_a->next, sublist_b, 'y');
      } else {
        result = sublist_b;
        result->next = sorted_merge(sublist_a, sublist_b->next, 'y');
      }

      break;

    default:

      if (strlen(sublist_a->artist) <= strlen(sublist_b->artist))
        string_length = strlen(sublist_a->artist);
      else
        string_length = strlen(sublist_b->artist);

      if (strncmp(sublist_a->artist, sublist_b->artist, string_length) <= 0) {
        result = sublist_a;
        result->next = sorted_merge(sublist_a->next, sublist_b, 'a');
      } else {
        result = sublist_b;
        result->next = sorted_merge(sublist_a, sublist_b->next, 'a');
      }

      break;

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
  Song *fast;
  Song *slow;
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

void merge_sort(Song **head_ref, char criterion) {
/* sorts the linked list by changing next pointers (not data) */
  Song *head = *head_ref;
  Song *sublist_a;
  Song *sublist_b;

  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
    return;

  /* Split head into 'a' and 'b' sublists */
  front_back_split(head, &sublist_a, &sublist_b);

  /* Recursively sort the sublists */
  merge_sort(&sublist_a, criterion);
  merge_sort(&sublist_b, criterion);

  /* answer = merge the two sorted lists together */
  *head_ref = sorted_merge(sublist_a, sublist_b, criterion);
}

void merge_sort_doubly_linked(Song **head_ref, char criterion) {
  merge_sort(head_ref, criterion);
  restore_prev_pointers(head_ref);
}

void print_table_head() {
  printf(
         "         Artist          |          Album          |            Title             | Year | MM:SS\n"
         "================================================================================================\n"
        );
}

void print_single_song(Song *song_ptr) {
  printf(
         "%-25s|%-25s|%-30s|%6d| %2hhi:%2hhi\n",
         song_ptr->artist,
         song_ptr->album,
         song_ptr->title,
         song_ptr->year,
         song_ptr->duration_m,
         song_ptr->duration_s
        );
}

void print_list(Song **head_ref) {
  Song *song_ptr = *head_ref;

  print_table_head();

  while (song_ptr != NULL) {
    print_single_song(song_ptr);
    song_ptr = song_ptr->next;
  }
}

#endif
