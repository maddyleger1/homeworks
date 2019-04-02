/*
 * Node.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: maddy
 */

#include "Node.h"
#include "Card.h"


Node::~Node() {

}

void Node::swap(Node *cardNode)
{
	Card temp = nodeValue;
	nodeValue = cardNode->nodeValue;
	cardNode->nodeValue = temp;
}
