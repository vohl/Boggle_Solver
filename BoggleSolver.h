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
// the Parent node and it's Childrens
// Built from the Trie concept.
struct Trie_Node
{
	bool Visited;
	char Word[WORD_SIZE];
	int Node_Size;
	struct Trie_Node * Parent;
	struct Trie_Node * Children[ALPHA_SIZE];

	// Trie_Node struct constructor
	Trie_Node ()
	{
		Visited = false;
		Node_Size = 0;
		Parent = 0;
		for (int i = 0; i < ALPHA_SIZE; ++i)
		{
			Children[i] = 0;
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
