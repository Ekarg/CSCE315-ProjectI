/* 
    File: Attribute.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Attribute".

*/


#ifndef _Attribute_
#define _Attribute_

#include "stdafx.h"

class Attribute {	//a named column of a relation
private:
	std::string name;
	int ident;  //identifier
	// 0 = INT, 1 = FLOAT, 2 = CHAR(n) 3 = VARCHAR(n)
	// 4 = DATE 5 = TIME
	
public:
	class InvalidType : public RuntimeException
	{
		public:
			InvalidType() : RuntimeException("Cannot create, invalid type") {}
	};
	
	class EmptyName : public RuntimeException 
	{
		public:
			EmptyName() : RuntimeException("Pleas type the attribute name") {}
	};
	
	Attribute();
	Attribute(std::string n, int in) throw (InvalidType, EmptyName);
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








