/*
 * main.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: maddy
 */
#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "Node.h"
#include <time.h>
#include <cstdlib>

bool isSet(std::vector <Card> &v)
{
	if (v.size() < 3)
		throw(2);

	bool nums,shapes,patterns,colors;

	if ((v[0].getNum() == v[1].getNum()) && (v[1].getNum() == v[2].getNum()))
		nums = true;
	else if (((v[0].getNum() == v[1].getNum()) && (v[0].getNum()!=v[2].getNum())) || ((v[1].getNum() == v[2].getNum()) && (v[0].getNum()!=v[1].getNum())) || ((v[0].getNum() == v[2].getNum()) && (v[0].getNum()!=v[1].getNum())) )
		return false;
	else
		nums = false;

	if (v[0].getShape() == v[1].getShape() && v[1].getShape() == v[2].getShape())
		shapes = true;
	else if ((v[0].getShape() == v[1].getShape() && v[0].getShape()!=v[2].getShape()) || (v[1].getShape() == v[2].getShape() && v[1].getShape()!=v[0].getShape()) || ((v[0].getShape() == v[2].getShape()) && (v[0].getShape()!=v[1].getShape())))
		return false;
	else
		shapes = false;

	if (v[0].getPattern() == v[1].getPattern() && v[1].getPattern() == v[2].getPattern())
		patterns = true;
	else if ((v[0].getPattern() == v[1].getPattern() && v[0].getPattern()!=v[2].getPattern()) || (v[1].getPattern() == v[2].getPattern() && v[1].getPattern()!=v[0].getPattern()) || ((v[0].getPattern() == v[2].getPattern()) && (v[0].getPattern()!=v[1].getPattern())) )
		return false;
	else
		patterns = false;

	if (v[0].getColor() == v[1].getColor() && v[1].getColor() == v[2].getColor())
		colors = true;
	else if ((v[0].getColor() == v[1].getColor() && v[0].getColor()!=v[2].getColor()) || (v[1].getColor() == v[2].getColor() && v[1].getColor()!=v[0].getColor()) || ((v[0].getColor() == v[2].getColor()) && (v[0].getColor()!=v[1].getColor())) )
		return false;
	else
		colors = false;

	return true;
}

void playSet(Deck deck)
{
	int num_sets=0;

	std::vector<Card> v;
	deck.deal(12, v);
	if (v.size() != 12)
		throw(1);
	std::cout<<"Your Cards:\n";
	for (int i = 0; i < 12; i++)
		std::cout<<v[i];

	std::vector <Card> threeCards;

	std::cout<<"Checking for sets..."<<std::endl;

	for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 11; j++) {
			for (int k = j + 1; k < 12; k++) {
				threeCards.push_back(v[i]);
				threeCards.push_back(v[j]);
				threeCards.push_back(v[k]);
				if (isSet(threeCards)) {
					std::cout<<v[i]<<v[j]<<v[k]<<std::endl;
					num_sets++;
				}

				for (int l = 0; l < 3; l++)
				{
					threeCards.pop_back();
				}
			}
		}
	}
	std::cout<<"Total Number of Sets Found: "<<num_sets<<std::endl;

	deck.replace(v);
}


int findLargestNonSet(Deck deck)
{
	std::vector <Card> v;
	std::vector <Card> v_temp;
	std::vector <Card> threeCards;
	bool set = false;
	deck.deal(3,v);
	if (v.size() != 3)
		throw(3);

while (!set)
{
	deck.deal(1,v_temp);
	v.push_back(v_temp.front());
	for (int i = 0; i < v.size()-2; i++) {
		for (int j = i + 1; j < v.size()-1; j++) {
			for (int k = j + 1; k < v.size(); k++) {
				threeCards.push_back(v[i]);
				threeCards.push_back(v[j]);
				threeCards.push_back(v[k]);
				if (isSet(threeCards)) {
					set = true;
					break;
				}

				for (int l = 0; l < 3; l++)
				{
					threeCards.pop_back();
				}
			}
		}
	}
}

	deck.replace(v);


	return (int)v.size();

}

int main()
{
	try{
	Deck deck;
	int size;
	srand(time(NULL));
	deck.initializeDeck();
	deck.shuffle();

	playSet(deck);

	size = findLargestNonSet(deck);
	std::cout<<"Largest non set: "<<size<<std::endl;

	}
	catch (int e)
	{
		std::cout<<"ERROR! "<<e<<std::endl;
		exit(0);
	}
	return 0;
}


