/*
 * main.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Mastermind.h"

int main() {
	//make sure input is valid!!!
	try{
	Mastermind maddy; //initialize mastermind object
	maddy.playGame2(); //lets go!!!

	system("pause");
	}

	catch (int e)
	{
		std::cout<<"exited with error code "<<e<<std::endl;
	}

	return 0;
}
