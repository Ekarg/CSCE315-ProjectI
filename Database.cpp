/* 
    File: Database.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Database".

*/


#include <vector>
#include <string>
#include "Database.h"

bool Database::create_table
(std::string name_init, std::vector<Attribute> table_attributes, std::vector<std::string> primary_key)
{	
	
	Relation r;
	//watdo with primary key?
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == name_init) {
			printf("ERROR: Attempted to create duplicate table name; \n");
			return 1;
		}
	}
	if (r.create(name_init, table_attributes)) {
		printf("ERROR: Failed to create table; \n");
		return 1;
	}
	vec_relations.push_back(r);
	return 0;
}	

void Database::show(std::string rel_name) {
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == rel_name) {
			vec_relations[i].show();
			return;
		}
	}
}

void Database::remove(std::string rel_name) {
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == rel_name) {
			vec_relations.erase( (vec_relations.begin() + i) );
			return;
		}
	}
}

void Database::open(std::string rel_name) {


}

void Database::write(std::string rel_name) {


}

void Database::close(std::string rel_name) {
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (rel_name == vec_relations[i].get_name()) {
			if (vec_relations[i].if_temp()) {
				vec_relations.erase( (vec_relations.begin() + i) );
				return;
			}
			else {
				write(rel_name);
				vec_relations.erase( (vec_relations.begin() + i) );
				return;
			}
		}
	}
}

void Database::close(int i) {
	if (vec_relations[i].if_temp()) {
		vec_relations.erase( (vec_relations.begin() + i) );
		return;
	}
	else {
		write(vec_relations[i].get_name());
		vec_relations.erase( (vec_relations.begin() + i) );
		return;
	}
}

void Database::rename_table(std::string rel_name, std::string new_rel_name) {
	int hold;
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == new_rel_name) {
			printf("ERROR: Renaming conflict, new name already in use; \n");
			return;
		}
		if (vec_relations[i].get_name() == rel_name) {
			hold = i;
		}
	}
	vec_relations[hold].set_name(new_rel_name);
}

void Database::exit() {
	for (int i = 0; i < vec_relations.size(); ++i) {
		close(0);
	}
}






