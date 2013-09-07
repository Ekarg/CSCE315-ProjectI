/* 
    File: Attribute.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Attribute".

*/


#ifndef _Attribute_
#define _Attribute_

#include <iostream>

class Attribute {	//a named column of a relation
private:
	std::string name;
	int ident;  //identifier
	// 0 = string, 1 = int, 2 = bool, etc.
	
public:
	Attribute();
	Attribute(std::string n, int in);
	//** Display Function **//
	void display();

	//** Basic Fetch Functions **//
	std::string get_name() const { return name;}
	int get_ident() const { return ident;}
	
	//** Basic Set Functions **//
	void set_name(std::string s) { name = s; }
	void set_ident(int i) { ident = i; }

	//** Overloaded Operators **//
	friend bool operator== (Attribute &a, Attribute &b);

};

#endif








