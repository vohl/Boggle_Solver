#ifndef BoggleSolver_h
#define BoggleSolver_h

// Max word size in dictionary, and number of alpha characters
#define ALPHA_SIZE 26
#define WORD_SIZE 20

struct Results
{
    // a pointer to a constant pointer to constant char
    const char* const* Words;    // pointers to unique found words, each terminated by a non-alpha char
    unsigned           Count;    // total number of words found
    unsigned           Score;    // total score for all words found
    void*              UserData; // ignored

    // Constructor for the Result struct
    Results ()
    {
    	Count = 0;
    	Score = 0;
    	Words = 0;
    }
};

// Main data structure to create dictionary from. Contains a
// boolean to show that this node has been visited as well as the
// the word associated with that node. Size of the word, and a pointer to
// the parent node and it's childrens
// Built from the Trie concept.
struct Trie_node
{
	bool visited;
	char word[WORD_SIZE];
	int size;
	struct Trie_node * parent;
	struct Trie_node * children[ALPHA_SIZE];

	// Trie_node struct constructor
	Trie_node ()
	{
		visited = false;
		size = 0;
		parent = 0;
		for (int i = 0; i < ALPHA_SIZE; ++i)
		{
			children[i] = 0;
		}
	}
};

// takes in a path to the dictionary, and makes a dictionary out of it?
// input dictionary is a file with one word per line
void LoadDictionary(const char* path); // << TODO

// this func may be called multiple times
// I may also solve all the words within this function
// board: will be exactly width * height chars, and 'q' represents the 'qu' Boggle cube
Results FindWords(const char* board, unsigned width, unsigned height); // << TODO

// 'results' is identical to what was returned from FindWords
void FreeWords(Results results); // << TODO

void FreeDictionary(); // << TODO

#endif
