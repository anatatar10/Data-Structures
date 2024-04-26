#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->current = d.head;

	//BC: θ(1);
	//WC: θ(1);
	//AC: O(1);
}

void SMMIterator::first(){
	//TODO - Implementation

	this->current = this->map.head;

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}

void SMMIterator::next(){
	//TODO - Implementation
	if (!valid()) {
		throw exception();
	}
	else
	{
		this->current = this->current->next();
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}

bool SMMIterator::valid() const{
	//TODO - Implementation
	return (this->current != nullptr);

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}

TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (!valid()) {
		throw exception();
	}
	else
	{
		return this->current->element();
	}

	//BC: θ(1);
	//WC: θ(n);
	//AC: O(n);
}


