/* 
    File: Entity.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Entity".

*/


#ifndef _Entity_
#define _Entity_

#include "stdafx.h"

class Entity { 	//a row of a relation representing an object
private:

	std::vector<std::string> s;

public:
	class InvalidIndex : public RuntimeException
	{
		public:
			InvalidIndex() : RuntimeException("No data in that row")
			{}
	};
	Entity() {}
	Entity(vector<string> data);
	//** Display Function **//
	void display();
	
	//** Basic Fetch Functions **//
	string get_elem(int index) const throw (InvalidIndex);
	//{ return s[index]; }
	std::vector<std::string> getData();
	//** Basic Set Functions **//
	void insert_elem(std::string value, int index) { s[index] = value; }
	
};

#endif




