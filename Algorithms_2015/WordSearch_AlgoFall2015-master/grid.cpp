/*
 * grid.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: maddy
 */

#include "grid.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

grid::grid(std::string file) {
	int c, r;

	std::ifstream fin;
	fin.open(file.c_str());

	if(!fin)
	{
		throw(1);
		exit(0);
	}

	fin >> c >> r; //reads in dimensions

	matrix.resize(r); //resizes the rows as length

	for (int i = 0; i < r; i++) //for each row, resizes columns
		matrix[i].resize(c);

	while(!fin.eof()) //while not the end of file
	{
		for (int j = 0; j < r; j++)
		{
			for (int k = 0; k < c; k++)
			{
				fin >> matrix[j][k]; //creates the v as 2d
			}
		}
	}

}

