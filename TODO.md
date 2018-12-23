# Projekt PRM
## Temat
**Piosenki**, lista **dwukierunkowa**
## Funkcjonalność i jak to zrobić
1. Tworzenie i rozbudowa bazy danych za pomocą standardowego wejścia, podobne do kodu:
```C
void add_track(struct Track* new_track, char new_path[PATH_LENGTH], enum Format new_format, int minutes, int seconds,
	char new_artist[DESC_FIELD_LENGTH], char new_title[DESC_FIELD_LENGTH], enum Genre new_genre) {

	strcpy(new_track -> path, new_path);
	strcpy(new_track -> description.artist, new_artist);
	strcpy(new_track -> description.title, new_title);

	new_track -> format = new_format;
	new_track -> duration = minutes_to_seconds(minutes, seconds);
	new_track -> description.genre = new_genre;
}
```
Wydaje mi się, że będzie wygodniej używać metody `fgets`, a nie `scanf`, bo ta druga nie pozwala na wpisanie spacji w jedno pole.
Chyba że w zadaniu będzie trzeba do jednego pola przypisywać tylko jeden wyraz.
2. Zapis do pliku tekstowego: [rosettacode](https://rosettacode.org/wiki/Simple_database#C)
3. Zapis do pliku binarnego: [stackoverflow](https://stackoverflow.com/questions/29768106/write-struct-to-binary-file-then-read-file-and-print-data)
4. Odczyt z plików: (prawdopodobnie oba powyższe)
5. Sortowanie wg dowolnego pola struktury danych `qsort()`:
  - [tutorialspoint](https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm)
  - [stackoverflow](https://stackoverflow.com/questions/1787996/c-library-function-to-do-sort)
6. Wstawianie i usuwanie dowolnego elementu: [geeksforgeeks](https://www.geeksforgeeks.org/delete-an-element-from-array-using-two-traversals-and-one-traversal/)
7. Wydruk na standardowym wyjściu: proste `printf()`.

## Struktura projektu
Min. 3 pliki:
- nagłówkowy (`*.h`) z definicją struktury danych
- z funkcjami (`*.c`) // trzeba pamiętać o `#include "naglowek.h"`
- main

### Makefile
[Colby computer science](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

> Dokumentacja funkcjonalna i strukturalna jakoś tam pójdzie xD
