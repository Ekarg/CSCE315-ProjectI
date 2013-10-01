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
#include "parser.h"

void introduction()
{
	cout << "***************************************************************"<<endl;
	cout << "*                                                             *"<<endl;
	cout << "*            Welcome to our world-class mini database         *"<<endl;                                            
	cout << "*        Authors: Grace Coffman, Sidian Wu, Wesley Tang       *"<<endl;
	cout << "*                 Department of Computer Science              *"<<endl;
	cout << "*                     Texas A&M University                    *"<<endl;
	cout << "***************************************************************"<<endl;

	cout << endl;
	cout<<"please select which mode you want."<<endl;
	cout<< endl;
	cout<< "1 -- commands from text."<<endl;
	cout<< "2 -- commands from keyboard."<<endl;

	string choice;
	cin >> choice;

	while(choice != "1" && choice != "2")
	{
		cout << "Input error, try again."<<endl;
		cout << endl;
		cin >> choice;
	}

	string line;
	Parser p = Parser();

	if(choice == "1")
	{
		string filename;
		ifstream input;

		cout << "Input file name: ";
		cin >> filename;
		input.open(filename, std::ifstream::in);

		if(input.is_open())
		{
			while (getline(input, line)) 
			{
				cout<<"\n\nCommand: "<<line<<"\n";
				//cin>>input;			
				if(input == "Hello_World")	
				{
					break;
				}
			
				bool valid = p.validate(line);
				if(valid)
				{
					//may need some change on output.
				}
				else
				{
				cout<<"Error: Command is NOT valid\n";
				}
			}
		}
		else
		{
			cout<< "Invalid file"<<endl;
		}
	}
	else
	{
		cout << endl;
		cout << "Please type command from your keyboard now!"<<endl;
		cout << endl;

		cin.sync(); //to clear cin's buffer
		getline(cin, line);

		while(line != "Exit")
		{
			bool valid = p.validate(line);
			if(valid)
				cout<< "command accepted! Go ahead for another command or type \"Exit\" to quit."<<endl;
			else
				cout<<"Error: Command is NOT valid\n";

			cin.sync();
			cout << endl;
			getline(cin, line);
		}
		p.validate("Exit;");
	}

	p.writeTofile("output.txt");
}

int main()
{
	introduction();
	//Parser* p = new Parser();
	//p->validate("CREATE TABLE animals (name VARCHAR, kind VARCHAR, years INTEGER) PRIMARY KEY (name, kind);");
	//p->validate("INSERT INTO animals VALUES FROM (Joe, cat, 4);");
	//p->validate("INSERT INTO animals VALUES FROM (Spot, dog, 10);");
	//p->validate("SHOW animals;");
	//p->validate("Exit;");
	//p->writeTofile("output.txt");

	return 0;
}