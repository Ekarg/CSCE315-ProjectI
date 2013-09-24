/* 
    File: Database.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "Database".

*/


#ifndef _Database_
#define _Database_

#include "Relation.h"
using namespace std;
class Database {	//a collection of relations
private:
	std::string name;
	std::vector<Relation> vec_relations;

public:
	Relation temp; //this Relation is the Relation that stores the result of a query
	Relation temp2; //this Relation is the Relation that stores the result of a query
	//returns zero on success; nonzero on failure
	bool create_table(std::string name_init, std::vector<Attribute> table_attributes, std::vector<std::string> primary_key);
	//WATDO WITH PRIMARY KEY? HOW WE WANT TO IMPLEMENT?
	//void update();          ????????????
	void insert_into(string rel_name, Entity e);
	void remove(std::string rel_name); 		//remove relation from database
	bool remove_entity(std::string rel_name, Entity e); 		//remove relation from database
	void show(std::string rel_name);	//print relation to screen
	void rename_table(std::string rel_name, std::string new_rel_name);
	void select(std::string rel_name, std::string new_rel, Attribute attributes, std::string values);
	bool projection(std::vector<string> attr,std::string rel_nam, std::string new_name);
	void rename(std::string rel_name, std::string old_att_name, std::string new_att_name);
	void rename(std::string rel_name, int old_att_name, std::string new_att_name);
	void uni(string rel_name1, string rel_name2, string new_name);
	void difference(string rel_name1, string rel_name2, string new_name);
	void cross(string rel_name1, string rel_name2, string new_name);
	void update(string rel_name, vector<string> attriToChange, vector<string> newValue,  vector<string> attriToCheck,  vector<string> valuesToCheck);
	//void remove(std::string name, Expr e); 	//where Expr = parsed expression
	//void show(std::string rel_name);			//show elements in relation that match atomic expression
	void open(std::string rel_name); 	//opens relation
	void write(std::string rel_name);	//writes relation to file
	void close(std::string rel_name);	//close relation given relation name
	void close(int i);					//close relation given index in vec_relations
	vector<string> tokenizer(string line);
	void exit();
	void display();
	void display(string rel_name);
	void insertNewRelation(string name);
	void insertNewRelation(Relation r);
	//** Basic Fetch Functions **//
	std::string get_name() const { return name; }
	std::vector<Relation> get_rel() const { return vec_relations; }
	Relation find_rel(std::string s); 
	
	//** Basic Set Functions **//
	void set_name(std::string s) { name = s; } 
	void test();

};

#endif









