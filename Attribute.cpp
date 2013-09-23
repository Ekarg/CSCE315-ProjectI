/* 
    File: Attribute.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Attribute".

*/
#include "Attribute.h"

Attribute::Attribute(std::string n, int in) throw (InvalidType, EmptyName){
	while(!n.empty()) //strip space
	{
		if(n.at(0) == ' ')
			n.erase(0,0);
		else
			break;
	}
	if(n.empty()) throw EmptyName();
	name=n;
	
	if( in > 5 || in < 0) throw InvalidType();
	ident=in;
 	}	 

bool operator== (Attribute &a, Attribute &b) {
	return ( ( a.get_ident() == b.get_ident() ) && ( a.get_name() == b.get_name() ) );
	}

void Attribute::display() {
	std::cout << get_name() << "(" << get_ident() << ")  \t";
	 }
	
