/*
 * Response.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 *
 *  the response class handles the response and comparing it to the mystery code
 */

#include "Response.h"

#include "Code.h"
#include <iostream>

//constructs the response
Response::Response(const Code& guess, const Code& mystery) {
	int c = guess.checkCorrect(mystery);
	Response::setCorrect(c);

	int in = guess.checkIncorrect(mystery);
	Response::setIncorrect(in);
}

std::ostream &operator<<(std::ostream &output, const Response &r) //overload <<
{
	output << "(" << r.correct << ", " << r.incorrect << ")\n";
	return output;
}

bool Response::operator ==(const Response &r1) const //overload the == operator
{
	return (r1.getCorrect() == this->getCorrect() && r1.getIncorrect() == this->getIncorrect());
}

Response Response::operator =(const Response &r)
{
	setCorrect(r.getCorrect());
	setIncorrect(r.getIncorrect());
	return *this;
}

void Response::clear()          //function to clear response digits
{
    setCorrect(0);
    setIncorrect(0);
}

//setters and getters
void Response::setCorrect(int c) {
	correct = c;
}

void Response::setIncorrect(int in) {
	incorrect = in;
}

int Response::getCorrect() const {
	return correct;
}

int Response::getIncorrect() const {
	return incorrect;
}

//checks for the win!
bool Response::compareResponses() const {
	if ((getCorrect() == 4) && (getIncorrect() == 0))
		return true;
	else
		return false;
}

void Response::printResponse() {
	std::cout << "(" << correct << ", " << incorrect << ")" << std::endl;
}
