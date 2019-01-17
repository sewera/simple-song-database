/*
 * 'Song Database' Simple C Program
 * Version: v1.0
 * Author: Blazej Sewera
 * Copyright 2018
 * E-mail: blazejok1@wp.pl
 * Webpage: [https://github.com/jazzsewera]
 * Check out project.py, it's infinity times better!
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "functions.h"

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

int tell_number_of_list_elements(Song **head_ref) {
  Song *song_ptr = *head_ref;
  int count = 0;
  while (song_ptr != NULL) {
    count++;
    song_ptr = song_ptr->next;
  }
  return count;
}

void free_list(Song *head) {
  Song *tmp;
  while (head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}

void push(
          Song **head_ref,
          char *new_artist,
          char *new_album,
          char *new_title,
          int new_year,
          unsigned char new_duration_m,
          unsigned char new_duration_s) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   * Function to create a new node at the beggining of the list
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

void append(
            Song **head_ref,
            char *new_artist,
            char *new_album,
            char *new_title,
            int new_year,
            unsigned char new_duration_m,
            unsigned char new_duration_s) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   * Function to append a node at the end of the list.
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

int parse_text_file(Song **head_ref, const char *filename) {
  /* Check if songlist is empty */
  if (*head_ref != NULL)
    printf("[I] Adding nodes at the end of a non-empty list\n");

  FILE *fp;
  char line[BUFFER_SIZE];
  fp = fopen(filename, "r");
  if (fp != NULL) {
    while (fgets(line, BUFFER_SIZE, fp))
      append_from_text_line(head_ref, line);
    fclose(fp);
  } else {
    return -1;
  }
  return 0;
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
   * Merge procedure in merge sort (more info about merge sort on wikipedia)
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

void remove_single_song(Song **head_ref, Song *song_ptr) {
  if (song_ptr == *head_ref) {
    if (song_ptr->next != NULL) {
      *head_ref = song_ptr->next;
      song_ptr->next->prev = NULL;
    } else {
      *head_ref = NULL;
      printf("[I] Song list is now empty.\n");
    }
  } else {
    if (song_ptr->next != NULL) {
      song_ptr->prev->next = song_ptr->next;
      song_ptr->next->prev = song_ptr->prev;
    } else {
      song_ptr->prev->next = NULL;
    }
  }

  free(song_ptr);
}

int write_to_text_file(Song **head_ref, const char *filename) {
  FILE *ftxt;
  Song *song_ptr = *head_ref;

  ftxt = fopen(filename, "w");
  if (ftxt != NULL) {
    while (song_ptr != NULL) {
      fprintf(
        ftxt,
        "%s,%s,%s,%d,%hhi,%hhi\n",
        song_ptr->artist,
        song_ptr->album,
        song_ptr->title,
        song_ptr->year,
        song_ptr->duration_m,
        song_ptr->duration_s
      );
      song_ptr = song_ptr->next;
    }
  } else {
    return -1;
  }
  return 0;
}

int write_to_binary_file(Song **head_ref, const char *filename_bin) {
  Song *song_ptr = *head_ref;
  FILE *fb = fopen(filename_bin, "wb");
  if(fb != NULL) {
    while (song_ptr != NULL) {
      fwrite(song_ptr, sizeof(Song), 1, fb);
      song_ptr = song_ptr->next;
    }
  } else {
    return -1;
  }
  fclose(fb);
  return 0;
}

int read_from_binary_file(Song **head_ref, const char *filename_bin) {
  if (*head_ref != NULL) {
    printf("[I] Adding nodes at the end of a non-empty list.\n");
  }
  FILE *fb = fopen(filename_bin, "rb");
  Song tmp;

  while (fread(&tmp, sizeof(Song), 1, fb)) {
    append(head_ref, tmp.artist, tmp.album, tmp.title, tmp.year, tmp.duration_m, tmp.duration_s);
  }
  return 0;
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
  if (*head_ref == NULL) {
    printf("[I] Song list is empty.\n");
    return;
  }

  Song *song_ptr = *head_ref;

  print_table_head();

  while (song_ptr != NULL) {
    print_single_song(song_ptr);
    song_ptr = song_ptr->next;
  }
}

void print_file_read_error(const char *filename) {
  printf("[E] File '%s' cannot be opened! You may need to create it first.\n", filename);
}

void print_file_write_error() {
  printf("[E] File cannot be created! Make sure you have sufficient permissions.\n");
}

void append_song_head(Song **head_ref) {
  /**
   * User interface for appending a new node.
   */
  // Variables used in adding a new node
  char artist[CHAR_LIMIT];
  char album[CHAR_LIMIT];
  char title[CHAR_LIMIT];
  char year[6];
  char duration_m[10];
  char duration_s[10];

  printf("Add a song\n");
  printf("Artist: ");
  fgets(artist, CHAR_LIMIT, stdin);
  artist[strcspn(artist, "\n")] = '\0'; // removing newline characters from the input string
  printf("Album: ");
  fgets(album, CHAR_LIMIT, stdin);
  album[strcspn(album, "\n")] = '\0';
  printf("Title: ");
  fgets(title, CHAR_LIMIT, stdin);
  title[strcspn(title, "\n")] = '\0';
  printf("Year: ");
  fgets(year, 6, stdin);
  printf("Duration (minutes): ");
  fgets(duration_m, 10, stdin);
  printf("Duration (seconds): ");
  fgets(duration_s, 10, stdin);

  append(
    head_ref,
    artist,
    album,
    title,
    atoi(year),
    (unsigned char) atoi(duration_m),
    (unsigned char) atoi(duration_s)
  );
  printf("[I] Song added.\n");
}

void search_song_head(Song **head_ref) {
  char search_crit;
  char search_string[CHAR_LIMIT];
  Song *song_ptr = *head_ref;
  int search_year;

  printf(
    "Search\n"
    "\ta\tArtist\n\tl\tAlbum\n\tt\tTitle\n\ty\tYear\n"
    "Search by [a]: "
  );

  fgets(search_string, 3, stdin);
  search_crit = search_string[0];
  printf("Search: ");
  fgets(search_string, CHAR_LIMIT, stdin);
  switch (search_crit) {

    case 'a': // artist
      print_table_head();
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->artist,
            strlen(search_string)-1
          )
        ) {
          print_single_song(song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    case 'l': // album
      print_table_head();
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->album,
            strlen(search_string)-1
          )
        ) {
          print_single_song(song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    case 't':
      print_table_head();
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->title,
            strlen(search_string)-1
          )
        ) {
          print_single_song(song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    case 'y':
      search_year = atoi(search_string);
      print_table_head();
      while (song_ptr != NULL) {
        if (search_year == song_ptr->year) {
          print_single_song(song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    default:
      print_table_head();
      while (song_ptr != NULL) {
        if (
          ! strncmp(
            search_string,
            song_ptr->artist,
            strlen(search_string)-1
          )
        ) {
          print_single_song(song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;
  }
}

void remove_song_head(Song **head_ref) {
  char search_crit;
  char search_string[CHAR_LIMIT];
  Song *song_ptr = *head_ref;
  int search_year;

  printf(
    "Search and remove\n"
    "\ta\tArtist\n\tl\tAlbum\n\tt\tTitle\n\ty\tYear\n"
    "Search by [a]: "
  );

  fgets(search_string, 3, stdin);
  search_crit = search_string[0];
  printf("Search: ");
  fgets(search_string, CHAR_LIMIT, stdin);
  switch (search_crit) {

    case 'a': // artist
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->artist,
            strlen(search_string)-1
          )
        ) {
          remove_single_song(head_ref, song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    case 'l': // album
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->album,
            strlen(search_string)-1
          )
        ) {
          remove_single_song(head_ref, song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    case 't':
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->title,
            strlen(search_string)-1
          )
        ) {
          remove_single_song(head_ref, song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    case 'y':
      search_year = atoi(search_string);
      while (song_ptr != NULL) {
        if (search_year == song_ptr->year) {
          remove_single_song(head_ref, song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;

    default:
      while (song_ptr != NULL) {
        if (
          !strncmp(
            search_string,
            song_ptr->artist,
            strlen(search_string)-1
          )
        ) {
          remove_single_song(head_ref, song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;
  }
}

void print_help_head() {
  printf(
    "Available options:\n"
    "\ta\tAdd a song\n"
    "\ts\tSearch for song(s)\n"
    "\tm\tSort song list\n"
    "\tp\tPrint song list\n"
    "\tr\tSearch and remove song(s)\n"
    "\tf\tRead data from text file\n"
    "\tb\tRead data from binary file\n"
    "\tw\tWrite data to text file\n"
    "\tv\tWrite data to binary file\n"
    "\te\tExit\n"
    "\tq\tExit\n"
  );
}

void sort_list_head(Song **head_ref) {
  char buffer[BUFFER_SIZE];
  char criterion;
  printf(
    "Sort\n"
    "\ta\tArtist\n\tl\tAlbum\n\tt\tTitle\n\ty\tYear\n"
    "Sort by [a]: "
  );
  fgets(buffer, BUFFER_SIZE, stdin);
  criterion = buffer[0];
  merge_sort(head_ref, criterion);
  restore_prev_pointers(head_ref); // only if the list is doubly-linked
}
