#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = this->bag.first;
	this->currentFreq = 1;
	

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

void BagIterator::first() {
	this->current = this->bag.first;
	this->currentFreq = 1;

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}


void BagIterator::next() {
	if (!valid())
	{
		throw exception();
	}
	else
	{
		if(currentFreq < this->bag.e[this->current].second)
		{ 
			currentFreq = currentFreq + 1;
		}
		else
		{
			this->current = this->bag.nextLink[this->current];
			currentFreq = 1;
		}
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}


bool BagIterator::valid() const {
	return (this->current != -1);

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}



TElem BagIterator::getCurrent() const
{
	if (!valid()) {
		throw exception();
	}
	else {
		return this->bag.e[this->current].first;
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}
