/*
 * Mastermind.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 */

#include "Mastermind.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Code.h"
#include "Response.h"
#include <ctime>

Mastermind::Mastermind() {

}

std::ostream &operator <<(std::ostream &output, const Mastermind &m)
{
	return output;
}

void Mastermind::printCode() { //prints code by accessing a print function in code class
	std::cout << "The mystery code is: ";
	mystery_code.printCode();
	std::cout << std::endl;
}

Code Mastermind::humanGuess() { //reads in the human guess
	Code guess;
	int tmp;
	std::vector<int> input;
	std::cout << "Please enter your guess (with spaces in between):"
			<< std::endl;
	for (int i = 0; i < 4; i++) {
		std::cin >> tmp; //you need a tmp var because you can't directly read in to the vector
		input.push_back(tmp);
	}
	guess = input;

	//error checking
	if (input[0] > 5 || input[1] > 5 || input[2] > 5 || input[3] > 5)
	{
		throw 1;
		exit(0);
	}

	return guess;
}

Response Mastermind::getResponse(const Code& guess, const Code& mystery_code) {
	return Response(guess, mystery_code);
}

//uses compare responses
bool Mastermind::isSolved(const Response& r) {
	if (r.compareResponses() == true)
		return true;
	else
		return false;
}

void Mastermind::setPrevGuess(const Code &g)
{
	prev_guesses.push_back(g);
}

void Mastermind::setPrevResponse(const Response &r)
{
	prev_responses.push_back(r);
}

std::vector <Code> Mastermind::getPrevGuess()
{
	return prev_guesses;
}

std::vector <Response> Mastermind::getPrevResponse()
{
	return prev_responses;
}

bool Mastermind::consistentWithPreviousGuesses(Code &guess)
{
	Response r;

	bool value = true;
	int x;
	x = (int)prev_guesses.size();

	for (int i = 0; i < x; i ++)
	{
		r = getResponse(prev_guesses[i], guess);

		value = value && (r == prev_responses[i]);
	}

	return value;
}

void Mastermind::agentGuess(Code &guess)
{
	bool isLegit = true;
	std::vector<Response> res;

	int x;
	x = (int)all_guesses.size();

	for (int i = 0; i < x; i++)
	{
		isLegit = consistentWithPreviousGuesses(all_guesses[i]);
		if (!isLegit && all_guesses[i].checkStat()==false)
			all_guesses[i].changeCheck(0);
	}

    for (int j = 0; j < x; j++)
    {
        if (all_guesses[j].checkStat() == false)
        {
           guess = all_guesses[j];
           break;
        }

    }


}

//plays the game!!!
void Mastermind::playGame() {
	//uses default constructors for placeholders
	Code guess;
	Response r;
	mystery_code.initializeCode();
	Mastermind::printCode();

	//the master loop
	for (int i = 0; i < 10; i++) {
		std::cout << "Guess number " << i + 1 << std::endl;
		guess = Mastermind::humanGuess();
		r = Mastermind::getResponse(guess, mystery_code);
		r.printResponse();
		if (Mastermind::isSolved(r) == true) {
			std::cout << "Winner! It took you " << i + 1 << " guesses."
					<< std::endl;
			return;
		}
	}
	std::cout << "Lost after 10 attempts" << std::endl;
	return;
}

void Mastermind::playGame2()
{
	mystery_code.clear();
	guess.clear();

	Code temp;
	Response rtemp;
	rtemp.clear();
	mystery_code = humanGuess();
	std::cout<<mystery_code<<std::endl;
	temp.init();
	temp.initializeCheck();

	for (int i = 1; i <1296; i ++)
	{
		all_guesses.push_back(temp);
		temp.increment();
	}

	//the master loop
	for (int i = 0; i < 10; i++) {
		guess.clear();
		guess.init();
		agentGuess(guess);
		std::cout << "Guess number " << i + 1 << std::endl;
		std::cout<<guess<<std::endl;

		rtemp = getResponse(guess, mystery_code);
		rtemp.printResponse();

		prev_guesses.push_back(guess);
		prev_responses.push_back(rtemp);

		if (isSolved(rtemp) == true)
		{
			std::cout<<"You win!"<<std::endl;
			return;
		}
	}
	std::cout << "Lost after 10 attempts" << std::endl;
	return;
}
