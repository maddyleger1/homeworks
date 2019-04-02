/*
 * wordlist.h
 *
 *  Created on: Oct 13, 2015
 *      Author: maddy
 */

#ifndef WORDLIST_H_
#define WORDLIST_H_

#include <iostream>
#include <vector>
#include <string>
#include "heap.h"
#include "hashTable.h"

class grid;

class wordlist {
public:
	wordlist(std::string file);
	wordlist() = default;
	friend std::ostream &operator <<(std::ostream&out, wordlist Words);

	//getters and setters yo
	int getListSize(){return listsize;};
	std::vector<std::string> getWords(){return words;};
	void setListSize(int size){listsize = size;};
	void setWords(){/*dont use me!*/};

	//sorts
	void quickSort(std::vector<std::string> &wordz, int first, int last);
	std::vector <std::string> mergeSort(std::vector <std::string> &wordz);
	void insertionSort();

	//necessary sort subfunctions
	int partition(std::vector<std::string> &wordz, int left, int right);
	std::vector<std::string> merge(std::vector<std::string> &left, std::vector<std::string> &right);

	void heapSort();

	bool binarySearch(const std::string &word) const;

	inline std::vector<std::string> returnWords(){return words;};

	friend void search(int type, grid Grid, wordlist Words); //so i can touch the word list


private:
	heap <std::string> heap_words;
	std::vector<std::string> words;
	int listsize;
};

#endif /* WORDLIST_H_ */
