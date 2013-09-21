/* 
    File: dbms.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "dbms".

*/


#ifndef _manager_
#define _manager_

#include "Database.h"

class Manager {		//interface or system for managing a database
private:
	vector<Database> d;
	Database database;
public: 
	Manager();
	void setUpDatabase(std::vector<std::string> fileNames);
	void print();
	void test();
	void insertNewRelation (string name);
	//Functions to be called from parser if commands inputed by the user is valid
	//Wes
	void insertOne(string rel_name, vector<string> data);
	void insertFrom(string target, string source);
	void exit();
	bool remove_things(string rel_name, std::string s); 		//remove entities from database
	void update(string rel_name, Entity old, Entity new_e);
	void write(string rel_name);

	//Sid
	void createTable(string rel_name, vector<Attribute> attributes, vector<string> keys);
	void open(string rel_name);
	void close(string rel_name);
	void show(string rel_name);

	//Grace
	void select(string rel_name, string new_rel, Attribute attributes, std::string values);
	bool projection(vector<string> attr,string rel_nam, string new_name);
	void rename(string rel_name, int old_att_name, string new_att_name);
	void uni(string rel_name1, string rel_name2, string new_name);
	void difference(string rel_name1, string rel_name2, string new_name);
	void cross(string rel_name1, string rel_name2, string new_name);

};

#endif








