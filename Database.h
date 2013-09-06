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

class Database {	//a collection of relations
private:
	std::string name;
	std::vector<Relation> vec_relations;

public:

	//returns zero on success; nonzero on failure
	bool create_table(std::string name_init, std::vector<Attribute> table_attributes, std::vector<std::string> primary_key);
	//WATDO WITH PRIMARY KEY? HOW WE WANT TO IMPLEMENT?
	//void update();          ????????????
	//void insert_into(Relation, ); ????
	void remove(std::string rel_name); 		//remove relation from database
	void show(std::string rel_name);	//print relation to screen
	void open(std::string rel_name); 	//opens relation
	void write(std::string rel_name);	//writes relation to file
	void close(std::string rel_name);	//close relation given relation name
	void close(int i);					//close relation given index in vec_relations
	
	void exit();
	

};

#endif









