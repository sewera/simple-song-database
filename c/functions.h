/*
 * 'Song Database' Simple C Program
 * Version: v1.0
 * Author: Blazej Sewera
 * Copyright 2018
 * E-mail: blazejok1@wp.pl
 * Webpage: [https://github.com/jazzsewera]
 * Check out projekt.py, it's infinity times better!
 */
#include "structure.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void free_list(Song **head_ref);

int parse_text_file(Song **head_ref, const char *filename);

int write_to_text_file(Song **head_ref, const char *filename);

int write_to_binary_file(Song **head_ref, const char *filename_bin);

int read_from_binary_file(Song **head_ref, const char *filename_bin);

void print_list(Song **head_ref);

void print_file_read_error(const char *filename);

void print_file_write_error();

void append_song_head(Song **head_ref);

void search_song_head(Song **head_ref);

void remove_song_head(Song **head_ref);

void print_help_head();

void sort_list_head(Song **head_ref);

#endif
