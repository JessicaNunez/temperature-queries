#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
#include <string>
#include "Node.h"

class LinkedList {
public:
	// Default constructor
	LinkedList();

	// Destructor
	~LinkedList();

	// Copy constructor
	LinkedList(const LinkedList& other);

	// Copy assignment
	LinkedList& operator=(const LinkedList& other);

	// Insert a record to the linked list
	void insert(std::string location, int year, int month, double temperature);
	
	//Find average temp of desired years & location
	double findAVG(std::string location, int year1, int year2);
	
	//Find mode temp of desired years & location
	int findMODE(std::string location, int year1, int year2);

	// Clear the content of this linked list
	void clear();

	// The functions below are written already. Do not modify them.
	std::string print() const;

	Node* getHead() const;

private:
	Node* head;
	Node* tail;
};

std::ostream& operator<<(std::ostream& os, const LinkedList& ll);
#endif
