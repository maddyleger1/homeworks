/*
 * grid.h
 *
 *  Created on: Oct 13, 2015
 *      Author: maddy
 */

#ifndef GRID_H_
#define GRID_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "wordlist.h"

class grid {
public:
	grid(std::string file); //Initializes Grid Constructor with name
	grid()=default;
	void setMatrix(std::vector <std::vector<char> > mat){matrix = mat;};
	std::vector <std::vector<char> > getMatrix(){return matrix;};

	friend void findMatches(const wordlist& Words, const grid& Grid);
	friend void findMatchesHash(const grid &Grid,hashTable<std::string> &Table);

private:
	std::vector <std::vector<char> > matrix;
};

#endif /* GRID_H_ */
