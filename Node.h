#ifndef NODE
#define NODE

#include "TemperatureData.h"

struct Node {
	TemperatureData data;
	Node* next;

	// Default constructor
	Node(); 
	Node(std::string id, int year, int month, double temperature); 

	// This operator will allow you to just ask if a node is smaller than another
	//  rather than looking at all of the location, temperature and date information
	bool operator<(const Node& b);

	virtual ~Node() {}
};

#endif
