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
		string name = fileNames[i]+".txt";
	//	cout<<name;
		database.open(name);
	}
}

void Manager::print() {
	database.display();
}




