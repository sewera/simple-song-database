"""
'Song Database' Simple Python Program
Version: v0.0.8 Alpha
Author: Blazej Sewera
Copyright 2018
E-mail: blazejok1@wp.pl
Webpage: [https://github.com/jazzsewera]
Python version: 3.7.1
Documentation in Polish due to the program being a university project.
"""
from collections import namedtuple as nt
from operator import attrgetter
import re
import json

class SongDatabase(object):
    """
    Klasa opisujaca baze danych utworow.
    Jest rozszerzeniem klasy object.
    """
    def __init__(self, filename='songs.json'):
        """
        Funkcja `__init__` to funkcja wykonujaca sie podczas tworzenia nowego obiektu klasy SongDatabase.
        Kazda funkcja w klasie ma pierwszy argument `self`, poniewaz wywolujac te metode, musimy przekazac tenze obiekt do funkcji.
        Args:
            filename - jest to argument typu string ustawiajacy nazwe domyslna pliku tworzonego za pomoca metody write_to_text_file()
                jest to argument opcjonalny, poniewaz ma wartosc domyslna - songs.json. Rozszerzenie `.json` jest opcjonalne, jednak zaleca sie
                uzywania go, poniewaz baza danych jest sformatowana w standardzie json.
        Example:
            db = SongDatabase(filename='songlist.json')
        """
        super(SongDatabase, self).__init__()
        self.filename = filename
        print('Object SongDatabase created.') # W tym momencie obiekt klasy SongDatabase jest juz utworzony. Mozna bez problemu pominac tego printa.

    """ Pola obiektu: """
    songlist = [] # przechowuje liste utworow
    filename = 'songs.json' # przechowuje nazwe pliku
    searchresults = [] # przechowuje liste utworzona w wyniku wyszukiwania `search_in_songlist()`

    def add_song(self, new_artist=None, new_album=None, new_title=None, new_year=None, new_duration_m=None, new_duration_s=None):
        """
        Metoda dodajaca utwor do `songlist`. Wykonana bez ktoregokolwiek z argumentow, dopyta uzytkownika o nie.
        Args:
            new_artist - nazwa artysty
            new_album - nazwa albumu, itd.
        Example:
            db.add_song('Toto', 'Toto IV', 'Africa', 1984, 4, 35)
        """
        song = nt('song', 'artist album title year duration_m duration_s') # namedtuple (krotka, odpowiednik struktury) przechowujaca wszystkie informacje o utworze

        if new_artist == None:
            new_artist = input('Artist: ')
        if new_album == None:
            new_album = input('Album: ')
        if new_title == None:
            new_title = input('Title: ')
        if new_year == None:
            new_year = int( input('Year: ') )
        if new_duration_m == None:
            new_duration_m = int( input('Duration (minutes): ') )
        if new_duration_s == None:
            new_duration_s = int( input('Duration (seconds): ') )
        self.songlist.append( song(artist=new_artist, album=new_album, title=new_title, year=new_year, duration_m=new_duration_m, duration_s=new_duration_s) )

    def write_to_text_file(self, filename=filename):
        """
        Metoda zapisujaca obecna liste utworow do pliku tekstowego o nazwie filename (domyslnie songs.json)
        Format tego pliku to json, wiecej informacji o tym standardzie: [https://www.json.org]
        Args:
            filename - nazwa pliku. Jesli nie zostanie podana, zostanie uzyta nazwa z pola `filename` obiektu.
        """
        lines = [json.dumps(s._asdict()) for s in self.songlist]
        with open(filename, 'w') as output_file:
            for line in lines:
                output_file.write(line)
                output_file.write('\n')

    def open_from_text_file(self, filename=filename):
        """
        Metoda zapisujaca do listy songlist z pliku o nazwie filename.
        Args:
            filename - analogicznie jak w metodzie write_to_text_file()
        """
        with open(filename, 'r') as input_file:
            lines_from_file = [line.rstrip('\n') for line in input_file]
        self.songlist = [ json.loads( line, object_hook=lambda l: nt( 'song', l.keys() )( *l.values() ) ) for line in lines_from_file ]

    def sort_songlist(self, sort_by='artist'):
        """
        Metoda sortujaca songlist wg podanego kryterium na miejscu, tzn. posortowana lista zastepuje obecna liste.
        Args:
            sort_by - kryterium, po ktorym nastepuje sortowanie w postaci stringa, domyslnie `artist`
            Dostepne kryteria:
                artist,
                album,
                title,
                year,
                duration_m,
                duration_s
        """
        self.songlist = sorted(self.songlist, key=attrgetter(sort_by))

    def search_in_songlist(self, search_string, search_by='artist'):
        """
        Metoda wyszukujaca w songlist wg podanego kryterium.
        Args:
            search_string - ciag znakow do wyszukania - pomijana jest wielkosc liter
            search_by - kryterium wyszukiwania - analogicznie do argumentu `sort_by` w funkcji sort_songlist()
        Example:
            db.search_in_songlist(input('Wyszukaj po tytule: '), search_by='title')
        """
        self.searchresults = [song for song in self.songlist if re.search(search_string, attrgetter(search_by)(song), re.IGNORECASE)]

    def pretty_print_songlist(self, searchresults=False):
        """
        Metoda wyswietlajaca na ekranie liste utworow lub liste utworzona w wyniku wyszukiwania.
        Pretty print to ogolne okreslenie na wyswietlenie informacji w formacie jak najczytelniejszym dla uzytkownika.
        Args:
            searchresults - argument typu boolean (True / False).
                False - drukuje cala liste utworow `songlist`
                True - drukuje liste utworzona w wyniku wyszukiwania `searchresults`
        """
        print('{0:^25s}|{1:^25s}|{2:^30s}|{3:^6}|{4:>3}:{5:>2}'.format('Artist', 'Album', 'Title', 'Year', 'MM', 'SS'))
        print('{0:=^96}'.format(''))
        if searchresults == False:
            for song in self.songlist:
                print('{0:<25s}|{1:<25s}|{2:<30s}|{3:>6}|{4:>3}:{5:>2}'.format(song.artist, song.album, song.title, song.year, song.duration_m, song.duration_s))
        else:
            if len(self.searchresults) == 0:
                print('No matching results.')
            else:
                for song in self.searchresults:
                    print('{0:<25s}|{1:<25s}|{2:<30s}|{3:>6}|{4:>3}:{5:>2}'.format(song.artist, song.album, song.title, song.year, song.duration_m, song.duration_s))
        print() # pusta linia

"""
Ponizej sa instrukcje wykonywane w trakcie trwania programu (runtime), czyli jest to odpowiednik funkcji int main()
"""
# Tworzenie obiektu db jako baza danych piosenek:
db = SongDatabase()

# Dodanie kilku utworow:
db.add_song('Phil Collins', 'In the air', 'In the air tonight', 1998, 5, 34)
db.add_song('Mitch Murder', 'Selection Four', 'Hideaway Remix', 2017, 4, 32)
db.add_song('Herbie Hancock', 'Head Hunters', 'Chameleon', 1973, 15, 45)
db.add_song('Herbie Hancock', 'Head Hunters', 'Watermelon Man', 1973, 6, 32)
# Utwor mozna tez dodac w trakcie wykonywania programu, przez uzytkownika, z klawiatury:
db.add_song() # Wtedy wywolujemy funkcje bez zadnych argumentow

# Wyswietlenie utworkow w konsoli:
db.pretty_print_songlist()
db.sort_songlist(sort_by='title') # w tych nawiasach mozemy podac w jakim kryterium chcemy sortowac.
db.pretty_print_songlist()
db.write_to_text_file() # zapis do pliku (domyslnie songs.json)

# Wyszukiwanie w bazie danych:
db.search_in_songlist(input('Search by album: '), search_by='album') # wyszukiwanie utworow na podstawie tego, co wpisze uzytkownik - metoda input()
db.pretty_print_songlist(searchresults=True)

"""
Poki co, napisana jest wiekszosc backendu i tylko mala czesc frontendu.
TODO:
    napisac zapis / odczyt do i z pliku binarnego (biblioteka pickle)
    napisac frontend
Dokumentacja stworzona na podstawie zalecen Google dot. dokumentacji w Pythonie.
"""
