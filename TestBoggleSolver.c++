#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#include "BoggleSolver.h"

// ---
// LoadDictionary and FreeDictionary
// Utilizes valgrind to look at memory being freed
// ---

// I do not handle different kind of characters in a
// dictionary outside of the alpha characters

TEST (BoggleSolver, load_dictionary_1)
{
  char * path = "dictionary.txt";
  LoadDictionary(path);
  Trie_Node * node = GiveMeTheTrie();
  FreeDictionary();
}

TEST (BoggleSolver, load_dictionary_2)
{
  char * path = "dictionary_test1,txt";
  LoadDictionary(path);
  Trie_Node * node = GiveMeTheTrie();
  FreeDictionary();
}

TEST (BoggleSolver, load_dictionary_3)
{
  char * path = "dictionary_test2.txt";
  LoadDictionary(path);
  Trie_Node * node = GiveMeTheTrie();
  FreeDictionary();
}

TEST (BoggleSolver, load_dictionary_4)
{
	char * path = "dictionary_test3.txt";
   LoadDictionary(path);
   Trie_Node * node = GiveMeTheTrie();
   FreeDictionary();
}
