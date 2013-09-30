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

void Entity::display(string& output) {
	for(int i = 0; i < s.size(); ++i) {
		//std::cout << s[i] << '\t';
		output.append(s[i]);
		output.append("\t");
	}
	//std::cout << std::endl;
	output.append("\n");
}
string Entity::get_elem(int index) const throw(InvalidIndex)
{
	if(index >= s.size()) throw InvalidIndex();
	
	return s.at(index);
}
std::vector<std::string> Entity::getData() {
	return s;
}

bool operator== (Entity &a, Entity &b)
{
	vector<string> one = a.getData();
	vector<string> two = b.getData();

	if(one.size() != two.size())
		return false;

	for(int i = 0; i < one.size(); i ++)
	{
		if(one.at(i).compare(two.at(i)) == -1)
			return false;
	}

	return true;
}


