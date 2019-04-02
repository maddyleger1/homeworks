/*
 * Deck.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: maddy
 */

#include "Deck.h"
#include "Card.h"
#include "Node.h"
#include <vector>
#include <algorithm>

Deck::Deck() {
	// TODO Auto-generated constructor stub

}

Deck::~Deck() {

}

void Deck::initializeDeck()
{
	int col=0, shp=0, pat=0;

	for (int i = 1; i <= len; i++)
	{
		Card card;
		if (i%3 == 0)
			card.setNum(3);
		else
			card.setNum(i%3);
		switch(col){
		case 0: card.setColor("Red");
				break;
		case 1: card.setColor("Green");
				break;
		case 2: card.setColor("Purple");
				break;
		}

		switch(shp){
		case 0: card.setShape("Diamond");
				break;
		case 1: card.setShape("Squiggle");
				break;
		case 2: card.setShape("Oval");
				break;
		}

		switch(pat){
		case 0: card.setPattern("Stripe");
				break;
		case 1: card.setPattern("Solid");
				break;
		case 2: card.setPattern("Blank");
				break;
		}

		if (i == 27 || i == 54){ //accounts for offset
			col++;
		}

		if (i%9 ==0){
			if (shp == 2)
				shp = 0;
			else
				shp++;
		}

		if (i%3 == 0 ){
			if (pat ==2)
				pat = 0;
			else
				pat++;
		}


		addCardtoFront(card);
	}
	//printDeck();

}

void Deck::shuffle()
{
	Node current;
	Card temp;
	int j;
	for (int i = len - 1; i > 0; i--)
	{
		j = rand() % (i + 1);
		getNode(i)->swap(getNode(j));
		}
	//printDeck();

}

void Deck::deal(int num, std::vector <Card> &v)
{
	for (int i = 0; i < num; i++)
		v.push_back(grabFromFront());
}

void Deck::replace(std::vector <Card> &v)
{
	for (int i = 0; i < (int)v.size(); i++)
		addCardtoFront(v[i]);
}

void Deck::addCardtoFront(const Card &card)
{
	Node *node = new Node(card, headPtr);
	headPtr = node;
}

Card Deck::grabFromFront()
{
	Card card;
	if (headPtr != NULL)
	{
		Node *node = headPtr;
		headPtr = headPtr->next;
		card = node->nodeValue;
		delete node;
	}
	return card;
}

void Deck::printDeck()
{
	Node *node = headPtr;
	while (node->next != NULL)
	{
		std::cout<<node->nodeValue;
		node = node->next;
	}
}

Node* Deck::getNode(int location) {
	Node *current = headPtr;
	while ((current->next != NULL) && (location > 1)) {
		current = current->next;
		location--;
	}
	return current;

}
