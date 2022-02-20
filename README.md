# T9

Program with a simple GUI imitating a numeric keypad that uses T9 in order to find words. Uses Trie data structure. Written using C++ and Qt.

# Description

* User can find the desired word by using a numeric keypad and then looking through possible translations
* User can use space to find next words, creating sentences and then saving them into a text file
* Dictionary uses words containing only [a-z] symbols
* In case of a mistake, user can reset his text and start over
* If program doesn't find a translation, an appropriate information is displayed, user can start over

# How to run

In order to run the program, you need Qt Creator.

Firstly, you need to build the project. Then, in the folder with the build go to debug and put "dictionary.txt" there - English dictionary containing only words formed with [a-z] symbols. Then, you can go ahead and run the program.

# How to use

* User presses the numeric keys in order to find words
* When user enters the correct sentence, he can press the button "Find Word" until he finds the right word
* User can now use the key '0' to enter a space and find further words. It's important to first find the word, and then use space key.
* In case of a mistake, user presses the 'Reset' button and starts over
* If a word isn't found, program displays "Word not found" text, user can start over
* If the user completed finding his word/sentence, he can use the 'Save text' button in order to save it into a text file. It will be created in the same directory, where the "dictionary.txt" file is 

