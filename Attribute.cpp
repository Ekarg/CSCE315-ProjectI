/* 
    File: Attribute.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Attribute".

*/


#include <string>
#include "Attribute.h"

void Attribute::display() {
	std::cout << get_name() << "(" << get_ident() << ")  \t";
}