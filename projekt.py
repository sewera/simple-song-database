"""
'Song Database' Simple Python Program
Version: v0.2 Beta
Author: Blazej Sewera
Copyright 2018
E-mail: blazejok1@wp.pl
Webpage: [https://github.com/jazzsewera]
Python version: 3.7.1
Dependencies: dill (!), collections, operator, re, json
(!) - non-standard dependency
Additional files: lang/pl.json and lang/en.json, also copyrighted 2018
Documentation in Polish due to the program being a university project.
"""
from collections import namedtuple as nt
from operator import attrgetter
import re
import json
import dill

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

    """ Pola obiektu: """
    songlist = [] # przechowuje liste utworow
    filename = 'songs.json' # przechowuje nazwe pliku
    bin_filename = 'songs.pickle' # przechowuje nazwe pliku binarnego
    searchresults = [] # przechowuje liste utworzona w wyniku wyszukiwania `search_in_songlist()`

    def add_song(self, new_artist, new_album, new_title, new_year, new_duration_m, new_duration_s):
        """
        Metoda dodajaca utwor do `songlist`.
        Args:
            new_artist - nazwa artysty
            new_album - nazwa albumu, itd.
        Example:
            db.add_song('Toto', 'Toto IV', 'Africa', 1984, 4, 35)
        """
        song = nt('song', 'artist album title year duration_m duration_s') # namedtuple (krotka, odpowiednik struktury) przechowujaca wszystkie informacje o utworze
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

    def write_to_binary_file(self, filename=bin_filename):
        """
        Metoda zapisujaca obecna liste utworow do pliku binarnego. Nie polecam tej metody, poniewaz pliki json sa
        powszechnie uzywane i rozpoznawane oraz istnieje wiele gotowych bibliotek do odczytu jsonow.
        Uzywana jest biblioteka dill. Mozna ja zainstalowac poprzez komende:
            pip install dill
        [Strona projektu dill](https://pypi.org/project/dill/)
        Args:
            filename - nazwa pliku binarnego. Analogicznie jak w metodzie `write_to_text_file`
        """
        with open(filename, 'wb') as bin_file:
            dill.dump(self.songlist, bin_file)

    def open_from_binary_file(self, filename=bin_filename):
        """
        Metoda zapisujaca do listy songlist z pliku o nazwie filename.
        Uzywana jest biblioteka dill. Mozna ja zainstalowac poprzez komende:
            pip install dill
        [Strona projektu dill](https://pypi.org/project/dill/)
        Args:
            filename - analogicznie jak w powyzszych metodach
        """
        with open(filename, 'rb') as bin_file:
            self.songlist = dill.load(bin_file)

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
        if search_by == 'year':
            self.searchresults = [song for song in self.songlist if int(search_string) == song.year]
        else:
            self.searchresults = [song for song in self.songlist if re.search(search_string, attrgetter(search_by)(song), re.IGNORECASE)]

    def remove_songs(self):
        self.songlist = [song for song in self.songlist if song not in self.searchresults]

class SongDatabaseHead(object):
    """
    Klasa z frontendem dla klasy SongDatabase.
    """

    def __init__(self, lang='pl'):
        super(SongDatabaseHead, self).__init__()
        self.lang = lang
        with open(self.filenames.get(self.lang), 'r') as langfile:
            self.messages = json.load(langfile)

    lang = 'pl'
    filenames = {'pl': 'lang/pl.json', 'en': 'lang/en.json'}
    messages = {}
    db = SongDatabase()

    def start(self):
        _ = self.messages.get

        menu = {
            'h': self.help,
            'a': self.add_song,
            's': self.search,
            'p': self.pretty_print_songlist,
            'r': self.remove_songs,
            'fo': self.db.open_from_text_file,
            'fob': self.db.open_from_binary_file,
            'fw': self.db.write_to_text_file,
            'fwb': self.db.write_to_binary_file,
            'fc': self.change_text_filename,
            'fcb': self.change_binary_filename,
            'cl': self.change_language,
            'e': exit
        }

        print(_('greeting'))
        choice = ''
        while not choice == 'e' and not choice == 'cl':
            choice = input(_('choice_prompt')).lower()
            menu.get(choice, self.invalid_input)()

    def help(self):
        _ = self.messages.get
        print(_('help'))

    def invalid_input(self):
        _ = self.messages.get
        print(_('invalid_input'))

    def add_song(self):
        """
        Metoda dodajaca utwor do `songlist` w obiekcie db interaktywnie.
        """
        _ = self.messages.get
        new_artist = input(_('artist') + ': ')
        new_album = input(_('album') + ': ')
        new_title = input(_('title') + ': ')
        new_year = int( input(_('year') + ': ') )
        new_duration_m = int( input(_('duration_m') + ': ') )
        new_duration_s = int( input(_('duration_s') + ': ') )

        self.db.add_song(new_artist, new_album, new_title, new_year, new_duration_m, new_duration_s)

    def search(self):
        """
        Metoda wyszukujaca i (w przypadku argumentu False) drukujaca na ekran liste utworow spelniajacych kryteria.
        """
        _ = self.messages.get
        print(_('search_main'))
        criteria = 'h'
        while criteria == 'h':
            print(_('criteria_help'))
            criteria = input(_('search_choice')) # like 'al' when empty
        search_string = input(_('search_string_prompt'))
        crit_dict = {'al': 'album', 'ar': 'artist', 't': 'title', 'y': 'year'}
        self.db.search_in_songlist(search_string, search_by=crit_dict.get(criteria, 'album'))
        self.pretty_print_songlist(searchresults=True)

    def remove_songs(self):
        """
        Metoda wyszukujaca i usuwajaca utwory spelniajace kryteria.
        """
        _ = self.messages.get
        self.search()
        self.db.remove_songs() if input(_('ensure')).lower() == 'y' else print(_('aborted'))

    def pretty_print_songlist(self, searchresults=False):
        """
        Metoda wyswietlajaca na ekranie liste utworow lub liste utworzona w wyniku wyszukiwania.
        Pretty print to ogolne okreslenie na wyswietlenie informacji w formacie jak najczytelniejszym dla uzytkownika.
        Args:
            searchresults - argument typu boolean (True / False).
                False - drukuje cala liste utworow `songlist`
                True - drukuje liste utworzona w wyniku wyszukiwania `searchresults`
        """
        _ = self.messages.get
        print('{0:^25s}|{1:^25s}|{2:^30s}|{3:^6}|{4:>3}:{5:>2}'.format(_('artist'), _('album'), _('title'), _('year'), 'MM', 'SS'))
        print('{0:=^96}'.format(''))
        if searchresults == False:
            for song in self.db.songlist:
                print('{0:<25s}|{1:<25s}|{2:<30s}|{3:>6}|{4:>3}:{5:>2}'.format(song.artist, song.album, song.title, song.year, song.duration_m, song.duration_s))
        else:
            if len(self.db.searchresults) == 0:
                print(_('search_no_results'))
            else:
                for song in self.db.searchresults:
                    print('{0:<25s}|{1:<25s}|{2:<30s}|{3:>6}|{4:>3}:{5:>2}'.format(song.artist, song.album, song.title, song.year, song.duration_m, song.duration_s))
        print() # empty line

    def change_text_filename(self):
        """
        Metoda pozwalajaca zmienic domyslna nazwe pliku tekstowego.
        """
        _ = self.messages.get
        print(_('change_text_filename'), end='')
        new_filename = input()
        if not new_filename == '':
            self.db.filename = new_filename
        else:
            self.db.filename = 'songs.json'

    def change_binary_filename(self):
        """
        Metoda pozwalajaca zmienic domyslna nazwe pliku binarnego.
        """
        _ = self.messages.get
        print(_('change_binary_filename'), end='')
        new_bin_filename = input()
        if not new_bin_filename == '':
            self.db.bin_filename = new_bin_filename
        else:
            self.db.bin_filename = 'songs.pickle'

    def change_language(self):
        """
        Metoda zmieniajaca jezyk (odczytujaca inny plik z komunikatami)
        """
        if self.lang == 'pl': self.lang = 'en'
        else: self.lang = 'pl'
        self.messages = {}
        with open(self.filenames.get(self.lang), 'r') as langfile:
            self.messages = json.load(langfile)
        self.start()


dbh = SongDatabaseHead('pl') # change to en if you want the app to start in English

dbh.start()
"""
Poki co, napisana jest wiekszosc backendu i tylko mala czesc frontendu.
TODO:
    napisac frontend
Changelog:
    v0.1 Beta:
        dodana obsluga plikow binarnych (biblioteka dill)
    v0.1.0.1 Beta / Alpha:
        dodana klasa frontendu (SongDatabaseHead)
        przeniesienie metody pretty_print_songlist do klasy frontendu
        dodana obsluga plikow jezykowych w formacie json
    v0.2 Beta:
        dopracowany frontend
        dodana metoda pozwalajaca usuwac elementy z listy
        dodane metody do frontendu (wszystkie wywolujace metody w klasie SongDatabase)
        dodana metoda zmieniajaca jezyk
Dokumentacja stworzona na podstawie zalecen Google dot. dokumentacji w Pythonie.
"""
