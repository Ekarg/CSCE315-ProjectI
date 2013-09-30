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
	cout << "*                                                             *"<<endl;
	cout << "***************************************************************"<<endl;

	cout<< "1 -- commands from text"<<endl;
	cout<< "2 -- commands from keyboard"<<endl;

	string choice;
	cin >> choice;

	while(choice != "1" && choice != "2")
	{
		cout << "Input error, try again"<<endl;
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
		cin >> line;

		while(line != "Exit")
		{
			bool valid = p.validate(line);
			if(valid)
			{
					//may need some change on output.
			}
			else
			{
				cout<<"Error: Command is NOT valid\n";
			}
			cin >> line;
		}
		p.validate("Exit");
	}

	p.writeTofile("output.txt");
}

int main()
{
	introduction();

	return 0;
}