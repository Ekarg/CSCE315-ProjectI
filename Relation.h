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
using namespace std;
class Relation {	//a table with columns and rows
private:
	std::string name;
	std::vector<Attribute> relations_atts;
	std::vector<Entity> relations_ents;
	std::vector<std::string> keys;  //figure out what this does
	std::vector<int> key_indices;  //figure out what this does
	bool temp; //1 for temporary 0 for static

public:

	//Relation constructor defaults to empty temp table
	Relation(): temp(1) {}
	Relation(std::vector<Attribute> a): temp(1), relations_atts(a) {}
	bool create(std::string name_init, std::vector<Attribute> table_attributes, std::vector<std::string> key_list);  //returns zero on success; nonzero on failure
	bool remove(int index); //returns zero on success; nonzero on failure
	bool insert_entity(Entity e); //returns zero on success; nonzero on failure
	Relation& projection(std::vector<string> a, std::string new_rel_name);
	//void select();
	//void update(Entity old, Entity new_e); //update single entity** maybe idk
	void show();
	void open(std::string name);
	void display();
	void rename(string old, string new_name);
	void rename(int old, string new_name);
	std::vector<Attribute> get_atts() const { return relations_atts; }
	std::vector<std::string> get_keys() const {return keys; }
	std::vector<Entity> get_data() const {return relations_ents; }
	Relation& uni(const Relation& other, std::string new_rel_name);
	Relation& difference(const Relation& other, std::string new_rel_name);
	Relation& cross(const Relation& other, std::string new_rel_name);
	std::vector<Entity> select(Attribute a, std::string value);
	void update( vector<string> attriToChange, vector<string> newValue,  vector<string> attriToCheck,  vector<string> valuesToCheck);
	//** Sort Utility Functions **//
	void sort_by(std::string primary_key);  // primary_key = name of attribute
	bool compare_entity(Entity a, Entity b);
	
	//** Basic Fetch Functions **//
	std::string get_name() const { return name; }
	std::vector<Entity> get_rel_ents() const { return relations_ents; }
	std::vector<Attribute> get_rel_atts() const { return relations_atts; }
	bool if_temp() const { return temp; } //true for temporary false for static
	int find(Entity e);
	//** Basic Set Functions **//
	void set_name(std::string s) { name = s; } 
	void set_temp(bool b) { temp = b; } 
	void set_atts(std::vector<Attribute> a) { relations_atts = a; }
	void set_keys(std::vector<string> a) { keys= a; }
	void set_indices(std::vector<int> a) { key_indices = a; }
	void set_data(std::vector<Entity> e) { relations_ents = e; }
};

#endif



