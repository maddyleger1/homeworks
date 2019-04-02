/*
 * main.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: maddy
 */
#include "wordlist.h"
#include "grid.h"
#include "hashTable.h"
#include "heap.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <cstdlib>

void findMatchesHash(const grid &Grid,hashTable<std::string> &Table)
{
	int gridsize;
	std::string search_me;
	gridsize = Grid.matrix.size();
	search_me = ""; //making it blank

	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			//checks going to the top
			for (int k = 0; k < gridsize; k++)
			{
				if (k > i)
					search_me += Grid.matrix[gridsize - (k-i)][j];
				else
					search_me += Grid.matrix[i-k][j];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Table.inlist(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the bottom
			for (int k = 0; k < gridsize; k++)
			{
				//row + k mod gridsize
				search_me += Grid.matrix[(i+k) % gridsize][j];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Table.inlist(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the right
			for (int k = 0; k < gridsize; k++)
			{
				search_me += Grid.matrix[i][(j+k) % gridsize];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Table.inlist(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the left
			for (int k = 0; k < gridsize; k++)
			{
				if (k > j)
					search_me += Grid.matrix[i][gridsize - (k-j)];
				else
					search_me += Grid.matrix[i][j-k];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Table.inlist(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the top right
			for (int k = 0; k < gridsize; k++)
			{
				if (k > i)
					search_me += Grid.matrix[gridsize - (k-i)][(j+k) % gridsize];
				else
					search_me += Grid.matrix[i-k][(j+k) % gridsize];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Table.inlist(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to bottom right - modularized to grid size
			for (int k = 0; k < gridsize; k++)
			{
				search_me += Grid.matrix[(i+k) % gridsize][(j+k)%gridsize];

				if (search_me.length() <= 22 && search_me.length() >= 5)
				{ //if parameters are true you can search
					if (Table.inlist(search_me))
						std::cout<<search_me<<std::endl;
				}

			}
			search_me = "";

			//going to top-left
			for (int k = 0; k < gridsize; k++)
			{
				if (k > i && k > j)
					search_me += Grid.matrix[i-k + gridsize][j-k + gridsize];
				else
				{
					if (k > i)
						search_me += Grid.matrix[i-k + gridsize][j-k];
					else
					{
						if (k > j)
							search_me += Grid.matrix[i-k][j-k + gridsize];
						else
							search_me += Grid.matrix[i-k][j-k];
					}
				}

				if (search_me.length() <= 22 && search_me.length() >=5)
				{
					if (Table.inlist(search_me))
						std::cout<<search_me<<std::endl;
				}
			}
			search_me="";

			//checks going to the bottom left
			for (int k = 0; k < gridsize; k++)
			{
				if (k > j)
					search_me += Grid.matrix[(i+k) % gridsize][j-k + gridsize];
				else
					search_me += Grid.matrix[(i+k) % gridsize][j-k];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Table.inlist(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word


		}
	}
	std::cout<<std::endl;
}

void findMatches(const wordlist &Words, const grid &Grid)
{
	int gridsize;
	std::string search_me;
	gridsize = Grid.matrix.size();
	search_me = ""; //making it blank

	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			//checks going to the top
			for (int k = 0; k < gridsize; k++)
			{
				if (k > i)
					search_me += Grid.matrix[gridsize - (k-i)][j];
				else
					search_me += Grid.matrix[i-k][j];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Words.binarySearch(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the bottom
			for (int k = 0; k < gridsize; k++)
			{
				//row + k mod gridsize
				search_me += Grid.matrix[(i+k) % gridsize][j];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Words.binarySearch(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the right
			for (int k = 0; k < gridsize; k++)
			{
				search_me += Grid.matrix[i][(j+k) % gridsize];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Words.binarySearch(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the left
			for (int k = 0; k < gridsize; k++)
			{
				if (k > j)
					search_me += Grid.matrix[i][gridsize - (k-j)];
				else
					search_me += Grid.matrix[i][j-k];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Words.binarySearch(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to the top right
			for (int k = 0; k < gridsize; k++)
			{
				if (k > i)
					search_me += Grid.matrix[gridsize - (k-i)][(j+k) % gridsize];
				else
					search_me += Grid.matrix[i-k][(j+k) % gridsize];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Words.binarySearch(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word

			//checks going to bottom right - modularized to grid size
			for (int k = 0; k < gridsize; k++)
			{
				search_me += Grid.matrix[(i+k) % gridsize][(j+k)%gridsize];

				if (search_me.length() <= 22 && search_me.length() >= 5)
				{ //if parameters are true you can search
					if (Words.binarySearch(search_me))
						std::cout<<search_me<<std::endl;
				}

			}
			search_me = "";

			//going to top-left
			for (int k = 0; k < gridsize; k++)
			{
				if (k > i && k > j)
					search_me += Grid.matrix[i-k + gridsize][j-k + gridsize];
				else
				{
					if (k > i)
						search_me += Grid.matrix[i-k + gridsize][j-k];
					else
					{
						if (k > j)
							search_me += Grid.matrix[i-k][j-k + gridsize];
						else
							search_me += Grid.matrix[i-k][j-k];
					}
				}

				if (search_me.length() <= 22 && search_me.length() >=5)
				{
					if (Words.binarySearch(search_me))
						std::cout<<search_me<<std::endl;
				}
			}
			search_me="";

			//checks going to the bottom left
			for (int k = 0; k < gridsize; k++)
			{
				if (k > j)
					search_me += Grid.matrix[(i+k) % gridsize][j-k + gridsize];
				else
					search_me += Grid.matrix[(i+k) % gridsize][j-k];

				if (search_me.length()<=22 && search_me.length()>=5)
				{ //checks criteria
					if (Words.binarySearch(search_me)) //checks if found
						std::cout<<search_me<<std::endl;
				}
			}
			search_me=""; //resets word


		}
	}
	std::cout<<std::endl;
}

void search(int type, grid Grid, wordlist Words)
{
	if (type > 3 || type < 0)
		throw(2);

	hashTable<std::string> Hash;


	clock_t start, sort_end, search_end;

	start = clock();


	switch(type)
	{
	case 0: std::cout<<"\n\n\nStarting QuickSort!"<<std::endl;
			Words.quickSort(Words.words, 0, Words.getListSize()-1);
			break;
	case 1: std::cout<<"\n\n\nStarting MergeSort!"<<std::endl;
			Words.words = Words.mergeSort(Words.words);
			break;
	case 2: std::cout<<"\n\n\nStarting InsertionSort!"<<std::endl;
			Words.insertionSort();
			break;
	case 3: std::cout<<"\n\nStarting HeapSort!"<<std::endl;
			Words.heapSort();
			break;
	}


	sort_end=clock();
	std::cout<<"Sorting took "<<(float)(sort_end-start) / CLOCKS_PER_SEC <<" seconds. Finding words..."<<std::endl;

	if (type == 3)
		findMatchesHash(Grid, Hash);

	search_end = clock();
	std::cout<<"Finding words took "<<(float) (search_end-sort_end) / CLOCKS_PER_SEC<<" seconds"<<std::endl;

	std::cout<<"Total Process Runtime (s): "<<(float) (search_end-start) / CLOCKS_PER_SEC <<std::endl;
}

//pass wordlist List list.getWords();

int main()
{
	try{
		clock_t start, endofsort, endofsearch;

		//Initialize clock
		start=clock();
		//instantiate grid
		grid Grid("puzzle3_size50");
		wordlist Words("wordlist.txt");
		std::cout<<"Heap Sorting!\n";
		Words.heapSort();

		endofsort=clock();

		hashTable<std::string> Hash;

		std::vector<std::string> wordz=Words.returnWords();
		//populate the hash table with words
		Hash.populateHash(wordz);
		std::cout<<"\nThe Following Words were found in the Puzzle:\n";
		findMatchesHash(Grid,Hash);
		//Finds matches for grid for grid with hashtable
		//Set clock breakpoint
		endofsearch=clock();
		int diff1=endofsort-start;
		int diff2=endofsearch-endofsort;
		int diff3=endofsearch-start;
		std::cout<<"It took "<<(float)diff1/CLOCKS_PER_SEC <<" seconds to do HeapSort\n";
		std::cout<<"It took "<<(float)diff2/CLOCKS_PER_SEC <<" seconds to Search using the hash table\n";
		std::cout<<"It took "<<(float)diff3/CLOCKS_PER_SEC <<" seconds for the entire process\n";


	}

	catch (int n)
	{
		if (n == 1)
			std::cout<<"File input error!!!!"<<std::endl;
		else
			std::cout<<"Error!"<<std::endl;
	}

	system("pause");
	return 0;
}
