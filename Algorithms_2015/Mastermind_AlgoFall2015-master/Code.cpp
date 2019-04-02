/*
 * Code.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 *
 *  the Code class handles initializing the mystery code and checking the guesses for correctness.
 */

#include "Code.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

//constructs the code object
Code::Code(const std::vector<int> code_value) {
	mystery_code = code_value;
}

void Code::initializeCode() {
	int c = 0; //initialize code placeholder

	srand(time(NULL)); //get the seed

	for (int i = 0; i < 4; i++) {
		c = rand() % 6; //for each value in mystery_code, creates random num 0 through 5
		mystery_code.push_back(c);
	}
}

void Code::printCode() {
	for (int i = 0; i < 4; i++) {
		std::cout << mystery_code[i];
	}
}

std::ostream &operator<<(std::ostream &output, const std::vector<int> &guess)
{
	output<<guess[0]<<guess[1]<<guess[2]<<guess[3];
	return output;
}

std::ostream &operator<<(std::ostream &output, const Code &c)
{
	output<<c.mystery_code;
	return output;
}

void Code::init()          //function to clear response digits
{
	for (int i = 0 ; i < 4; i++)
		mystery_code.push_back(0);
}

void Code::clear()
{
	mystery_code.clear();
}

//checks
int Code::checkCorrect(const Code& guess) const {
	//check which are in the right place
	int correct = 0;

	for (int i = 0; i < 4; i++) {
		if (guess.mystery_code[i] == mystery_code[i])
			correct++;
	}

	return correct;
}

int Code::checkIncorrect(const Code& guess) const {
	//check which are correct digits in the wrong place
	int incorrect = 0;

	//makes sure no digit is ever double checked!!!
	std::vector<bool> codeHasBeenMatched;
	std::vector<bool> guessHasBeenMatched;

	for (int i = 0; i < 4; i++) {
		codeHasBeenMatched.push_back(false);
		guessHasBeenMatched.push_back(false);
	}

	for (int i = 0; i < 4; i++) { //iterate through each digit of mystery code for one digit of guess
		for (int j = 0; j < 4; j++) {
			if ((guess.mystery_code[i] == mystery_code[j])
					&& codeHasBeenMatched[j] == false
					&& guessHasBeenMatched[i] == false) {
				incorrect++;
				codeHasBeenMatched[j] = true;
				guessHasBeenMatched[i] = true;
			}
		}
	}

	//compares to correct - important so not doubled
	int correct = guess.checkCorrect(mystery_code);

	incorrect -= correct;

	return incorrect;
}

void Code::initializeCheck()
{
	bool value = false;
	isChecked.clear();
	for (int i=0; i<4; i++)
	{
	    isChecked.push_back(value);
	 }
}

void Code::changeCheck(int n)               //function to change checked variable
{
    isChecked[n].flip(); //flips boolean value
}

//thanks Brian Wilcox for help with the increment algorithm
void Code::increment()
{
	int index = 3;

	while (mystery_code[index]==5)
	{
		mystery_code[index]=0;
		index--;
	}

	mystery_code[index]++;
}
