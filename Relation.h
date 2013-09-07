/* 
    File: Relation.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Relation".

*/


#ifndef _Relation_
#define _Relation_

#include <set>
#include "Attribute.h"
#include "Entity.h"

class Relation {	//a table with columns and rows
private:
	std::string name;
	std::vector<Attribute> relations_atts;
	std::vector<Entity> relations_ents;
	std::vector<std::string> keys;  //figure out what this does
	bool temp; //1 for temporary 0 for static

public:

	//Relation constructor defaults to empty temp table
	Relation(): temp(1) {}
	Relation(std::vector<Attribute> a): temp(1), relations_atts(a) {}
	bool create(std::string name_init, std::vector<Attribute> table_attributes, std::vector<std::string> key_list);  //returns zero on success; nonzero on failure
	bool remove(int index); //returns zero on success; nonzero on failure
	bool insert_entity(const Entity &e); //returns zero on success; nonzero on failure
	Relation& projection(std::vector<Attribute> a, std::string new_rel_name);
	void select();
	void update(); //update single entity** maybe idk
	void show();
	void open(std::string name);
	std::vector<Attribute> get_atts() const { return relations_atts; }
	Relation& uni(const Relation& other, std::string new_rel_name);
	Relation& difference(const Relation& other, std::string new_rel_name);
	Relation& cross(const Relation& other, std::string new_rel_name);
	
	//** Sort Utility Functions **//
	void sort_by(std::string primary_key);  // primary_key = name of attribute
	bool compare_entity(Entity a, Entity b);
	
	//** Basic Fetch Functions **//
	std::string get_name() const { return name; }
	bool if_temp() const { return temp; } //true for temporary false for static
	
	//** Basic Set Functions **//
	void set_name(std::string s) { name = s; } 
	void set_temp(bool b) { temp = b; } 
	void set_atts(std::vector<Attribute> a) { relations_atts = a; }
};

#endif



