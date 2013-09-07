/* 
    File: Database.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "Database".

*/

#include "stdafx.h"
#include <vector>
#include <string>
#include <set>
#include "Database.h"
#include <iostream>
#include <fstream>
using namespace std;

bool Database::create_table(string name_init, vector<Attribute> table_attributes, 
							vector<string> primary_key)
{		
	//Need to ensure that all attribute names are unique?
	Relation r;
	//watdo with primary key?
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == name_init) {
			printf("ERROR: Attempted to create duplicate table name; \n");
			return 1;
		}
	}
	if (r.create(name_init, table_attributes, primary_key)) {
		printf("ERROR: Failed to create table; \n");
		return 1;
	}
	
	vec_relations.push_back(r);
	return 0;
}	

void Database::show(string rel_name) {
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
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


void Database::open(string rel_name) {
		ifstream tableFile;
		tableFile.open(rel_name);
		string attributes ="";
		if(tableFile.good())
			getline(tableFile, attributes);
		else{
			printf("Error reading relation file\n");
		}
		//Tokenize the first line, ignoring the first token which will just be "Attributes: "
		vector<string> tokens = tokenizer(attributes);
		vector<Attribute> attr;
		for(int i=1; i<(int)tokens.size(); i++) {
			//cout<<tokens[i+1];
			//cout<<tokens[i]+"\n";
			Attribute a = Attribute(tokens[i],std::stoi(tokens[i+1]));
			attr.push_back(a);
			i++;
		}		
		/*
		* Get keys
		*/
		string keyLine = " ";
		if(tableFile.good())
			getline(tableFile, keyLine);
		else{
			printf("Error reading relation file\n");
		}
		vector<string> keyData = tokenizer(keyLine);
		vector<set<string> > keys;
		for(int i=1; i<(int)keyData.size(); i++)
		{
			string key = keyData[i];
			//Set<string> newSet(
		}
		string s =" ";
		int numFields = attributes.size();
		vector<Entity> entities;
		while(tableFile.good())
		{
			getline(tableFile, s);
			vector<string> tokensData = tokenizer(s);	
			Entity e=Entity(tokensData);
			entities.push_back(e);
		}
		create_table(rel_name, attr, keyData);
		//vec_relations.push_back(r);
}

void Database::write(string rel_name) {


}

void Database::close(string rel_name) {
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
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
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
		close(0);
	}
}

vector<string> Database::tokenizer(string line) {
	char* str = new char[line.length()+1];
	char* next = NULL;
	vector<string> tokens;
	for(int i=0; i<(int)line.length(); i++)
		str[i]=line.at(i);
	str[line.length()]=NULL;
	char * start = NULL;
	start = strtok_s(str, " ", &next);
	while(start!=NULL)
	{
		string s(start);
		tokens.push_back(start);
		start = strtok_s(NULL, " ", &next);
	}
	return tokens;

}