# spell-checker
Uses a trie to load a dictionary and spell-check a selected text<br>
Usage: speller.c [dictionary] [text] <br>
Calls dictionary.c, which loads the selected dictionary through use of a trie.  Checks the text against the dictionary, reports the number of misspelled words, then unloads the dictionary.
