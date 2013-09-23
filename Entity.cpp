/* 
    File: Entity.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Entity".

*/

#include "Entity.h"

Entity::Entity(std::vector<std::string> data) {
	s=data;
}

void Entity::display() {
	for(int i = 0; i < s.size(); ++i) {
		std::cout << s[i] << '\t';
	}
	std::cout << std::endl;
}
string Entity::get_elem(int index) const throw(InvalidIndex)
{
	if(index >= s.size()) throw InvalidIndex();
	
	return s.at(index);
}
std::vector<std::string> Entity::getData() {
	return s;
}


