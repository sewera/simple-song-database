/*
 * 'Song Database' Simple C Program
 * Version: v1.0
 * Author: Blazej Sewera
 * Copyright 2018
 * E-mail: blazejok1@wp.pl
 * Webpage: [https://github.com/jazzsewera]
 * Check out project.py, it's infinity times better!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "functions.h"

void start_head(Song **head_ref) {
  const char *filename = "songs.txt";
  const char *filename_bin = "songs.dbb";
  char buffer[BUFFER_SIZE];
  char choice;

  printf("Song Database Program\n");
  while (1) {
    printf("Please choose an option (h - help): ");
    fgets(buffer, BUFFER_SIZE, stdin);
    choice = buffer[0];

    switch (choice) {
      case 'h':
        print_help_head();
        break;
      case 'a':
        append_song_head(head_ref);
        break;
      case 's':
        search_song_head(head_ref);
        break;
      case 'm':
        sort_list_head(head_ref);
        break;
      case 'p':
        print_list(head_ref);
        printf("\n");
        break;
      case 'r':
        remove_song_head(head_ref);
        break;
      case 'f':
        if (parse_text_file(head_ref, filename)) {
          print_file_read_error(filename);
        }
        break;
      case 'b':
        if (read_from_binary_file(head_ref, filename_bin)) {
          print_file_read_error(filename_bin);
        }
        break;
      case 'w':
        if (write_to_text_file(head_ref, filename)) {
          print_file_write_error();
        }
        break;
      case 'v':
        if (write_to_binary_file(head_ref, filename_bin)) {
          print_file_read_error(filename_bin);
        }
        break;
      case 'e':
      case 'q':
        return;
      default:
        printf("[E] Invalid option!\n");
        break;
    }
  }
}

int main() {

  Song *head_ref = NULL; // pointer to a first node

  start_head(&head_ref);

  free(head_ref);

  return 0;
}
