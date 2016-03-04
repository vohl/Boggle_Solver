# Boggle_Solver
Boggle Unity Project

given an NxN grid that contains characters, write a solver fot the game of Boggle in c++

Game of Boggle :

Words are formed by sequentially adjacent characters, and unique blocks
Words have to be at least 3 letters long
Can include other derivations of sead word i.e. past tense, plural, single, active verd
Differences from the actual game : Q represents the qu block

Scoring of words :
word-length | Points
       3, 4          |      1
         5           |      2
         6           |      3
         7           |      5
         8+          |      11

code given::
struct Results
{
    // a pointer to a constant pointer to constant char
    const char* const* Words;    // pointers to unique found words, each terminated by a non-alpha char
    unsigned           Count;    // total number of words found
    unsigned           Score;    // total score for all words found
    void*              UserData; // ignored
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
