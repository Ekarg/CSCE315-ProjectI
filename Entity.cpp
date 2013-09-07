/* 
    File: Entity.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Entity".

*/

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
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


