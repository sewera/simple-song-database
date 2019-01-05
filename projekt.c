/*
 * Huge mess in C, but at least tokenize_line is working quite well.
 * Not for any practical use yet.
 * You don't have to look, check out project.py, it's infinity times better!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

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

void read_line(char *dest_str, FILE *fp) {
  fgets(dest_str, BUFFER_SIZE, fp);
}

int main(int argc, char const *argv[]) {
  FILE *fp;
  Song *s = (Song*) malloc(sizeof(Song));
  fp = fopen("songs.txt", "r");
  //char line[BUFFER_SIZE] = read_line(fp);
  //char *tokptr = line;
  //fgets(line, BUFFER_SIZE, fp);
  char *str = malloc(BUFFER_SIZE);
  read_line(str, fp);

  printf("%s\n", str);
  tokenize_line(s, str);
  printf("%s -- %s -- %s -- %d -- %d -- %d\n", s->artist, s->album, s->title, s->year, s->duration_m, s->duration_s);
  return 0;
}
