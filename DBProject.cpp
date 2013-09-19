// DBProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Entity.h"
#include "Attribute.h"
#include "Database.h"
#include "Manager.h"
#include "Relation.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/* Loads the database file which contains the file names that store the relations
	std::ifstream databaseFile;
	databaseFile.open("databaseFile.txt");
	std::vector<std::string> fileNames;
	while(databaseFile.good())
	{
		std::string str;
		std::getline(databaseFile, str);
		fileNames.push_back(str);
	}
	Manager m= Manager();
	m.test();
	*/
	
	/* Accepts input from a text file and tests the commands 
	string line;
	ifstream input("testInput.txt"); //input -- Make sure this is in the current folder
	ofstream output ("output.txt"); //output

	if(input.is_open() && output.is_open()) 
	{
		cout<<"******Writing output to output.txt\n";
		while (getline(input, line)) {
			cout<<"\n\nCommand: "<<line<<"\n";
			output<<"\n\nCommand: "<<line<<"\n";
			//cin>>input;			
			if(input == "Hello_World") {
				break;
			}
			Parser p = Parser();
			bool valid = p.validate(line);
			if(valid)
			{
				cout<<"Command is valid.\n";
				output<<"Command is valid.\n";
			}
			else
			{
				cout<<"Error: Command is NOT valid\n";
				output<<"Error: Command is NOT valid\n";
			}
		}
		output.close();
	}

	*/
	while (true) {
		cout<<"\n\nPlease input Command\n";
		string input;
		//cin>>input;
		getline(cin, input);
		if(input == "Hello_World") {
			break;
		}
		Parser p = Parser();
		bool valid = p.validate(input);
		if(valid)
		{
			cout<<"Command is valid.\n";			
		}
		else
		{
			cout<<"Error: Command is NOT valid\n";				
		}
	}


	return 0;
}

