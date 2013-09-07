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
	m.setUpDatabase(fileNames);
	
	return 0;
}

