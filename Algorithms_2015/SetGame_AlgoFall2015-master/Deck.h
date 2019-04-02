/*
 * Deck.h
 *
 *  Created on: Sep 30, 2015
 *      Author: maddy
 */

#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include "Card.h"
#include "Node.h"

class Deck {
public:
	Deck();
	~Deck();

	void initializeDeck();
	void shuffle();
	void deal(int num, std::vector<Card> &v);
	void replace(std::vector<Card> &v);
	void addCardtoFront(const Card &card);
	Card grabFromFront();
	void printDeck();
	Node* getNode(int location);

	Node *headPtr = new Node;
	int len = 81;

private:

};

#endif /* DECK_H_ */
