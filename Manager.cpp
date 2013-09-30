/* 
    File: dbms.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "dbms".

*/


#include "stdafx.h"
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Manager::Manager() {
}

void Manager::insertNewRelation (string name) 
{
	database.insertNewRelation(name);
}


void Manager::setUpDatabase(vector<string> fileNames) {
	for(int i=0; i<(int)fileNames.size(); i++)
	{
		string temp;
		string name = fileNames[i];
	//	cout<<name;
		database.open(name, temp);
		cout << temp << endl;
		info.append(temp);
	}
}

void Manager::print() {
	string temp;
	database.display(temp);
	cout<< temp << endl;
	info.append(temp);
}


void Manager::test() {
	database.test();
}


// Wes
void Manager::insertOne(string rel_name, vector<string> data) //Command : INSERT INTO dots VALUES FROM (0, 0, "X");;
{
	Entity *e = new Entity(data);
	database.insert_into(rel_name, *e);
	//init e on heap -> insert into rel_name

}

void Manager::insertFrom(string rel_name)
{
	//I won't lie, this function is not very robust. 
	//temp is created from handleQuery() called in the parser where this is called
	//This design feels poor and this function shouldn't be called anywhere without
	//first being prefaced with handleQuery();
	insertNewRelation(rel_name);
	

	return;
}

void Manager::exit() //Command : EXIT;
{
	string temp;
	database.exit(temp);
	cout << temp << endl;
	info.append(temp);
	//database.exit() calls database.close(int i) for each table in
	//database that isn't temp
}

bool Manager::remove_things(string rel_name) //Command : DELETE FROM XXX WHERE XXX;
{
	//READ COMMENTS IN insertFrom();
	vector<Entity> temp = database.find_rel("temp").get_rel_ents();
	for (int i = 0; i < temp.size(); ++i) {
		Entity e = temp[i];
		database.remove_entity(rel_name, e);
	}
	return true;
}

void Manager::update(string rel_name, vector<string> attriToChange, vector<string> newValue,  vector<string> attriToCheck,  vector<string> valuesToCheck)
{   
	//NOT FINISHED :------------------------------------------:
	//THERE'S LIKE ONLY ONE EXAMPLE OF THIS COMMAND
	//BEING USED IN ANY OF THE EXAMPLE COMMANDS
	//NOT SURE IF UPDATING A SINGLE ENTITY OR
	//UPDATING A SINGLE ATTRIBUTE IN EACH ENTITY IN
	//A RELATION WHERE A SPECIFIC CONDITION IS MET
	string temp;
	database.update(rel_name, attriToChange, newValue,  attriToCheck, valuesToCheck, temp);
	cout << temp;
	info.append(temp);
}

void Manager::write(string rel_name) //Command : WRITE XXX;
{
	string temp;
	database.write(rel_name, temp);
	cout << temp << endl;
	info.append(temp);
	//simple enough, eh?

}

//Sid
void Manager::createTable(string rel_name, vector<Attribute> attributes, vector<string> keys) 
{
	string temp;
	database.create_table(rel_name, attributes, keys, temp);
	cout << temp << endl;
	info.append(temp);
}

void Manager::open(string rel_name)
{
	string temp;
	database.open(rel_name, temp);
	cout << temp << endl;
	info.append(temp);
}

void Manager::close(string rel_name)
{
	string temp;
	database.close(rel_name, temp);
	cout << temp << endl;
	info.append(temp);
}

void Manager::show(string rel_name) 
{
	string temp;
	database.show(rel_name, temp);
	cout << temp << endl;
	info.append(temp);
}

//Grace 
void Manager::select(string rel_name, string new_rel, Attribute attributes, std::string values)
{
	database.select(rel_name, new_rel, attributes, values);
}

bool Manager::projection(vector<string> attr,string rel_name, string new_name)
{
	return database.projection(attr, rel_name, new_name);
}

void Manager::rename(string rel_name, int old_att_name, string new_att_name)
{


}

void Manager::uni(string rel_name1, string rel_name2, string new_name)
{



}

void Manager::difference(string rel_name1, string rel_name2, string new_name)
{



}

void Manager::cross(string rel_name1, string rel_name2, string new_name)
{



}

void Manager::writeToFile(string filename)
{
	ofstream file(filename);
	file << this->info;
}