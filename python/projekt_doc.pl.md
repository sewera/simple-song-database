# Dokumentacja po polsku
### Dla programu projekt.py

## Klasa `SongDatabase`:
  Jest to klasa opisująca bazę danych utworów. Implementuje backend w tym projekcie. Rozszerzenie klasy `object`.

#### Pola `SongDatabase`:
  - `songlist`: przechowuje listę utworów - listę krotek `namedtuple`,
  - `filename`: przechowuje nazwę pliku tekstowego, do którego można zapisać / z którego można odczytać listę,
  - `bin_filename`: przechowuje nazwę pliku binarnego, do którego można zapisać / z którego można odczytać listę,
  - `searchresults`: przechowuje liste utworzona w wyniku wyszukiwania `search_in_songlist()`.

#### Metody `SongDatabase`:
  - `__init__`:
    Funkcja `__init__` to funkcja wykonująca się podczas tworzenia nowego obiektu klasy SongDatabase.
    Każda funkcja w klasie ma pierwszy argument `self`, ponieważ wywołując tę metodę, musimy przekazać tenże obiekt do funkcji.

    **Argumenty:**

    - `filename` - jest to argument typu string ustawiający nazwę domyślną pliku tworzonego za pomocą metody `write_to_text_file()`.
    Jest to argument opcjonalny, ponieważ ma wartość domyślną - 'songs.json'. Rozszerzenie `.json` jest opcjonalne, jednak zaleca sie
    używania go, ponieważ baza danych jest sformatowana w standardzie json / json lines.

    **Przykład:**

    ```
    db = SongDatabase(filename='songlist.json')
    ```

  - `add_song`:
    Metoda dodająca utwór do `songlist`.

    **Argumenty:**

    - `new_artist` - nazwa artysty
    - `new_album` - nazwa albumu, itd.

    **Przykład:**

    ```
    db.add_song('Toto', 'Toto IV', 'Africa', 1984, 4, 35)
    ```

  - `write_to_text_file`:
    Metoda zapisująca obecną listę utworów do pliku tekstowego o nazwie filename (domyślnie songs.json)
    Format tego pliku to json / json lines, więcej informacji o tym standardzie: [JSON](https://www.json.org) / [JSON lines](https://hackernoon.com/json-lines-format-76353b4e588d)

    **Argumenty:**

    - `filename` - nazwa pliku. Jeśli nie zostanie podana, zostanie użyta nazwa z pola `filename` obiektu.

  - `open_from_text_file`:
    Metoda zapisująca do listy songlist dane z pliku o nazwie filename.

    **Argumenty:**

    - `filename` - analogicznie jak w metodzie `write_to_text_file()`

  - `write_to_binary_file`:
    Metoda zapisująca obecną listę utworów do pliku binarnego. Nie polecam tej metody, ponieważ pliki json są
    powszechnie używane i rozpoznawane oraz istnieje wiele gotowych bibliotek do odczytu jsonów.  
    Używana jest biblioteka dill. Można ją zainstalować poprzez komendę:
    ```
    pip install dill
    ```
    [Strona projektu dill](https://pypi.org/project/dill/)

    **Argumenty:**

    - `filename` - nazwa pliku binarnego. Analogicznie jak w metodzie `write_to_text_file`

  - `open_from_binary_file`:
    Metoda zapisująca do listy songlist z pliku o nazwie filename.

    **Argumenty:**

    - `filename` - analogicznie jak w powyższych metodach

  - `sort_songlist`:
    Metoda sortująca songlist wg podanego kryterium na miejscu, tzn. posortowana lista zastępuje obecną listę.

    **Argumenty:**

    - `sort_by` - kryterium, po którym następuje sortowanie w postaci stringa, domyślnie `artist`
      *Dostępne kryteria:*
      - `artist`,
      - `album`,
      - `title`,
      - `year`,
      - `duration_m`,
      - `duration_s`.

  - `search_in_songlist`:
    Metoda wyszukująca w songlist wg podanego kryterium.

    **Argumenty:**

    - `search_string` - ciąg znaków do wyszukania - pomijana jest wielkość liter
    - `search_by` - kryterium wyszukiwania - analogicznie do argumentu `sort_by` w funkcji `sort_songlist`

    **Przykład:**

    ```
    db.search_in_songlist(input('Wyszukaj po tytule: '), search_by='title')
    ```

  - `remove_songs`:
    Metoda usuwająca z songlist utwory, które znajdują się obecnie w liście searchresults.

## Klasa `SongDatabaseHead`:
Klasa z frontendem (konsolowym) dla klasy `SongDatabase`.

#### Pola `SongDatabaseHead`:
  - `lang`: przechowuje obecnie używany we frontendzie język, domyślnie 'pl', ale przy tworzeniu obiektu można podać argument 'en' (metoda `__init__`),
  - `filenames`: słownik (dictionary) przechowujący nazwy plików z komunikatami w poszczególnych językach,
  - `messages`: słownik, do którego ładują się komunikaty w danym języku,
  - `db`: obiekt klasy `SongDatabase` (backend),
  - `crit_dict`: słownik przechowujący skrócone zapisy kryteriów, aby skrócić i ułatwić użytkownikowi wpisywanie kryteriów podczas np. wyszukiwania.

#### Metody `SongDatabaseHead`:
  - `start`: Metoda uruchamiająca frontend i implementująca menu główne (ogólnie uruchamia program)
  - `help`: Wyświetla pomoc w menu głównym
  - `invalid_input`: Wyświetla komunikat o niepoprawnie wprowadzonej opcji
  - `add_song`: Pozwala interaktywnie wprowadzić utwór do `db.songlist`
  - `search`: Pozwala interaktywnie wyszukać w `db.songlist` utwory wg podanego kryterium i zapisać je w liście `db.searchresults`
  - `sort_songlist`: Pozwala posortować listę wg interaktywnie podanego kryterium
  - `remove_songs`: Pozwala usunąć utwory spełniające wyniki wyszukiwania
  - `pretty_print_songlist`: Wyświetla listę utworów lub wyniki wyszukiwania w ładnej tabelce  
    **Argumenty:**
    - `searchresults` - czy pokazać wyniki wyszukiwania (True) albo całą listę utworów (False). Domyślnie False.
  - `change_text_filename`: Pozwala zmienić nazwę pliku tekstowego do którego zapisywana jest lista utworów
  - `change_binary_filename`: Pozwala zmienić nazwę pliku binarnego do którego zapisywana jest lista utworów
  - `change_language`: Zmienia język programu (komunikatów) z polskiego na angielski i odwrotnie

#### Changelog:
v0.1 Beta:
  - dodana obsluga plikow binarnych (biblioteka dill)

v0.1.0.1 Beta / Alpha:
  - dodana klasa frontendu (SongDatabaseHead)
  - przeniesienie metody `pretty_print_songlist` do klasy frontendu
  - dodana obsluga plikow jezykowych w formacie json

v0.2 Beta:
  - dopracowany frontend
  - dodana metoda pozwalajaca usuwac elementy z listy
  - dodane metody do frontendu (wszystkie wywolujace metody w klasie `SongDatabase`)
  - dodana metoda zmieniajaca jezyk

v0.3 Beta:
  - dodane sortowanie do frontendu

v1.0:
  - dokumentacja w języku polskim i angielskim w oddzielnych plikach markdown
