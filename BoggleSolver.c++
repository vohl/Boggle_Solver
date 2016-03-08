// includes
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>
#include "BoggleSolver.h"

// Number of letters in the alphaboot
#define ALPHA_SIZE 26
#define WORD_SIZE 20

// Globals
// Empty head of the trie. This pointer wil be set
// to wherever on the heap that the Dictionary is located
Trie_node * head;

// A pointer to an instance of Result. Will set this pointer
// to the Result we build when solving, and return it.
Results * my_result;

// A temp of the found words. This pointer is given to
// the Results->Word
char ** temp_words;

using namespace std;

/*
	@param start is the head pointer that we are going
	to traverse and free.
*/
void Delete_Trie_Node (Trie_node * start)
{
	// Recursively free every child node that has been allocated
	for (int i = 0; i < ALPHA_SIZE; ++i)
	{
		if (start->children[i] != NULL)
		{
			Delete_Trie_Node(start->children[i]);
		}
		++i;
	}

	// deletes the highest node after freeing the children
	delete [] start;
}

/*
	@param size is the size of a word that was found durring the search
	@return the score for a word of that size
*/
int size_To_Score (int size)
{
	// Used a switch table to determine the score based on the size
	switch (size)
	{
		case 3:
		case 4:
			return 1;
		case 5:
			return 2;
		case 6:
			return 3;
		case 7:
			return 5;
		default:
			return 11;
	}
}

/*
	Recursive auxillary function for the board to find words
	@param my_result is the expected Results struct
	@param node is place we are in the dictionary that corresponds
	to the order of blocks we have looked at
	@param board is a single c-string that represents the problem
	@param visited is a vctor that represents locations on the
	board that I have been so we dont go there again
	@param i is the index of my board
	@param width  of the board
	@param height of the board
*/
void recursiveFind (Results * my_result, Trie_node * node, const char * board, vector<bool>& visited, int i, unsigned width, unsigned height)
{
	// This if loop defines the case where the the node
	// for the trie has a word that we havent made yet for this istance of the game
	if (node->size > 0 && node->visited == false)
	{
		// Sets the node to visited for future encounters, and records the score
		node->visited = true;
		my_result->Score += size_To_Score(node->size);

		// if this is the first word, allocate room for it
		// on the heap and set the temp_words to point at it
		if (my_result->Count == 0)
		{
			++(my_result->Count);
			char** temp = (char **)malloc(sizeof(char *));
			temp[0] = (char *)malloc((node->size+1)*sizeof(char));

			for (int j = 0; j < node->size; ++j)
			{
				temp[0][j] = node->word[j];
			}

			// non alpha terminating character
			temp[0][node->size] = '1';
			temp_words = temp;
		}
		// Malloc more memory and set temps_words to point to this
		// new memory after freeing the old block. Make sure to copy old over to the new block
		else
		{
			int old_size = (my_result->Count);
			++(my_result->Count);
			char** temp = (char **)malloc(my_result->Count*sizeof(char *));
			for (int j = 0; j < old_size; ++j)
			{
				temp[j] = temp_words[j];
			}
			temp[old_size]= (char *)malloc((node->size+1)*sizeof(char));

			for (int j = 0; j <= node->size; ++j)
			{
				temp[old_size][j] = node->word[j];
			}

			// non alpha terminating character
			temp[old_size][node->size] = '1';
			free(temp_words);
			temp_words = temp;
		}
	}

	// recursively traverses the board to adjacent tires that we HAVENT been to
	int size = width*height;
	// If the height or height is 1 we are dealing with just a single array
	if (height == 1 || width == 1)
	{
		if (i != 0)
		{
			visited[i-1] = true;
			recursiveFind(my_result, node->children[board[i-1] - 97], board, visited, i-1, width, height);
			visited[i-1] = false;
		}
		if (i != size-1)
		{
			visited[i+1] = true;
			recursiveFind(my_result, node->children[board[i+1] - 97], board, visited, i+1, width, height);
			visited[i+1] = false;
		}
	}
	// If the block we are at is pointing to is in the center area
	// we can move up or down
	else if (i < (size-width) && i >= width)
	{
		// The block is not on the left side, it can move leftwards
		if (i%width != 0)
		{
			if (node->children[board[i-1] - 97] != NULL && visited[i-1] == false)
			{
				visited[i-1] = true;
				recursiveFind(my_result, node->children[board[i-1] - 97], board, visited, i-1, width, height);
				visited[i-1] = false;
			}
			if (node->children[board[i-width-1] - 97] != NULL && visited[i-width-1] == false)
			{
				visited[i-width-1] = true;
				recursiveFind(my_result, node->children[board[i-width-1] - 97], board, visited, i-width-1, width, height);
				visited[i-width-1] = false;
			}
			if (node->children[board[i+width-1] - 97] != NULL && visited[i+width-1] == false)
			{
				visited[i+width-1] = true;
				recursiveFind(my_result, node->children[board[i+width-1] - 97], board, visited, i+width-1, width, height);
				visited[i+width-1] = false;
			}
		}
		// The block is not on the right side, it can move rightwards
		if (i%width != width-1)
		{
			if (node->children[board[i+1] - 97] != NULL && visited[i+1] == false)
			{
				visited[i+1] = true;
				recursiveFind(my_result, node->children[board[i+1] - 97], board, visited, i+1, width, height);
				visited[i+1] = false;
			}
			if (node->children[board[i-width+1] - 97] != NULL && visited[i-width+1] == false)
			{
				visited[i-width+1] = true;
				recursiveFind(my_result, node->children[board[i-width+1] - 97], board, visited, i-width+1, width, height);
				visited[i-width+1] = false;
			}
			if (node->children[board[i+width+1] - 97] != NULL && visited[i+width+1] == false)
			{
				visited[i+width+1] = true;
				recursiveFind(my_result, node->children[board[i+width+1] - 97], board, visited, i+width+1, width, height);
				visited[i+width+1] = false;
			}
		}
		if (node->children[board[i-width] - 97] != NULL && visited[i-width] == false)
		{
			visited[i-width] = true;
			recursiveFind(my_result, node->children[board[i-width] - 97], board, visited, i-width, width, height);
			visited[i-width] = false;
		}
		if (node->children[board[i+width] - 97] != NULL && visited[i+width] == false)
		{
			visited[i+width] = true;
			recursiveFind(my_result, node->children[board[i+width] - 97], board, visited, i+width, width, height);
			visited[i+width] = false;
		}
	}
	// We are in the bottom row, cant move a row down
	else if (i >= (size-width))
	{
		if (i%width != 0)
		{
			if (node->children[board[i-1] - 97] != NULL && visited[i-1] == false)
			{
				visited[i-1] = true;
				recursiveFind(my_result, node->children[board[i-1] - 97], board, visited, i-1, width, height);
				visited[i-1] = false;
			}
			if (node->children[board[i-width-1] - 97] != NULL && visited[i-width-1] == false)
			{
				visited[i-width-1] = true;
				recursiveFind(my_result, node->children[board[i-width-1] - 97], board, visited, i-width-1, width, height);
				visited[i-width-1] = false;
			}
		}
		if (i%width != width-1)
		{
			if (node->children[board[i+1] - 97] != NULL && visited[i+1] == false)
			{
				visited[i+1] = true;
				recursiveFind(my_result, node->children[board[i+1] - 97], board, visited, i+1, width, height);
				visited[i+1] = false;
			}
			if (node->children[board[i-width+1] - 97] != NULL && visited[i-width+1] == false)
			{
				visited[i-width+1] = true;
				recursiveFind(my_result, node->children[board[i-width+1] - 97], board, visited, i-width+1, width, height);
				visited[i-width+1] = false;
			}
		}
		if (node->children[board[i-width] - 97] != NULL && visited[i-width] == false)
		{
			visited[i-width] = true;
			recursiveFind(my_result, node->children[board[i-width] - 97], board, visited, i-width, width, height);
			visited[i-width] = false;
		}
	}
	// We are in the top row, cant move up
	else if (i < width)
	{
		if (i%width != 0)
		{
			if (node->children[board[i-1] - 97] != NULL && visited[i-1] == false)
			{
				visited[i-1] = true;
				recursiveFind(my_result, node->children[board[i-1] - 97], board, visited, i-1, width, height);
				visited[i-1] = false;
			}
			if (node->children[board[i+width-1] - 97] != NULL && visited[i+width-1] == false)
			{
				visited[i+width-1] = true;
				recursiveFind(my_result, node->children[board[i+width-1] - 97], board, visited, i+width-1, width, height);
				visited[i+width-1] = false;
			}
		}
		if (i%width != width-1)
		{
			if (node->children[board[i+1] - 97] != NULL && visited[i+1] == false)
			{
				visited[i+1] = true;
				recursiveFind(my_result, node->children[board[i+1] - 97], board, visited, i+1, width, height);
				visited[i+1] = false;
			}
			if (node->children[board[i+width+1] - 97] != NULL && visited[i+width+1] == false)
			{
				visited[i+width+1] = true;
				recursiveFind(my_result, node->children[board[i+width+1] - 97], board, visited, i+width+1, width, height);
				visited[i+width+1] = false;
			}
		}
		if (node->children[board[i+width] - 97] != NULL && visited[i+width] == false)
		{
			visited[i+width] = true;
			recursiveFind(my_result, node->children[board[i+width] - 97], board, visited, i+width, width, height);
			visited[i+width] = false;
		}
	}
}

/*
	@param path is the string path to the dictionary file
*/
// takes in a path to the dictionary, and makes a dictionary out of it?
// input dictionary is a file with one word per line
void LoadDictionary(const char* path)
{
	// creating the Trie_node
	head = new Trie_node;

	// Pointer to the dictionary file
	FILE * dictF;
	int c;
	int i = 0;
	// open the file and assign it to dictF
	dictF = fopen(path, "r");
	Trie_node * node = head;

	// buffer is used to create the word in the dictionary
	// that a node will point at
	// value will be copied over into node->word
	char buffer[WORD_SIZE];

	// if the file is there it should not be NULL
	if (dictF != NULL)
	{
		// iterates through the dictionary and build the Trie until eof is reached
		while (!feof(dictF))
		{
			c = fgetc(dictF);

			// if this character sequence has not been seen allocate the new Trie_node
			if ((char)c != '\n' && node->children[c - 97] == NULL)
			{
				buffer[i] = (char)c;
				node->children[c - 97] = new Trie_node;
				(node->children[c - 97])->parent = node;
				node = node->children[c - 97];
				++i;
			}
			// we have seen this sequence, so just travers the trie_node to the next node
			else if ((char)c != '\n')
			{
				buffer[i] = (char)c;
				node = node->children[c - 97];
				++i;
			}
			// this else if will run if the new line character is met
			// we'll store the buffer at the node we are at
			else if (i >= 3)
			{
				node->size = i;
				for (int j = 0; j < i; ++j)
				{
					node->word[j] = buffer[j];
					//cout << node->word[j];
				}
				//cout << endl;
				node = head;
				i = 0;
			}
			// only runs if a word less then three is seen
			// these are woth 0 points, dont need to add them into the trie
			else
			{
				node = head;
				i = 0;
			}
		}
	}

	// close the file
	fclose(dictF);
}

/*
	@param board is a cstring representation of the game board
	@param width is the width of the board
	@param height is the height of the board
	@return Results structure for the answer to the game board
*/
// this func may be called multiple times
// I may also solve all the words within this function
// board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube
Results FindWords(const char* board, unsigned width, unsigned height)
{
	// asserts that will only fail with inputs that wouldnt make sense
	assert(width > 0);
	assert(height > 0);
	if (height == 1)
	{
		assert(width > 2);
	}
	else if (width == 1)
	{
		assert(height > 2);
	}

	// initializing the Results struct that I have to return
	my_result = new Results;
	Trie_node * node = head;
	int size = width*height;
	vector<bool> visited(size);

	// for each board tile recursively find a word starting on that tile
	for (int i = 0; i < size; ++i)
	{
		if (node->children[board[i] - 97] != NULL)
		{
			visited[i] = true;
			recursiveFind(my_result, node->children[board[i] - 97], board, visited, i, width, height);
			visited[i] = false;
		}
	}

	// sets Results->Words to the string of arrays
	my_result->Words = temp_words;

	// return the struct
	return *my_result;
}

/*
	@param results is the structure that we are freeing
*/
// 'results' is identical to what was returned from FindWords
void FreeWords(Results results)
{
	int s = results.Count;
	// free each inner pointer
	for (int i = 0; i < s; ++i)
	{
		free(temp_words[i]);
	}
	// Frees the top level pointer
	free(temp_words);

	// finally delete the Results struct
	delete [] my_result;
}

void FreeDictionary()
{
	// calls function to recursively free Trie
	Delete_Trie_Node(head);
}
