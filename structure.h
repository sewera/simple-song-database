#ifndef STRUCT_H
#define STRUCT_H
#define CHAR_LIMIT 64

struct song {
  char artist[CHAR_LIMIT];
  char album[CHAR_LIMIT];
  char title[CHAR_LIMIT];
  int year;
  unsigned char duration_m;
  unsigned char duration_s;
  struct song *prev;
  struct song *next;
};
typedef struct song Song;

#endif
