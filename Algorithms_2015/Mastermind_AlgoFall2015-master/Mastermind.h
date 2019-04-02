/*
 * Mastermind.h
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 */

#ifndef MASTERMIND_H_
#define MASTERMIND_H_

#include "Code.h"
#include "Response.h"
#include <vector>

class Mastermind {
public:
	Mastermind();
	void printCode();

	friend std::ostream &operator <<(std::ostream &output, const Code &c);

	//functions to return code and response objects
	Code humanGuess();
	Response getResponse(const Code& guess, const Code& mystery_code);

	//checks to see if solved
	bool isSolved(const Response& r);

	//getters setters for previous responses/guesses
	void setPrevGuess(const Code &guess);
	void setPrevResponse(const Response &r);
	std::vector <Code> getPrevGuess();
	std::vector <Response> getPrevResponse();

	bool consistentWithPreviousGuesses(Code &guess);

	void agentGuess(Code &guess);

	//leggggooooo!!!
	void playGame();
	void playGame2();

private:
	//you need this here to access the code class stuff
	Code mystery_code,guess;
	Response digs;
	std::vector <Code> prev_guesses;
	std::vector <Response> prev_responses;
	std::vector <Code> all_guesses;
};

#endif /* MASTERMIND_H_ */
