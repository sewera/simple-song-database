"""
'Song Database' Simple Python Program
Version: v1.0
Author: Blazej Sewera
Copyright 2018
E-mail: blazejok1@wp.pl
Webpage: [https://github.com/jazzsewera]
Python version: 3.7.1
Dependencies: dill (!), collections, operator, re, json
(!) - non-standard dependency
You can install dill with pip:

    pip install dill

Additional files: lang/pl.json and lang/en.json, also copyrighted 2018
Documentation in Polish and English in files `projekt_doc.pl.md`
and `projekt_doc.en.md`
"""
from collections import namedtuple as nt
from operator import attrgetter
import re
import json
import dill


class SongDatabase(object):
    def __init__(self, filename='songs.json'):
        super(SongDatabase, self).__init__()
        self.filename = filename

    """ Class fields: """
    songlist = []
    filename = 'songs.json'
    bin_filename = 'songs.pickle'
    searchresults = []

    def add_song(self,
                 new_artist,
                 new_album,
                 new_title,
                 new_year,
                 new_duration_m,
                 new_duration_s):
        song = nt('song', 'artist album title year duration_m duration_s')
        self.songlist.append(
            song(
                artist=new_artist,
                album=new_album,
                title=new_title,
                year=new_year,
                duration_m=new_duration_m,
                duration_s=new_duration_s
            )
        )

    def write_to_text_file(self, filename=filename):
        lines = [json.dumps(s._asdict()) for s in self.songlist]
        with open(filename, 'w') as output_file:
            for line in lines:
                output_file.write(line)
                output_file.write('\n')

    def open_from_text_file(self, filename=filename):
        with open(filename, 'r') as input_file:
            lines_from_file = [line.rstrip('\n') for line in input_file]
        self.songlist = [
            json.loads(
                line,
                object_hook=lambda l: nt('song', l.keys())(*l.values())
            ) for line in lines_from_file
        ]

    def write_to_binary_file(self, filename=bin_filename):
        with open(filename, 'wb') as bin_file:
            dill.dump(self.songlist, bin_file)

    def open_from_binary_file(self, filename=bin_filename):
        with open(filename, 'rb') as bin_file:
            self.songlist = dill.load(bin_file)

    def sort_songlist(self, sort_by='artist'):
        self.songlist = sorted(self.songlist, key=attrgetter(sort_by))

    def search_in_songlist(self, search_string, search_by='artist'):
        if search_by == 'year':
            self.searchresults = [
                song for song in self.songlist
                if int(search_string) == song.year
            ]
        else:
            self.searchresults = [
                song for song in self.songlist
                if re.search(
                    search_string,
                    attrgetter(search_by)(song),
                    re.IGNORECASE
                )
            ]

    def remove_songs(self):
        self.songlist = [
            song for song in self.songlist if song not in self.searchresults
        ]


class SongDatabaseHead(object):
    """
    Frontend class for SongDatabase.
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
    crit_dict = {'al': 'album', 'ar': 'artist', 't': 'title', 'y': 'year'}

    def start(self):
        _ = self.messages.get

        menu = {
            'h': self.help,
            'a': self.add_song,
            's': self.search,
            'so': self.sort_songlist,
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
        _ = self.messages.get
        new_artist = input(_('artist') + ': ')
        new_album = input(_('album') + ': ')
        new_title = input(_('title') + ': ')
        new_year = int(input(_('year') + ': '))
        new_duration_m = int(input(_('duration_m') + ': '))
        new_duration_s = int(input(_('duration_s') + ': '))

        self.db.add_song(
            new_artist,
            new_album,
            new_title,
            new_year,
            new_duration_m,
            new_duration_s
        )

    def search(self):
        _ = self.messages.get
        print(_('search_main'))
        criteria = 'h'
        while criteria == 'h':
            print(_('criteria_help'))
            criteria = input(_('search_choice'))  # like 'al' when empty
        search_string = input(_('search_string_prompt'))
        self.db.search_in_songlist(
            search_string,
            search_by=self.crit_dict.get(criteria, 'album')
        )
        self.pretty_print_songlist(searchresults=True)

    def sort_songlist(self):
        _ = self.messages.get
        criteria = 'h'
        while criteria == 'h':
            print(_('criteria_help'))
            criteria = input(_('sort_choice'))  # like 'al' when empty
        self.db.sort_songlist(sort_by=self.crit_dict.get(criteria, 'album'))

    def remove_songs(self):
        _ = self.messages.get
        self.search()
        if input(_('ensure')).lower() == 'y':
            self.db.remove_songs()
        else:
            print(_('aborted'))

    def pretty_print_songlist(self, searchresults=False):
        _ = self.messages.get
        print(
            '{0:^25s}|{1:^25s}|{2:^30s}|{3:^6}|{4:>3}:{5:>2}'
            .format(
                _('artist'),
                _('album'),
                _('title'),
                _('year'),
                'MM',
                'SS'
            )
        )
        print('{0:=^96}'.format(''))
        if searchresults is False:
            for song in self.db.songlist:
                print(
                    '{0:<25s}|{1:<25s}|{2:<30s}|{3:>6}|{4:>3}:{5:>2}'.format(
                        song.artist,
                        song.album,
                        song.title,
                        song.year,
                        song.duration_m,
                        song.duration_s
                    )
                )
        else:
            if len(self.db.searchresults) == 0:
                print(_('search_no_results'))
            else:
                for song in self.db.searchresults:
                    print(
                        '{0:<25s}|{1:<25s}|{2:<30s}|{3:>6}|{4:>3}:{5:>2}'
                        .format(
                            song.artist,
                            song.album,
                            song.title,
                            song.year,
                            song.duration_m,
                            song.duration_s
                        )
                    )
        print()  # empty line

    def change_text_filename(self):
        _ = self.messages.get
        print(_('change_text_filename'), end='')
        new_filename = input()
        if not new_filename == '':
            self.db.filename = new_filename
        else:
            self.db.filename = 'songs.json'

    def change_binary_filename(self):
        _ = self.messages.get
        print(_('change_binary_filename'), end='')
        new_bin_filename = input()
        if not new_bin_filename == '':
            self.db.bin_filename = new_bin_filename
        else:
            self.db.bin_filename = 'songs.pickle'

    def change_language(self):
        if self.lang == 'pl':
            self.lang = 'en'
        else:
            self.lang = 'pl'
        self.messages = {}
        with open(self.filenames.get(self.lang), 'r') as langfile:
            self.messages = json.load(langfile)
        self.start()


if(__name__ == '__main__'):
    dbh = SongDatabaseHead('pl')
    # change to en if you want the app to start in English
    dbh.start()
