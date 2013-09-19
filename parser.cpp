/* 
    File: parser.cpp

    Authors: Grace Coffman, Sidian Wu, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the implementation for database parser.

*/

#include "stdafx.h"
#include <vector> 
#include <string>
#include <iostream>
#include "parser.h"
using namespace std;

vector<string> Parser::tokenizer(string line) {
	for(int i=0; i<line.length(); i++)
	{
		if(line.at(i)=='('||line.at(i)=='='||line.at(i)==')')
		{
			if(i!=0)
				line.insert(i," ");
			if(i!=(line.length()-2))
				line.insert(i+2," ");
			i+=2;
		}
		if(line.at(i)==';')
		{
			line.insert(i," ");
			i+=2;
		}
	}
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
		tokens.push_back(s);
		start = strtok_s(NULL, " ", &next);
	}
	//START TROUBLESHOOTING ITERATOR	
	/*
	for (int i = 0; i < tokens.size(); ++i) {
			cout << tokens[i];
	}
	*/
	//END TROUBLESHOOTING ITERATOR		

	return tokens;

}

//WE NEED A RECURSIVE DESCENT PARSER FOR PARSING AND HANDLING EXPRESSIONS 

bool Parser::validate(string input) {
	
	vector<string> tokens = tokenizer(input);
	if(!tokens.size()>0)
		return false;
	string first = tokens[0];
	string s = ";";
	if(s.compare(tokens[tokens.size()-1]) != 0)
	{
		printf("; expected\n");
		return false;
	}
	if(open.compare(first) == 0)
	{
		// SID WU
		if(tokens.size()!=3)
			return false;
		if(tokens[2].back()!=';')
			return false;
		string rel_name = tokens.at(1);
		printf("Open command parsed.\n\n");

		//Call manager function
		manager.open(rel_name);

		return true; 
	}
	else if(close.compare(first) == 0)
	{
		// SID WU
		if(tokens.size()!=3)
			return false;
		if(tokens[2].back()!=';')
			return false;
		string rel_name = tokens.at(1);
		printf("Close command parsed.\n\n");

		//Call manager function
		manager.close(rel_name);

		return true; 
	}
	else if(write.compare(first) == 0)
	{
		// GRACE COFFMAN
		if(tokens.size() != 3)
			return false;
		if(tokens[2].back()!=';')
			return false;
		string rel_name = tokens.at(1);
		printf("Write command parsed.\n\n");

		//Call manager function
		manager.write(rel_name);

		return true; 
	}
	else if(exit.compare(first) == 0)
	{
		printf("Exit command parsed.\n\n");
		// exit();

		//Call manager function
		manager.exit();

		return true; 
	}
	else if( (insert.compare(first) == 0)) 
	{
		if((tokens[1] == "INTO") && (tokens[3] == "VALUES") && (tokens[4] == "FROM") && tokens.size()>5)
		{
			string rel_name = tokens[2];
			tokens.erase(tokens.begin(), tokens.begin()+5);
			// Case for "INSERT INTO points VALUES FROM RELATION (select (z2 > 0) dots_to_points);"
			if (tokens[0] == "RELATION") {
				tokens.erase(tokens.begin());
				string expr;
				for (int i = 0; i < tokens.size(); ++i) {
					expr += tokens[i];
				}
				cout << "expr == " << expr << endl;
				//parse_expr(expr);
				//union(table1, table2);
			}
			// Case for "INSERT INTO dots VALUES FROM (0, 0, 0);"
			else {
				string expr;
				for (int i = 0; i < tokens.size(); ++i) {
					expr += tokens[i];
				}
				vector<string> args;
				for (int j = 0; j < expr.size(); ++j) {
					if (expr[j] == '(') {
						continue;
					}
					if (expr[j] == '"') {
						continue;
					}
					string a;
					while ( (expr[j] != ',') && (j < expr.size()) && (expr[j] != ')') ) {
						a += expr[j];
						++j;
					}
					args.push_back(a);
				}
				for (int k = 0; k < args.size(); ++k) {
					cout << args[k] << endl;
				}
				//create entity with values from args
				//check if entity is allowable into table rel_name
				//insert entity into tablr rel_name
			}
			printf("Insert command parsed.\n\n");

			//Call manager function
		
			return true; 
		}
		else return false;
	}
	else if( (del.compare(first) == 0) && (tokens[1] == "FROM") && (tokens[3] == "WHERE") && (tokens.size() > 4) )
	{
		printf("Delete command parsed.\n\n");
		string rel_name = tokens[2];
		tokens.erase(tokens.begin(), tokens.begin()+4);
		string expr;
		for (int i = 0; i < tokens.size(); ++i) {
			expr += tokens[i];
		}
//		cout << "expr == " << expr << endl;
		// SEND REMAINING VECTOR (WHICH SHOULD CONTAIN AN ATOMIC EXPRESSION)
		// TO BE PARSED RECURSIVELY INTO A TABLE AND THEN SUBTRACTED FROM
		// THE THE TABLE rel_name. ASSUMED ERROR CATCHING FOR EXPRESSION PASRING
		// TO BE HANDLED IN parse_expr. ??????????????????????????????
		// parse_expr(expr);
		// difference(table1, table2);
		printf("Delete command parsed.\n\n");

		//Call manager function

		return true; 
	}
	else if(update.compare(first) == 0)
	{
		// GRACE COFFMAN
		if(tokens.size() < 10)
			return false;
		string last = tokens[tokens.size() - 1];
		if(last.back() != ';')
			printf("Error: No semi-colon\n");
		string set = "SET";
		if(set.compare(tokens[2]) != 0)
			return false;
		string wher = "WHERE";
		if(wher.compare(tokens[3]) == 0)
			return false;
		int i=3;
		string equal = "=";
		while(wher.compare(tokens[i]) != 0 && (i+3)<tokens.size())
		{
			if(equal.compare(tokens[i+1]) != 0)
			{
				printf("1\n");
				return false;
			}
			i+=3;
		}
		string semi = ";";
		i++;
		if(i>=tokens.size() )
		{
			cout<<"Error: conditions expected after WHERE\n";
			return false;
		}
		while((i+2)<tokens.size())
		{
			if(equal.compare(tokens[i+1]) != 0)
			{
				return false;
			}
			i+=2;
		}
		printf("Update command parsed.\n\n");

		//Call manager function

		return true; 
	}
	else if(show.compare(first) == 0)
	{
		// SID WU
		if(tokens.size()!=3)
			return false;
		if(tokens[2].back() != ';')
			return false;
		string rel_name = tokens.at(1);
		printf("Show command parsed.\n\n");

		//Call manager function
		manager.show(rel_name);

		return true; 
	}
	else if(create.compare(first) == 0)
	{
		/*
		// SID WU
		string* rel_name;
		string* primary_key;
		vector<Attribute>* attr_list;
 		// SID WU
			if(tokens.at(1) == "TABLE")	
			{
			//throw
			string rel_name = new string(tokens.at(2));
			
			int i = 3;
			
			if(tokens.at(i) != "(")
				//throw exception
			else
			{
				//a new attribute constructure funciton is needed
				attr_list = new vector<Attribute>;
				
				while(tokens.at(i + 1) != ")")
				{					//case when input primary key 
					bool has_key = false;
					if(tokens.at(i + 1) == "PRIMARY" ) //input primary key
					{
						if(has_key == false)
						{
							i = i +2;
							primary_key = new string(tokens.at(i));
							key = key->substring(1, key.length - 2); //strip parenthesis
						}
						else // syntax error
						{
							//throw exception 
					}
					}

					//case when input attributes
					Attribute temp = Attribute(tokens.at(++i), tokens.at(++i));
					attr_list.push_back(temp);		
				if(tokens.at(i + 1) == ",")
					continue; // input next attribute
				else 
				{
					// case when we have some other key words.
				}
			}
		}
		else if(tokens.at(1) == "DATABASE")
		{
			string db_name = tokens.at(2);		}
		else //Error operation
		{
		//	throw exception
		}
		*/
		if(tokens.size() < 8)
			return false;
		string table = "TABLE";
		if(table.compare(tokens[1]) != 0) 
			return false;
		string rel_name = tokens[2];
		string start = "(";
		string end = ")";
		int x=3; 
		if(start.compare(tokens[3]) != 0)
		{
			printf("( expected \n");
			return false;
		}
		int numStart = 1;
		x++;
		while(x<tokens.size() && numStart != 0)
		{
			//Get attributes here
			if(end.compare(tokens[x]) == 0)
				numStart--;
			if(start.compare(tokens[x]) == 0)
				numStart++;
			x++;
		
		}if( x>=tokens.size())
		{
			printf("Missing )\n");			
			return false;
		}
		string primary = "PRIMARY";
		string key = "KEY";
		if(primary.compare(tokens[x]) != 0)
		{
			printf("Keyword PRIMARY expected\n");
			return false;
		}
		x++;
		if( x>=tokens.size())
			return false;
		if(key.compare(tokens[x]) != 0)
		{
			printf("Keyword KEY expected\n");
			return false;
		}
		x++;
		if( x>=tokens.size())
			return false;
		if(start.compare(tokens[x]) != 0)
		{
			printf("( expected \n");
			return false;
		}
		numStart = 1;
		x++;
		while(x<tokens.size() && numStart != 0)
		{
			//Get attributes here
			if(end.compare(tokens[x]) == 0)
				numStart--;
			if(start.compare(tokens[x]) == 0)
				numStart++;
			x++;
		}
		if( x>=tokens.size())
			return false;
		string semi = ";";
		if(semi.compare(tokens[x]) != 0)
		{
			printf("; expected\n");
			return false;
		}
		x++;
		if( x<tokens.size())
			return false;
		printf("Create command parsed.\n\n");
		return true; 
	}
	else if(uni.compare(first) == 0)
	{
		return true;

	}
	else if(difference.compare(first) == 0)
	{
		return true;
	}

	else if(select.compare(first) == 0)
	{
		return true;
	}
	else if(projection.compare(first) == 0)
	{
		return true;
	}
	else if(rename.compare(first) == 0)
	{
		return true;
	}
	else // Query 
	{
		string keys[] = {"union", "rename","cross", "project","select","rename"};
		int numKeys = 5;
		//Grace Coffman	
		if(tokens.size()<3)
			return false;
		if(tokens.size() == 3)
			return true;
		string arrow = "<-";
		string start = "(";
		string end = ")";
		string semi = ";";
		if(arrow.compare(tokens[1])!=0)
			return false;
		int j=2;
		while(j<tokens.size()) 
		{
			string send = " ";
			int numStart=0;
		for(int i=0; i<numKeys; i++)
		{
			if(keys[i].compare(tokens[j]) == 0)
			{
				send = " " + tokens[j];
				//we have found a keyword, now need to find the expression to evaluate
				int x=j+1;
				if(x>=tokens.size())
					return false;
				if(start.compare(tokens[x]) != 0)
					return false;
				numStart++;
				x++;
				while(x<tokens.size())
				{
					if(start.compare(tokens[x]) == 0)
					{
						numStart++;
					}
					else if(end.compare(tokens[x]) == 0)
					{
						numStart--;
						if(numStart == 0)
						{
							bool check = validate(send+" ;");		
							if(!check)
								return false;
							else 
							{
								j = x+1;
								break;
							}
						}
					}
						send=send+" " + tokens[x];	
						x++;
				}
				j=x+1;
				if(semi.compare(tokens[j])==0)
				{
					printf("Query command parsed.\n\n");
					return true;
				}
				break;
			}
		}

		}

	}
	return false;
}