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
	for(int i=0; i<(int)keys.size(); i++)
	{
		for(int j=0; j<(int)relations_atts.size(); j++)
			if(keys[i].compare(relations_atts[j].get_name())==0)
			{
				key_indices.push_back(j);
				break;
			}
	}
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

int Relation::find(Entity e) {
	for(int i=0; i<(int)relations_ents.size(); i++)
	{
		bool equal = true;
		vector<string> elem = e.getData();
		vector<string> elem2 = relations_ents[i].getData();
		for(int j=0; j<(int)elem.size(); j++)
		{
			if(elem[j].compare(elem2[j])!=0)
			{
				equal = false;
			}
		}
		if(equal)
		{
			return i;
		}
	}
	return -1;
}

bool Relation::insert_entity(Entity e) {
	//check to ensure entity should belong in table
	vector<string> data=e.getData();
	for(int i=0; i<(int) relations_ents.size(); i++)
	{
		vector<string> cur_data=relations_ents[i].getData();
		for(int j=0; j<key_indices.size(); j++){
			if(data[key_indices[j]].compare(cur_data[key_indices[j]])==0)
				return false;
		}
	}

	relations_ents.push_back(e);
	return true;
}

vector<Entity> Relation::select(Attribute a, string value) {
	int index = 0;
	for(int i=0; i<(int)relations_atts.size(); i++)
		if(relations_atts[i].get_name().compare(a.get_name())==0)
		{
			index=i;
			break;
		}
	vector<Entity> match;
	for(int i=0 ; i<(int)relations_ents.size(); i++)
	{
		vector<string> data = relations_ents[i].getData();
		if(data[index].compare(value)==0)
			match.push_back(relations_ents[i]);
	}
	return match;
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
	r->set_name(new_rel_name);
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

Relation& Relation::projection(std::vector<string> a, std::string new_rel_name) {
	/*
	if (new_rel_name == this->get_name()) {
		printf("ERROR: Projection Table Name Conflict; \n");
	}
	*/
	vector<Attribute> attr;
	Relation *r = new Relation();
	r->set_name(new_rel_name);
	//r->set_atts(a);

	vector<int> indices;
	for(int i=0; i< (int)a.size(); i++)
	{
		for(int j=0; j<(int)relations_atts.size(); j++)
		{
			if(a[i].compare(relations_atts[j].get_name())==0)
			{
				attr.push_back(relations_atts[j]);
				indices.push_back(j);
				break;
			}
		}
	}
	r->set_atts(attr);
	vector<Entity> entities;
	for(int i=0; i<(int)relations_ents.size(); i++)
	{
		vector<string> data = relations_ents[i].getData();
		vector<string> new_data;
		for(int j=0; j<(int)indices.size(); j++)
			new_data.push_back(data[indices[j]]);
		Entity e = Entity(new_data);
		entities.push_back(e);
	}
	r->relations_ents=entities;
	/*	
	//create number of blank entities
	for (int m = 0; m < (int)relations_ents.size(); ++m) {
		Entity e;
		r->insert_entity(e);
	}
	//finds matching column and copies over elements by update()
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < (int)relations_atts.size(); ++j) {
			if (a[i] == relations_atts[j]) {
				for (int k = 0; k < relations_ents.size(); ++k) {
				//update entity with 
				}
			}
		}
	}
	*/
	return (*r);


}

void Relation::display() {
	cout<<"Relation: "<<name<<"\n";
	for(int i=0; i<(int)relations_atts.size();i++)
		cout<<relations_atts[i].get_name()<<'\t';
	cout<<"\n";
	for(int i=0; i<(int)relations_atts.size(); i++)
	{
		for(int j=0; j<relations_atts[i].get_name().length(); j++)
			cout<<"=";
		cout<<"\t";
	}
	cout<<"\n";
	for(int i=0; i<(int)relations_ents.size(); i++){
		relations_ents[i].display();
	}
	cout<<"\n";
}

void Relation::rename(string old, string new_name) {
	for(int i=0; i<(int) relations_atts.size(); i++)
		if(relations_atts[i].get_name().compare(old)==0)
			relations_atts[i].set_name(new_name);
}

void Relation::rename(int old, string new_name) {
	if(old<relations_atts.size())
		relations_atts[old].set_name(new_name);
}

