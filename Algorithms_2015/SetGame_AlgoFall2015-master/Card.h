/*
 * Card.h
 *
 *  Created on: Sep 30, 2015
 *      Author: maddy
 */

#ifndef CARD_H_
#define CARD_H_

#include <vector>
#include <string>
#include <iostream>

class Card {
public:
	Card() = default;
	Card(int num, std::string col, std::string shp, std::string pat);
	~Card();

	friend std::ostream &operator <<(std::ostream &output, const Card &card);

	//setters
	void setNum(const int &num);
	void setColor(const std::string &col);
	void setShape(const std::string &shp);
	void setPattern(const std::string &pat);

	//getters
	int getNum();
	std::string getColor();
	std::string getShape();
	std::string getPattern();


private:
	int num_objects;
	std::string color;
	std::string shape;
	std::string pattern;
};

#endif /* CARD_H_ */
