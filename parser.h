/* 
    File: parser.h

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the header for the database parser. 

*/

#ifndef _DATABASE_PARSER_
#define _DATABASE_PARSER_

#include <string>
#include <vector> 
#include "Manager.h"
using namespace std;
/*
	For Monday's submission, you need to include the following DBMS functions:

	create table
	insert into
	delete
	selection
	projection
	renaming
	set union
	set difference
	cross product
	update
	show

	You don't need to implement the following:

	open
	close
	write
	exit
*/
class Parser {
public:

	string open;
	string close;
	string write;
	string exit;
	string insert;
	string del;
	string create;
	string projection;
	string rename;
	string uni;
	string difference;
	string cross;
	string update;
	string show;
	string select;
	string into;
	Manager manager;

	Parser() { 
		open = "OPEN"; 
		close = "CLOSE"; 
		write = "WRITE"; 
		exit = "EXIT"; 
		insert = "INSERT"; 
		del = "DELETE"; 
		create = "CREATE";
		projection = "project"; 
		rename = "rename"; 
		uni = "union"; 
		difference = "differnce"; 
		cross = "cross"; 
		update = "UPDATE"; 
		show = "SHOW"; 
		select="select"; 
		manager = Manager();
	}
	vector<string> tokenizer(string input);
	bool validate(string input);


};

#endif