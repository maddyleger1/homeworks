/*
 * Node.h
 *
 *  Created on: Oct 1, 2015
 *      Author: maddy
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include "Card.h"

class Node {
public:
	Node() = default;
	Node(const Card &item, Node *nextNode = NULL) : nodeValue(item), next(nextNode){};
	~Node();
	Card nodeValue;
	Node *next;
	void swap(Node *cardNode);

private:

};

#endif /* NODE_H_ */
