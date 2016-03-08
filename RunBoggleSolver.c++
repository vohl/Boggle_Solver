// includes

#include "BoggleSolver.h"
#include <iostream>

using namespace std;

// main
int main(int argc, char const *argv[])
{
	// simple run harness that outputs answers to sample grid
	LoadDictionary("dictionary.txt");
	Results results = FindWords("dzxeaiqut", 3, 3);
	for (int i = 0; i < results.Count; ++i)
	{
		int j = 0;
		while (results.Words[i][j] >= 'a' && results.Words[i][j] <= 'z')
		{
			cout << results.Words[i][j];
			++j;
		}
		cout << endl;
	}
	cout << results.Score << endl;
	FreeDictionary();
	FreeWords(results);
	return 0;
}
