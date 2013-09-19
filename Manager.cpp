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

void Manager::setUpDatabase(vector<string> fileNames) {
	for(int i=0; i<(int)fileNames.size(); i++)
	{
		string name = fileNames[i];
	//	cout<<name;
		database.open(name);
	}
}

void Manager::print() {
	database.display();
}


void Manager::test() {
	database.test();
}


// Wes
void Manager::insertOne(string rel_name, vector<string> data)
{



}

void Manager::insertFrom(string target, string source)
{



}

void Manager::exit() 
{




}

bool Manager::remove_entity(string rel_name, Entity e) 		//remove relation from database
{


	return false;
}

void Manager::update(string rel_name, Entity old, Entity new_e)
{


}

void Manager::write(string rel_name)
{



}

//Sid
void Manager::createTable(string rel_name, vector<Attribute> attributes, vector<string> keys) 
{


}

void Manager::open(string rel_name)
{



}

void Manager::close(string rel_name)
{


}

void Manager::show(string rel_name) 
{


}

//Grace 
void Manager::select(string rel_name, string new_rel, Attribute attributes, std::string values)
{


}

void Manager::projection(vector<Attribute> attr,string rel_nam, string new_name)
{


}

void Manager::rename(string rel_name, string old_att_name, string new_att_name)
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