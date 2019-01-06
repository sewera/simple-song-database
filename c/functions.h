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

void push(Song **head_ref, int new_year) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   */

  /* 1. allocate node */
  Song *new_node = (Song*) malloc(sizeof(Song));

  /* 2. put in the data  */
  new_node->year = new_year; // TODO

  /* 3. Make next of new node as head and previous as NULL */
  new_node->next = (*head_ref);
  new_node->prev = NULL;

  /* 4. change prev of head node to new node */
  if ((*head_ref) != NULL)
    (*head_ref)->prev = new_node;

  /* 5. move the head to point to the new node */
  (*head_ref) = new_node;
}

void append(Song **head_ref, int new_year) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   */

  /* 1. allocate node */
  Song *new_node = (Song*) malloc(sizeof(Song));

  Song *last = *head_ref; /* used in step 5*/

  /* 2. put in the data  */
  new_node->year = new_year; // TODO

  /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
  new_node->next = NULL;

  /* 4. If the Linked List is empty, then make the new
        node as head */
  if(*head_ref == NULL) {
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
  if(*head_ref == NULL) {
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

void print_list(Song* head) {
  /**
   * Code from [geeksforgeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
   * Modified and fitted by jazz
   */
  Song* last;
  printf("\nTraversal in forward direction \n");
  while (head != NULL) {
    printf(" %d ", head->year);
    last = head;
    head = head->next;
  }

  printf("\nTraversal in reverse direction \n");
  while (last != NULL) {
    printf(" %d ", last->year);
    last = last->prev;
  }
}

void parse_file(const char *filename, Song **head_ref) {
  /* Check if songlist is empty */
  if(*head_ref != NULL)
    printf("Adding nodes at the end of a non-empty list\n");

  FILE *fp;
  char line[BUFFER_SIZE];
  fp = fopen(filename, "r");
  while(fgets(line, BUFFER_SIZE, fp))
    append_from_text_line(head_ref, line);
  fclose(fp);
}

#endif
