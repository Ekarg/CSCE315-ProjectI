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
#include "Entity.h"
#include "time.h"
using namespace std;

void Database::insertNewRelation(string name) 
{
	temp.set_name(name);
	vec_relations.push_back(temp);
}

bool Database::create_table(string name_init, vector<Attribute> table_attributes, 
							vector<string> primary_key, string& output)
{		
	//Need to ensure that all attribute names are unique?
	Relation r;
	//watdo with primary key?
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == name_init) {
			//printf("ERROR: Attempted to create duplicate table name; \n");
			output.append("ERROR: Attempted to create duplicate table name;\n");
			return 1;
		}
	}
	if (! r.create(name_init, table_attributes, primary_key)) {
		//printf("ERROR: Failed to create table; \n");
		output.append("ERROR: Failed to create table;\n");
		return false;
	}
	
	vec_relations.push_back(r);
	return true;
}	

void Database::show(string rel_name, string& output) {
	//printf("size: %d\n", vec_relations.size());
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == rel_name) {
			vec_relations[i].display(output);
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


void Database::open(string rel_name, string& output) {
		ifstream tableFile;
		tableFile.open(rel_name+".txt");
		string attributes ="";
		if(tableFile.good())
			getline(tableFile, attributes);
		else{
			//printf("Error reading relation file\n");
			output.append("Error reading relation file\n");
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
			//printf("Error reading relation file\n");
			output.append("Error reading relation file\n");
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
		Relation r;
		r.create(rel_name, attr, keyData);
		while(tableFile.good())
		{
			getline(tableFile, s);
			vector<string> tokensData = tokenizer(s);	
			Entity e=Entity(tokensData);
			r.insert_entity(e);
		}
		vec_relations.push_back(r);
}

void Database::write(string rel_name, string& output) {
	//COMPILES BUT UNTESTED UNTIL EVERYTHING IS FULLY INTEGRATED
	int rel_index = -1;
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (rel_name == vec_relations[i].get_name()) {
			rel_index = i;
		}
	}
	if (rel_index == -1) {
		//printf("ERROR : Could not write nonexistent relation;\n");
		output.append("ERROR : Could not write nonexistent relation;\n");
		return;
	}
	std::string rel_filename = rel_name + ".txt";
	ofstream os(rel_filename);

	std::vector<Attribute> atts = vec_relations[rel_index].get_rel_atts();
	os << "Attributes: ";
	for (int q = 0; q < atts.size(); ++q) {
		os << atts[q].get_name() << ' ' << atts[q].get_ident() << ' ';
	}
	os << '\n';
	//GRACE : IF YOU'RE READING THIS, YOU'RE IN THE RIGHT PLACE!!
	srand(time(NULL));
	os << "Key: " << atts[( rand()%atts.size() )].get_name() << '\n';
	//GRACE : IF YOU'RE READING THIS, I CLEARLY HAVE NO IDEA WHAT I'M DOING!!
	//GRACE : SORRY!! -WES
	//found those momments at midnight, hahahaha --Sid
	std::vector<Entity> ents = vec_relations[rel_index].get_rel_ents();
	for (int j = 0; j < ents.size(); ++j) {
		std::vector<std::string> temp = ents[j].getData();
		for (int k = 0; k < temp.size(); ++k) {
			os << temp[k] << ' ';
		}
		os <<'\n';
	}
	os << '\n';
	os.close();
}

void Database::close(string rel_name, string&output) {
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
		if (rel_name == vec_relations[i].get_name()) {
			if (vec_relations[i].if_temp()) {
				vec_relations.erase( (vec_relations.begin() + i) );
				return;
			}
			else {
				write(rel_name, output);
				vec_relations.erase( (vec_relations.begin() + i) );
				return;
			}
		}
	}
}

void Database::close(int i, string &output) {
	if (vec_relations[i].if_temp()) {
		vec_relations.erase( (vec_relations.begin() + i) );
		return;
	}
	else {
		write(vec_relations[i].get_name(), output);
		vec_relations.erase( (vec_relations.begin() + i) );
		return;
	}
}

void Database::rename_table(std::string rel_name, std::string new_rel_name, string &output) {
	int hold;
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (vec_relations[i].get_name().compare(new_rel_name)==0) {
			//printf("ERROR: Renaming conflict, new name already in use; \n");
			output.append("ERROR: Renaming conflict, new name already in use; \n");
				return;
			}
		if (vec_relations[i].get_name().compare(rel_name)==0) {
				hold = i;
			}
		}
		vec_relations[hold].set_name(new_rel_name);
}

void Database::exit(string& output) {
	for (int i = 0; i < (int)vec_relations.size(); ++i) {
		close(i, output);
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

void Database::display(string& output) {
	for(int i=0; i<(int)vec_relations.size(); i++)
		vec_relations[i].display(output);
}

void Database::display(string rel_name, string& output) {
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{
			vec_relations[i].display(output);
		}
	}
}


/*void Database::test() {

	printf("***OPEN relations (animals, animals2, age) from text file and SHOW tables\n");
	open("animals");
	open("animals2");
	open("age");
	display();

	vector<string> ent;
	ent.push_back("Hugh");
	ent.push_back("4");
	ent.push_back("lion");
	Entity e=Entity(ent);
	printf("***Insert Entity\n");
	e.display();
	insert_into("animals", e);
	display();

	vector<string> ent2;
	ent2.push_back("Sam");
	ent2.push_back("3");
	ent2.push_back("bear");
	Entity e2=Entity(ent2);
	printf("***Delete Entity\n");
	e2.display();
	remove_entity("animals", e2);
	display();
	
	printf("***Selection test\n");
	printf("All animals where 'type==lion'\n");
	Attribute a = Attribute("type",0);
	string str = "lion";
	select("animals", "lions", a, str);
	display("lions");
	
	printf("***Projection test\n");
	printf("Attributes: name, type\n");
	vector<Attribute> att;
	att.push_back(Attribute("name", 0));
	att.push_back(Attribute("type", 0));
	projection(att, "animals", "names&types");
	display("names&types");
	
	printf("***Rename attribute 'tpye' to 'species' in lions\n");
	rename("lions","type","species");
	display("lions");

	printf("***Union test\n");
	uni("animals","animals2","union");
	display("union");

	printf("***Difference test\n");
	difference("animals","animals2","difference");
	display("difference");

	printf("***Cross Product test\n");
	cross("animals","age","cross");
	display("cross");

	printf("***Update test\n");
	vector<string> en;
	en.push_back("Hugh");
	en.push_back("4");
	en.push_back("lion");
	Entity e12=Entity(ent);
	vector<string> en2;
	en2.push_back("Hugh");
	en2.push_back("4");
	en2.push_back("tiger");
	Entity e13=Entity(en2);
	//update("animals",e12, e13);
	display("animals");

}*/

void Database::insert_into(string rel_name, Entity e) {
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
			vec_relations[i].insert_entity(e);
	}
}

bool Database::remove_entity(string rel_name, Entity e) {
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{
			int index = vec_relations[i].find(e);
			if(index == -1)
				return false;
			return vec_relations[i].remove(index);
		}
	}
	return false;
}

void Database::select(std::string rel_name, std::string new_rel, Attribute attributes, std::string values){
	cout<<rel_name<<endl<<new_rel;
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{
			vector<Entity> data =vec_relations[i].select(attributes, values);
			//printf("size: \n", data.size());
			temp.create(new_rel, vec_relations[i].get_atts(), vec_relations[i].get_keys());
			for(int j=0; j<(int)data.size(); j++)
				temp.insert_entity(data[j]);
			//vec_relations.push_back(r);
		}

	}

}

bool Database::projection(vector<string> att, string rel_name, string new_name) {
	if(rel_name == "\0")
	{
		if(att.size() > temp.get_atts().size())
		{
			printf("Error: More attributes listed than in relation. Please try again.\n");
			return false;
		}
		temp = temp.projection(att, new_name);
		return true;
	}
	else if(rel_name== "\0\0")
	{
		if(att.size() > temp2.get_atts().size())
		{
			printf("Error: More attributes listed than in relation. Please try again.\n");
			return false;
		}
		temp2 = temp2.projection(att, new_name);
		return true;
	}
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{
			//Relation r;
			temp = vec_relations[i].projection(att, new_name);
			return true;
			//vec_relations.push_back(r);
		}
	}
	return false;
}

void Database::rename(string rel_name, string old_att_name, string new_att_name) {
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{			
			vec_relations[i].rename(old_att_name, new_att_name);			
		}
	}
}

void Database::rename(string rel_name, int old_att_name, string new_att_name) {
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{			
			vec_relations[i].rename(old_att_name, new_att_name);			
		}
	}
}

void Database::uni(string rel_name1, string rel_name2, string new_name) {
	Relation r1;
	Relation r2;
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name1)==0)
		{			
			r1=vec_relations[i];			
		}
	}
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name2)==0)
		{			
			r2=vec_relations[i];			
		}
	}
	temp.create(new_name,r1.get_atts(), r1.get_keys());
	temp.set_data(r1.get_data());
	vector<Entity> data = r2.get_data();
	for(int i=0; i<(int)data.size(); i++)
	{
		temp.insert_entity(data[i]);
	}
	//vec_relations.push_back(temp);
}

void Database::difference(string rel_name1, string rel_name2, string new_name) {
	Relation r1;
	Relation r2;
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name1)==0)
		{			
			r1=vec_relations[i];			
		}
	}
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name2)==0)
		{			
			r2=vec_relations[i];			
		}
	}
	Relation r3;
	r3.create(new_name,r2.get_atts(), r2.get_keys());
	r3.set_data(r2.get_data());
	temp.create(new_name,r1.get_atts(), r1.get_keys());
	//r4.set_data(r1.get_data());
	vector<Entity> data = r1.get_data();
	for(int i=0; i<(int)data.size(); i++)
	{
		if(r3.insert_entity(data[i]))
			temp.insert_entity(data[i]);
	}
	//vec_relations.push_back(r4);
}

void Database::cross(string rel_name1, string rel_name2, string new_name) {
	//To Do: Enforce uniqueness by combining the keys in the two relations
	Relation r1;
	Relation r2;
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name1)==0)
		{			
			r1=vec_relations[i];			
		}
	}
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name2)==0)
		{			
			r2=vec_relations[i];			
		}
	}
	//Relation r3;
	vector<Attribute> att1 = r1.get_atts();
	vector<Attribute> att2 = r2.get_atts();
	vector<Attribute> att;
	for(int i=0; i<(int)att1.size(); i++)
		att.push_back(att1[i]);
	for(int i=0; i<(int)att2.size(); i++)
		att.push_back(att2[i]);
	vector<string> keys;
	/*vector<string> k1 = r1.get_keys();
	vector<string> k2 = r2.get_keys();
	for(int i=0; i<(int)k1.size(); i++)
		keys.push_back(k1[i]);
	for(int i=0; i<(int)k2.size(); i++)
		keys.push_back(k2[i]);
*/
	temp.create(new_name, att, keys); 
	vector<Entity> data1 = r1.get_data();
	vector<Entity> data2 = r2.get_data();
	for(int i=0; i<(int)data1.size(); i++)
	{
		for(int j=0; j<data2.size(); j++)
		{
			vector<string> sdata = data1[i].getData();
			vector<string> newData;
			for(int k=0; k<sdata.size(); k++)
			newData.push_back(sdata[k]);
			vector<string> s2data =  data2[j].getData();
			for(int k=0; k<s2data.size(); k++)
				newData.push_back(s2data[k]);
			Entity e = Entity(newData);
			temp.insert_entity(e);
		}
	}
	//vec_relations.push_back(r3);
}

void Database::update(string rel_name, vector<string> attriToChange, vector<string> newValue,  vector<string> attriToCheck,  vector<string> valuesToCheck, string& output){
	for(int i=0; i<(int)vec_relations.size(); i++)
	{
		if(vec_relations[i].get_name().compare(rel_name)==0)
		{	
			vec_relations[i].update(attriToChange,  newValue,  attriToCheck,  valuesToCheck, output);
		}
	}


}


Relation Database::find_rel(std::string s) {
	for (int i = 0; i < vec_relations.size(); ++i) {
		if (vec_relations[i].get_name() == s) {
			return vec_relations[i];
		}
	}
	//THIS CASE SHOULD NEVER HAPPEN
	Relation r;
	return r;
}