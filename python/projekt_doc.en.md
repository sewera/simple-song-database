# Documentation in English
### For projekt.py program

## `SongDatabase` class:
  Class implementing song database. Also implements backend in this project. Extension of `object` class.

#### `SongDatabase` fields:
  - `songlist`: contains the list of songs - stored in namedtuples
  - `filename`: contains filename of text file from which you can read data or write data to
  - `bin_filename`: contains binary filename
  - `searchresults`: a list containing current search results

#### `SongDatabase` methods:
  - `__init__`:
    Init function is a function called everytime when a new object of this class is created.
    Every function has the first argument `self`, because when calling the function, we have to pass the object to it.

    **Args:**

    - `filename` - string argument setting the default name for the file created by calling `write_to_text_file()` function.
    It is optional and has the default value 'songs.json'. `.json` file extension is also optional, but is recommended due to the
    actual text being formatted in json / json lines standard.

    **Example:**

    ```
    db = SongDatabase(filename='songlist.json')
    ```

  - `add_song`:
    Method adding a new song to `songlist`.

    **Args:**

    - `new_artist` - artist name
    - `new_album` - album name, etc.

    **Example:**

    ```
    db.add_song('Toto', 'Toto IV', 'Africa', 1984, 4, 35)
    ```

  - `write_to_text_file`:
    Method writing the current songlist into a text file with name `filename` (default: 'songs.json')
    Format / standard of this file is json / json lines, more info about those: [JSON](https://www.json.org) / [JSON lines](https://hackernoon.com/json-lines-format-76353b4e588d)

    **Args:**

    - `filename` - name of the file. If not provided, `filename` from the object fields will be used.

  - `open_from_text_file`:
    Method writing to `songlist` data from the text file named `filename`.

    **Args:**

    - `filename` - the same as in `write_to_text_file()` method

  - `write_to_binary_file`:
    Method writing current songlist into a binary file. I do not recommend using this solution, because json files are widely supported
    with lots of available libraries in numerous programming languages to handle them.  
    dill library is used. You can install it with command:
    ```
    pip install dill
    ```
    [dill project website](https://pypi.org/project/dill/)

    **Args:**

    - `filename` - name of the binary file. Same as in `write_to_text_file` method

  - `open_from_binary_file`:
    Method writing to `songlist` data from the binary file named `filename`.

    **Args:**

    - `filename` - same as in methods above

  - `sort_songlist`:
    Method sorting song list by given criterion in-place, so that sorted list replaces current list.

    **Args:**

    - `sort_by` - criterion, by which the list is sorted. Default: 'artist'
      *Availabe criteria:*
      - `artist`,
      - `album`,
      - `title`,
      - `year`,
      - `duration_m`,
      - `duration_s`.

  - `search_in_songlist`:
    Method searching in songlist with given criterion.

    **Args:**

    - `search_string` - string to search - case-insensitive
    - `search_by` - criterion of search - analogous to `search_by` argument in function `sort_songlist`

    **Example:**
    ```
    db.search_in_songlist(input('Search by title: '), search_by='title')
    ```

  - `remove_songs`:
    Method removing from songlist songs that are currently in searchresults list.

## `SongDatabaseHead` class:
(In-terminal) frontend class for `SongDatabase`

#### `SongDatabaseHead` fields:
  - `lang`: contains currently used in program language, default 'pl', but it can be easily changed when creating an object of `SongDatabaseHead` class to 'en' (`__init__` method),
  - `filenames`: dictionary containing the names of the files with messages in different languages ('en' and 'pl' for now),
  - `messages`: dictionary to which the messages in given language are loaded,
  - `db`: `SongDatabase` object (backend),
  - `crit_dict`: dictionary containing shortened notation of criteria (of sort and search) so as to speed up and simplify interaction and input.

#### `SongDatabaseHead` methods:
  - `start`: Method launching the frontend which implements main menu
  - `help`: Displays help message in main menu
  - `invalid_input`: Displays a message when user input was invalid
  - `add_song`: Allows to interactively add a song to `db.songlist`
  - `search`: Allows to interactively search in `db.songlist` songs by given criterion and write them to `db.searchresults`
  - `sort_songlist`: Allows to sort the list by given criterion
  - `remove_songs`: Allows to search and delete songs
  - `pretty_print_songlist`: Prints the list to the screen in a table.  
    **Args:**
    - `searchresults` - if True: show search results (`searchresults`); if False: show the whole list (`songlist`). Default: False.
  - `change_text_filename`: Allows to change the name of the file to which the songlist is written
  - `change_binary_filename`: Allows to change the name of binary file to which the songlist is written
  - `change_language`: Changes the language of the program (language of messages) from English to Polish and vice-versa

#### Changelog:
v0.1 Beta:
  - binary file handling (dill library)

v0.1.0.1 Beta / Alpha:
  - frontend class created (SongDatabaseHead)
  - method `pretty_print_songlist` moved to frontend class
  - messages in different lang/.json files

v0.2 Beta:
  - improved frontend
  - method to remove elements from songlist
  - methods for frontend class (all calling methods in `SongDatabase` class)
  - method to change the language

v0.3 Beta:
  - added sorting to frontend

v1.0:
  - documentation in Polish and English in separate markdown files
