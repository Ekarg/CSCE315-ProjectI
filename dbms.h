/* 
    File: dbms.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the declaration for the class "dbms".

*/


#ifndef _dbms_
#define _dbms_

#include "Database.h"

class dbms {		//interface or system for managing a database
private:
	Database d;

public: 

	void rename_database(std::string new_dat_name);
	

};

#endif








