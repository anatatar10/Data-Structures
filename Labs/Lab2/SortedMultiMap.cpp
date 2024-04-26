#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

Node::Node(TElem e, PNod next)
{
	// we initialize the node with the given data and the
	// pointer to the next node

	this->e.first = e.first; //TKey 
	this->e.second = e.second; //TValue 
	this->nextNode = next; // next of the node 

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

TElem Node::element()
{
	//returns the data from the node

	return this->e;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

PNod Node::next()

// returns the pointer to the next node from the node
{
	return this->nextNode;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation

	//we initialize the head of the list
	head = nullptr;

	//we initialize the relation between keys with the given one
	this->relation = r;

	//we initialize the length of the list
	this->length = 0;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation

	PNod newNode = new Node(make_pair(c,v), nullptr); //initialize a new node with the given pair key - value
	if (head == nullptr && length == 0) // check if the mulimap is empty or not
	{
		length++;
		this->head = newNode; // the list is empty, so the newNode is added and becomes the head of the list
	}
	else if (relation(newNode->element().first, this->head->element().first)) //key is "less than" the key from the head
	{
		// the newNode is added in front of the list
		length++;
		newNode->nextNode = head; // newNode points to the current head of the list
		this->head = newNode; // the newNode becomes the head of the list
	}
	else
	{
		// in this case the newNode needs to be added after the head, 
		//so we go through the list to find the node after which we add the newNode
		PNod currentNode = this->head; 

		// we go through the list until we get to the last node 
		//or the currentNode has the key smaller than the one to be added
		while (currentNode->next() != nullptr && !relation(newNode->element().first, (currentNode->next())->element().first))
		{
			currentNode = currentNode->next();
		}
		// the newNode is inserted after the currentNode
		this->length++;
		newNode->nextNode = currentNode->next(); // newNode gets the addres to which the currentNode is pointing
		currentNode->nextNode = newNode; // currentNode points to the newNode
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}

bool SortedMultiMap::rel(TKey c1, TKey c2)
{
	// the function will return true if "c1 <= c2", otherwise false

	if (c1 <= c2)
		return true;
	return false;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation

	//the function will return a vector with values of type TValue belonging to a given key

	vector<TValue> values;
	PNod current = this->head;
	while (current != nullptr && relation(current->element().first, c)) // we stop traversing the list when we get to a node whose key is greater than the given one
	{
		if (current->element().first == c) // if we found a node with the given key, we add the value belonging to the key in the vector
			values.push_back(current->element().second);
		current = current->next();
	}
	return values;

	//BC: θ(n);
	//WC: θ(n);
	//AC: O(n);
	
}

bool SortedMultiMap::remove(TKey c, TValue v) {

	PNod currentNode = this->head;
	PNod previousNode = nullptr;
	while (currentNode != nullptr && relation(currentNode->element().first, c)) { // we stop traversing the list when we get to a node whose key is greater than the given one
		if (currentNode->element().first == c && currentNode->element().second == v) // if we found the node to be deleted, we need to check its position in the list
		{
			if (previousNode == nullptr && currentNode != nullptr) { //We have to delete the first node of the list, the head
				this->head = this->head->next(); // the head becomes the node which is after the one to be deleted
				delete currentNode;
				length--;
				return true; // return true if the node was found and deleted
			}
			else if(currentNode != nullptr) //We have to delete the node after the one pointed by previous
			{
				previousNode->nextNode = currentNode->next(); // previousNode will point to the node after the one to be deleted
				delete currentNode;
				length--;
				return true; // return true if the node was found and deleted
			}
		}
		else {
			previousNode = currentNode; // we traverse the list
			currentNode = currentNode->next();
		}
	}
	return false;

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}


int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->length;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation

	return (length == 0);

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);

}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	//We free the memory allocated for the nodes of the SLL
	while (head != nullptr) {
		PNod p = head;
		head = head->nextNode;
		delete p;
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}
