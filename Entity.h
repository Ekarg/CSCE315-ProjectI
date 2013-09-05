/* 
    File: Entity.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Entity".

*/


#ifndef _Entity_
#define _Entity_

class Entity { 	//a row of a relation representing an object
private:

	std::vector<std::string> s;

public:

	
	//** Display Function **//
	void display();
	
	//** Basic Fetch Functions **//
	std::string get_elem(int index) const { return s[index]; }
	
	//** Basic Set Functions **//
	void insert_elem(std::string value, int index) { s[index] = value; }
	
};

#endif




