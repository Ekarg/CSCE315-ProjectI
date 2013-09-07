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
	std::vector<Database> d;
	Database database;
public: 
	Manager();
	void setUpDatabase(std::vector<std::string> fileNames);
};

#endif








