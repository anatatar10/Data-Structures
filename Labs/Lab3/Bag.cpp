#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	//the list is empty
	first = -1;
	last = -1;
	previousLink[0] = -1;
	//we initialize the list of free space
	for (int i = 0; i < cp - 1; i++)
	{
		nextLink[i] = i + 1;
		previousLink[i] = i - 1;
	}
	nextLink[cp - 1] = -1;
	firstEmpty = 0;

	//BC: θ(cp);
	//WC: θ(cp);
	//AC: O(cp);
	
}

int Bag::allocate()
{
	// we create space for a new element in the array
	int i = firstEmpty;
	firstEmpty = nextLink[firstEmpty];
	return i;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

void Bag::deallocate(int i)
{
	nextLink[i] = firstEmpty;
	previousLink[i] = -1;
	if (firstEmpty != -1)
		previousLink[firstEmpty] = i;
	firstEmpty = i;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

int Bag::createNode(TElem e)
{
	int positionOfElement = this->findPosition(e); //finding the position of the element in the array
	if (positionOfElement != -1) //if the element is already in the array, we increase the frequency
	{
		this->e[positionOfElement].second++;
		return -1;
	}
	else
	{
		// the element hasn't been found and we need to allocate a new space for it
		int i = allocate(); // create a new space for the element
		this->e[i].first = e; 
		this->e[i].second = 1;
		nextLink[i] = -1;
		previousLink[i] = -1;
		return i;
	}

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);

}

int Bag::findPosition(TElem e)
{
	// we find the index of the given element in the array
	int currentPos = this->first;
	while (currentPos != -1)
	{
		if (this->e[currentPos].first == e)
		{
			return currentPos;
		}
		currentPos = this->nextLink[currentPos];
	}
	return -1;

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}



void Bag::add(TElem elem) {
	
	int newElem = this->createNode(elem); 
	if (newElem != -1) //if we reach this case, it means that the element to be added, hasn't been found in the array, and we need to add it 
	{
		nextLink[newElem] = -1;
		previousLink[newElem] = last; // we link the element with the current tail
		if (first == -1) 
		{
			first = newElem; // if the bag is empty, the element becomes the head
		}
		else
		{
			nextLink[last] = newElem; //we link the previous tail with the new element
		}
		last = newElem; //the tail becomes the new element
	}
}


bool Bag::remove(TElem elem) 
{
	//bool found = false;
	//int current = this->first;
	//int prev = -1;
	//while (current != -1 && !found) //we search for the element to be deleted in the array
	//{
	//	if (this->e[current].first == elem)
	//	{
	//		found = true;
	//	}
	//	else {
	//		prev = current;
	//		current = this->nextLink[current];
	//	}
	//}
	//if (!found) // if the element is not in the list, we return false
	//{
	//	return false;
	//}
	//else 
	//{
	//	if (current != -1)
	//	{
	//		if (current == first)
	//		{
	//			if (current == last) // case when the element is the head and tail (1 element)
	//			{
	//				first = -1;
	//				last = -1;
	//			}
	//			else // case when the element is the head
	//			{
	//				first = nextLink[first]; // the second element becomes the head 
	//				previousLink[first] = -1;
	//			}
	//		}
	//		else if (current == last) // case when element is the tail
	//		{
	//			last = previousLink[last]; // the element before the tail becomes the tail
	//			nextLink[last] = -1;
	//		}
	//		else if(this->e[current].second == 1) // if the element to be removed has only one occurence, we deallocate the node and link the neighbours node
	//		{
	//			previousLink[nextLink[current]] = previousLink[current];
	//			nextLink[previousLink[current]] = nextLink[current];
	//			deallocate(current);
	//		}
	//	}
	//	if (this->e[current].second > 1) // the element appears more than one, so we just decrease the frequency
	//	{
	//		this->e[current].second--;
	//	}

	//	return true;
	//}
	//return false;

	int foundPosition = this->findPosition(elem);
	if (foundPosition == -1)
	{
		return false;
	}
	else
	{
		if (this->e[foundPosition].second > 1)
		{
			this->e[foundPosition].second--;
			return true;
		}
		else
		{
			if (foundPosition != -1)
			{
				if (foundPosition == first)
				{
					if (foundPosition == last) // case when the element is the head and tail (1 element)
					{
						first = -1;
						last = -1;
					}
					else // case when the element is the head
					{
						first = nextLink[first]; // the second element becomes the head 
						previousLink[first] = -1;
					}
				}
				else if (foundPosition == last) // case when element is the tail
				{
					last = previousLink[last]; // the element before the tail becomes the tail
					nextLink[last] = -1;
				}
				else  // if the element to be removed has only one occurence, we deallocate the node and link the neighbours node
				{
					previousLink[nextLink[foundPosition]] = previousLink[foundPosition];
					nextLink[previousLink[foundPosition]] = nextLink[foundPosition];
					deallocate(foundPosition);
				}
				return true;
			}
		}
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
	
}


bool Bag::search(TElem elem) const {
	bool found = false;
	int current = this->first;
	while (current != -1 && !found) { // we search in the list for the element
		if (this->e[current].first == elem) {
			found = true;
			return true; // we return true if we found the element
		}
		else {
			current = this->nextLink[current];
		}
	}
	return false; // we return false if we reached the end of the array and didn't find the element

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}

int Bag::nrOccurrences(TElem elem) const {
	int current = this->first;
	while (current != -1) { // we search for the element
		if (this->e[current].first == elem) { // when we found the element, we return the frequency
			return this->e[current].second;
		}
		current = this->nextLink[current];
	}
	return 0;
	
	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}


int Bag::size() const {
	int n = 0;
	int current = this->first;
	while (current != -1) // we go through the list and add the frequencies of each element
	{
		n = n+ this->e[current].second;
		current = this->nextLink[current];
	}
	return n;

	//BC: θ(n);
	//WC: θ(n);
	//AC: O(n);
	
}


bool Bag::isEmpty() const {
	return (size() == 0);
	// sau return(first == -1);

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
	
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}


Bag::~Bag() {
	for (int i = 0; i < cp; i++)
	{
		deallocate(i);
	}

	//BC: θ(cp);
	//WC: θ(cp);
	//AC: O(cp);
}

