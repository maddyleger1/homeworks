/*
 * Response.h
 *
 *  Created on: Sep 16, 2015
 *      Author: maddy
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "Code.h"
#include <iostream>

class Response {
public:
	Response() = default; //default constructor - will not work in visual studio 2010
	Response(const Code& guess, const Code& mystery_code);//constructs the response

	//Operator Overloads
	friend std::ostream &operator<<(std::ostream &output, const Response &r);
	bool operator ==(const Response &r1) const;
	Response operator =(const Response &r1);

	void clear();

	//Setters and Getters
	void setCorrect(int c);
	void setIncorrect(int i);
	int getCorrect() const;
	int getIncorrect() const;

	//Compare Responses
	bool compareResponses() const;

	void printResponse();

private:
	int correct;
	int incorrect;

};

#endif /* RESPONSE_H_ */
