#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {
	//initialized variables
}

LinkedList::~LinkedList() {
	//Destructor clears list
	LinkedList::clear();
}

LinkedList::LinkedList(const LinkedList& source) {
	//Copy Constructor called
	Node* cur = source.head;
	Node* prev = nullptr;
	while (cur != nullptr) {
		Node* newNode = new Node(cur->data.id, cur->data.year, cur->data.month, cur->data.temperature);
		if (head == nullptr)
			head = newNode;
		if (prev != nullptr)
			prev->next = newNode;
		prev = newNode;
		cur = cur->next;
	}
	tail = prev;
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	//Copy Assignment called
	if (this != &source) {
		clear();
		Node* cur = source.head;
		Node* prev = nullptr;
		while (cur != nullptr) {
			Node* newNode = new Node(cur->data.id, cur->data.year, cur->data.month, cur->data.temperature);
			if (head == nullptr)
				head = newNode;
			if (prev != nullptr)
				prev->next = newNode;
			prev = newNode;
			cur = cur->next;
		}
		tail = prev;
	}
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	if (temperature == -99.99) {
		return;
	}
	Node* inc = new Node(location, year, month, temperature);

	if (head == nullptr) {
		head = inc;
		tail = inc;
		return;
	}

	if (*inc < *head) {
		inc->next = head;
		head = inc;
		return;
	}

	Node* cur = head;
	Node *prev = nullptr;
	while(cur != nullptr) {
		if (*inc < *cur) {
			inc->next = cur;
			prev->next = inc;
			return;
		}

		prev = cur;
		cur = cur->next;
	}

	prev->next = inc;
	tail = inc;
}

void LinkedList::clear() {
	//clear list
	while (head != nullptr) {
		Node* temp = head->next;
		delete(head);
		head = temp;
	}
}

Node* LinkedList::getHead() const {
	return head;
}

string LinkedList::print() const {
	std::stringstream outputString;

	Node* cur = head;

	while (cur != nullptr) {
		outputString << cur->data.id << " " << cur->data.year << " " << cur->data.month << " " << cur->data.temperature << '\n';
		cur = cur->next;
	}

	return outputString.str();
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	os << ll.print();
	return os;
}

double LinkedList::findAVG(string location, int year1, int year2) {
    bool validAVG = false;
    double sum = 0;
    int count = 0;
    
    //get values
    Node* cur = head;
    while (cur != nullptr) {
		if ((cur->data.id == location) && (cur->data.year >= year1) && (cur->data.year <= year2)) {
		    sum += cur->data.temperature;
		    validAVG = true;
		    count++;
		}
	    cur = cur->next;
	}
    
    if (!validAVG) {
        return -0.111111;
    }
    
    return (sum/count);
}

int LinkedList::findMODE(string location, int year1, int year2) {
    bool validMODE = false;
    vector<int> allNums;
    vector<int> nums;
    
    //Get values (fill vector)
    Node* cur = head;
    while (cur != nullptr) {
		if ((cur->data.id == location) && (cur->data.year >= year1) && (cur->data.year <= year2)) {
		    int rndval = round(cur->data.temperature);
		    allNums.push_back(rndval);  //add element to vector
		    //add element to nums vector if it isn't already in it
		    bool alreadyin = false;
		    for (int i = 0; i < nums.size(); i++) {
		        if (nums.at(i) == rndval) {
		            alreadyin = true;
		        }
		    }
		    if (!alreadyin) {
		        nums.push_back(rndval); 
		    }
		    validMODE = true;
		}
	    cur = cur->next;
	}
    
    if (!validMODE) {
        return 888888;
    }

    //Find mode
    int instances = 0;
    int mode = 0;
    for (int i = 0; i < nums.size(); i++) {
        int count = 0;
        for (int j = 0; j < allNums.size(); j++) {
            if (nums.at(i) == allNums.at(j)) {
                count++;
            }
        }
        //Update mode
        if (count > instances) {
            mode = nums.at(i);
            instances = count;
        }
        //Want largest mode
        if (count == instances) {
            if (nums.at(i) > mode) {     
                mode = nums.at(i);
                instances = count;
            }
        }
    }

    return mode;
}

