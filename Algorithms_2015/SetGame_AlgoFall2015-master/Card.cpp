/*
 * Card.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: maddy
 */

#include "Card.h"
#include <vector>

Card::Card(int num, std::string col, std::string shp, std::string pat) {

	num_objects=num;
	color = col;
	shape = shp;
	pattern = pat;
}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

std::ostream &operator<<(std::ostream &output, const Card &card)
{
	output<<card.num_objects<<"\t"<<card.color<<"\t"<<card.pattern<<"\t"<<card.shape<<std::endl;
	return output;
}

//setters and getters

void Card::setNum(const int &num)
{
	num_objects = num;
}

void Card::setColor(const std::string &col)
{
	color = col;
}

void Card::setShape(const std::string &shp)
{
	shape = shp;
}

void Card::setPattern(const std::string &pat)
{
	pattern = pat;
}

int Card::getNum()
{
	return num_objects;
}
std::string Card::getColor()
{
	return color;
}
std::string Card::getShape()
{
	return shape;
}
std::string Card::getPattern()
{
	return pattern;
}
