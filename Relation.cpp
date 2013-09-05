/* 
    File: Relation.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Relation".

*/


#include <vector>
#include <string>
#include <algorithm>
#include "Relation.h"

bool Relation::create
(std::string name_init, std::vector<Attribute> table_attributes)
{
	name = name_init;
	relations_atts = table_attributes;
	return 0;
}

//Removes an entity from relations_ents 
bool Relation::remove(int index) {
	if (index >= relations_ents.size()) {
		return 1;
	}
	relations_ents.erase( (relations_ents.begin() + index) );
	return 0;
}

bool Relation::insert_entity(const Entity &e) {
	//check to ensure entity should belong in table
	relations_ents.push_back(e);
	return 0;
}

void Relation::select() {


}

void Relation::update() {


}

void Relation::show() {
		for (int i = 0; i < relations_atts.size(); ++i) {
			relations_atts[i].display();
		}
		for (int j = 0; j < relations_ents.size(); ++j) {
			relations_ents[j].display();
		}
}

Relation& Relation::uni(const Relation& other, std::string new_rel_name) {
	if ( ( new_rel_name == this->get_name() ) || ( new_rel_name == other.get_name() ) ) {
		printf("ERROR: Union Table Name Conflict (Thrown from Relation:uni(); \n");
	}
	Relation *r = new Relation();
	r->get_name() = new_rel_name;
	for(int i = 0; i < this->relations_ents.size(); ++i) {
		r->insert_entity(this->relations_ents[i]);
	}
	for(int j = 0; j < other.relations_ents.size(); ++j) {
		r->insert_entity(other.relations_ents[j]);
	}
	return (*r);
}

Relation& Relation::difference(const Relation& other, std::string new_rel_name) {

}

Relation& Relation::cross(const Relation& other, std::string new_rel_name) {

}

void Relation::sort_by(std::string primary_key) {
	for (int i = 0; i < relations_atts.size(); ++i) {
		if (primary_key == relations_atts[i].get_name()) {
			//sort based on index of primary key. std::sort(..) work in progress
			return;
		}
	}
}








