/*
 * wordlist.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: maddy
 */

#include "wordlist.h"
#include "grid.h"
#include "heap.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>

std::ostream &operator <<(std::ostream &out, const std::vector<std::string> &Words)
{
	for (int i = 0; i < Words.size(); i++)
	{
		out<<Words[i];
		out<<std::endl;
	}

	return out;
}
wordlist::wordlist(std::string file)
{
	std::ifstream fin;
	std::string temp;
	listsize = 0;
	fin.open(file.c_str());

	if(!fin)
	{
		throw(0);
		exit(0);
	}

	while (!fin.eof())
	{
		getline(fin,temp);
		words.push_back(temp);
		listsize++;
	}

}

void wordlist::quickSort(std::vector<std::string> &wordz, int first, int last)
{
	int s;
	if (first < last)
	{
		s = partition(wordz, first, last);
		quickSort(wordz, first, s-1);
		quickSort(wordz, s+1, last);

	}
}

std::vector <std::string> wordlist::mergeSort(std::vector<std::string> &wordz)
{

	if ((int)wordz.size() <= 1)
		return wordz;

	std::vector<std::string> left, right, output;
	int mid; //declares vectors that are the sides and also mid index

	mid = ((int)wordz.size() + 1)/2;

	for (int i = 0; i < mid; i++)
		left.push_back(wordz[i]);

	for (int i = mid; i < (int)wordz.size(); i++)
		right.push_back(wordz[i]);

	left = mergeSort(left);
	right = mergeSort(right);
	output = merge(left, right);

	return output;
}


void wordlist::insertionSort()
{
	for (int i = 0; i < listsize; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (words[j] < words[j-1])
				std::swap(words[j], words[j-1]);
		}
	}
}





int wordlist::partition(std::vector<std::string> &wordz, int left, int right)
{
	int i, j;
	std::string p;
	p = wordz[left];
	i = left;

	for(j = left + 1; j < right; j++)
	{
		if (wordz[j] < p)
		{
			i++;
			swap(wordz[i], wordz[j]);
		}
	}

	swap(wordz[i],wordz[left]);

	return i;
}

std::vector<std::string> wordlist::merge(std::vector<std::string> &left, std::vector<std::string> &right)
{
	std::vector <std::string> wordzz;

	while ((int)left.size() > 0 || (int)right.size() > 0)
	{
		if ((int)left.size() > 0 && (int)right.size() > 0)
		{
			if ((std::string)left.front() <= (std::string)right.front())
			{
				wordzz.push_back(left.front());
				left.erase(left.begin());
			}
			else
			{
				wordzz.push_back(right.front());
				right.erase(right.begin());
			}
		}

		else if ((int)left.size() > 0)
		{
			for (int i = 0; i < (int)left.size(); i++)
				wordzz.push_back(left[i]);
			break;
		}

		else
		{
			for (int i = 0; i < (int)right.size(); i++)
				wordzz.push_back(right[i]);
			break;
		}
	}
	return wordzz;
}

void wordlist::heapSort()
{
	heap_words.initializeMaxHeap(words);

	int n = words.size() - 1;

	for (int i = n; i >= 2; i--)
	{
		std::swap(words[i],words[1]);
		heap_words.maxHeapify(words, 1, i-1);
	}

	std::cout<<words<<std::endl;

}

bool wordlist::binarySearch(const std::string &word) const
{
	std::string temp;
	int first = 0, last, mid;
	last = listsize;

	while (first < last)
	{
		mid = (first + last)/2;
		temp = words[mid];
		if (word == temp)
			return true;
		else
		{
			if (word < temp)
				last = mid;
			else
				first = mid + 1;
		}
	}
	return false;
}
