/* 
    File: Entity.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Entity".

*/


#ifndef _Entity_
#define _Entity_
#include <vector>

class Entity { 	//a row of a relation representing an object
private:

	std::vector<std::string> s;

public:
	Entity() {}
	Entity(std::vector<std::string> data);
	//** Display Function **//
	void display();
	
	//** Basic Fetch Functions **//
	std::string get_elem(int index) const { return s[index]; }
	std::vector<std::string> getData();
	//** Basic Set Functions **//
	void insert_elem(std::string value, int index) { s[index] = value; }
	
};

#endif




