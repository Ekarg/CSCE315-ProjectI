/* 
    File: dbms.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the function definitions for the class "dbms".

*/


#include <vector>
#include <string>
#include "dbms.h"


void dbms::rename_database(std::string new_dat_name) {
	d.set_name(new_dat_name);
}