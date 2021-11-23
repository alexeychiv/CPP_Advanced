#pragma once

namespace intArrayUtils
{
	void print(int * arr, const int SIZE);
	void fillAscending(int * arr, const int SIZE, const int start);
	void fillDescending(int * arr, const int SIZE, const int start);
	void fillRandom(int * arr, const int SIZE, const int MIN = -1'000'000, const int MAX = 1'000'000);
	void shuffle(int * arr, const int SIZE, const int randomness);
	bool isSortedAscending(int * arr, const int SIZE);
	bool isAscendingSequence(int * arr, const int SIZE);
	bool isSortedDescending(int * arr, const int SIZE);
	bool isDescendingSequence(int * arr, const int SIZE);
	void copy(int * arrSource, int * arrDest, const int SIZE);
};

