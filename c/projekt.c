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

void append_song_head(Song **head_ref) {
  // Variables used in adding a new node
  char artist[CHAR_LIMIT];
  char album[CHAR_LIMIT];
  char title[CHAR_LIMIT];
  char year[6];
  char duration_m[10];
  char duration_s[3];

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
  fgets(duration_s, 3, stdin);

  append(head_ref, artist, album, title, atoi(year), (unsigned char) atoi(duration_m), (unsigned char) atoi(duration_s));
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
  //search_crit = fgetc(stdin);
  //scanf("%c\n", &search_crit);
  fgets(search_string, 3, stdin);
  search_crit = search_string[0];
  printf("Search: ");
  fgets(search_string, CHAR_LIMIT, stdin);
  switch (search_crit) {

    case 'a': // artist

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

    case 'l': // album

      print_table_head();
      while (song_ptr != NULL) {
        if (
            ! strncmp(
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
            ! strncmp(
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
                      strlen(search_string) <= strlen(song_ptr->artist) ? strlen(search_string) : strlen(song_ptr->artist)
                     )
           ) {
          print_single_song(song_ptr);
        }
        song_ptr = song_ptr->next;
      }
      break;
  }
}

int main(int argc, char const *argv[]) {
  // Necessary "objects" xD No, but really, variables.
  const char filename[] = "songs.txt";
  Song *head = NULL; // pointer to a first node

  parse_file(filename, &head);

  print_list(&head);
  merge_sort_doubly_linked(&head, 'a');
  printf("\n");
  print_list(&head);
  printf("\n");
  search_song_head(&head);
  append_song_head(&head);
  print_list(&head);

  return 0;
}
