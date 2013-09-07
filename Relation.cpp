/* 
    File: Relation.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Relation".

*/

#include "stdafx.h"
#include <vector>
#include <string>
#include <algorithm>
#include "Relation.h"
using namespace std;

bool Relation::create(std::string name_init, std::vector<Attribute> table_attributes, std::vector<std::string> key_list)
{
	name = name_init;
	relations_atts = table_attributes;
	keys=key_list;
	return 0;
}

//Removes an entity from relations_ents 
bool Relation::remove(int index) {
	if (index >= (int)relations_ents.size()) {
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
		for (int i = 0; i < (int)relations_atts.size(); ++i) {
			relations_atts[i].display();
		}
		for (int j = 0; j < (int)relations_ents.size(); ++j) {
			relations_ents[j].display();
		}
}

Relation& Relation::uni(const Relation& other, std::string new_rel_name) {
	if ( ( new_rel_name == this->get_name() ) || ( new_rel_name == other.get_name() ) ) {
		printf("ERROR: Union Table Name Conflict (Thrown from Relation:uni(); \n");
	}
	Relation *r = new Relation();
	r->get_name() = new_rel_name;
	r->set_atts(this->get_atts());
	for(int i = 0; i < (int) this->relations_ents.size(); ++i) {
		r->insert_entity(this->relations_ents[i]);
	}
	for(int j = 0; j < (int)other.relations_ents.size(); ++j) {
		r->insert_entity(other.relations_ents[j]);
	}
	return (*r);
}

Relation& Relation::difference(const Relation& other, std::string new_rel_name) {
	if ( ( new_rel_name == this->get_name() ) || ( new_rel_name == other.get_name() ) ) {
		printf("ERROR: Difference Table Name Conflict (Thrown from Relation:uni(); \n");
	}
	Relation placehold;
	Relation *r = new Relation();
	placehold.get_name() = new_rel_name;
	r->set_atts(this->get_atts());
	for(int i = 0; i < (int) this->relations_ents.size(); ++i) {
		placehold.insert_entity(this->relations_ents[i]);
	}
	for(int j = 0; j <(int)other.relations_ents.size(); ++j) {
		if ( placehold.insert_entity(other.relations_ents[j]) ) {
			r->insert_entity(other.relations_ents[j]);
		}
	}
	return (*r);
}

Relation& Relation::cross(const Relation& other, std::string new_rel_name) {
	Relation& r = Relation();
	return r;
}

void Relation::sort_by(std::string primary_key) {
	for (int i = 0; i < (int)relations_atts.size(); ++i) {
		if (primary_key == relations_atts[i].get_name()) {
			//sort based on index of primary key. std::sort(..) work in progress
			return;
		}
	}
}

Relation& Relation::projection(std::vector<Attribute> a, std::string new_rel_name) {
	if (new_rel_name == this->get_name()) {
		printf("ERROR: Projection Table Name Conflict; \n");
	}
	Relation *r = new Relation();
	r->get_name() = new_rel_name;
	r->set_atts(a);
		
	//create number of blank entities
	for (int m = 0; m < relations_ents.size(); ++m) {
		Entity e;
		r->insert_entity(e);
	}
	//finds matching column and copies over elements by update()
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < this->relations_atts.size(); ++j) {
			if (a[i] == relations_atts[j]) {
				for (int k = 0; k < relations_ents.size(); ++k) {
				//update entity with 
				}
			}
		}
	}
	return (*r);


}



