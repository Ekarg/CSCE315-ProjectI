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
#include <stack>
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

vector<string> Parser::queryTokenizer(string line) {
	char* str = new char[line.length()+1];
	char* next = NULL;
	vector<string> tokens;
	for(int i=0; i<(int)line.length(); i++)
		str[i]=line.at(i);
	str[line.length()]=NULL;
	char * start = NULL;
	start = strtok_s(str, " ,", &next);
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

bool Parser::validate(string input) {
	
	vector<string> tokens = tokenizer(input);
	if(!tokens.size()>0)
		return false;
	if(!matchingParenthesis(tokens))
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
		//printf("Open command parsed.\n\n");

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
		//printf("Close command parsed.\n\n");

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
		//printf("Write command parsed.\n\n");

		//Call manager function
		manager.write(rel_name);

		return true; 
	}
	else if(exit.compare(first) == 0)
	{
		//printf("Exit command parsed.\n\n");

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
				vector<string> expr;
				for (int i = 0; i < tokens.size(); ++i) {
					expr.push_back(tokens[i]);
				}
				//cout << "expr == " << expr << endl;
				evaluate(expr);
				manager.insertFrom(rel_name);
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
					if (args[k][args[k].size()-1] == '"') {
						args[k].erase(args[k].end()-1);
					}
					if (args[k][args[k].size()-1] == ';') {
						args[k].erase(args[k].end()-1);
					}
					//cout << args[k] << endl;
				}
				manager.insertOne(rel_name, args);
			}
			//printf("Insert command parsed.\n\n");

			//Call manager function
		
			return true; 
		}
		else return false;
	}
	else if( (del.compare(first) == 0) && (tokens[1] == "FROM") && (tokens[3] == "WHERE") && (tokens.size() > 4) )
	{
		//printf("Delete command parsed.\n\n");
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
		if (!handleQuery(expr)) {
			printf("Invalid Expression in delete command;\n");
			return false;
		}
		//difference(table1, table2);
		//printf("Delete command parsed.\n\n");

		//Call manager function
		manager.remove_things(rel_name);

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
		string rel_name = tokens[1];
		vector<string> attriToChange;
		vector<string> newValues;
		
		while(wher.compare(tokens[i]) != 0 && (i+3)<tokens.size())
		{
			if(equal.compare(tokens[i+1]) != 0)
			{
				//printf("1\n");
				return false;
			}
			attriToChange.push_back(tokens[i]);
			newValues.push_back(tokens[i+2]);
			i+=3;
		}
	
		string semi = ";";
		i++;
		if(i>=tokens.size() )
		{
			cout<<"Error: conditions expected after WHERE\n";
			return false;
		}
		vector<string> attriToCheck;
		vector<string> valuesToCheck;
		while((i+2)<tokens.size())
		{
			if(equal.compare(tokens[i+1]) != 0)
			{
				return false;
			}
			attriToCheck.push_back(tokens[i]);
			valuesToCheck.push_back(tokens[i+2]);
			i+=2;
		}
		
	//	printf("Update command parsed.\n\n");
		manager.update(rel_name, attriToChange,newValues,attriToCheck,valuesToCheck);
		//Call manager function
		//manager.update(tokens[1], ); 
		//THERE'S LIKE ONLY ONE EXAMPLE OF THIS COMMAND
		//BEING USED IN ANY OF THE EXAMPLE COMMANDS
		//NOT SURE IF UPDATING A SINGLE ENTITY OR
		//UPDATING A SINGLE ATTRIBUTE IN EACH ENTITY IN
		//A RELATION WHERE A SPECIFIC CONDITION IS MET
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
		//printf("Show command parsed.\n\n");

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
		vector<Attribute> attr;
		while(x<tokens.size()-1 && numStart != 0)
		{
			//Get attributes here
			if(end.compare(tokens[x]) == 0)
				numStart--;
			else if(start.compare(tokens[x]) == 0)
				numStart++;
			else {
				string name = tokens [x];
				string type = tokens [x++];
				int num = 0;
				if(type == "VARCHAR")
					num = 3;
				else if(type == "INTEGER")
					num = 1;
				else if(type == "BOOL")
					num=2;
				attr.push_back(Attribute(name, num));
			}
			x++;
		
		}
		if( x>=tokens.size())
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
		string keyString ="";
		while(x<tokens.size() && numStart != 0)
		{
			//Get attributes here
				if(end.compare(tokens[x]) == 0)
				numStart--;
			else if(start.compare(tokens[x]) == 0)
				numStart++;
			else {
				keyString+=tokens[x];

			}
			x++;
		}
		vector<string> keys = queryTokenizer(keyString);
		manager.createTable(rel_name, attr, keys);
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
	//	printf("Create command parsed.\n\n");
		return true; 
	}
	else // Query 
	{
		//Grace Coffman	
		if(tokens.size()<4)
			return false;
	//	if(tokens.size() == 4)
	//		return true;
		string arrow = "<-";
		string start = "(";
		string end = ")";
		string semi = ";";
		if(arrow.compare(tokens[1])!=0)
			return false;
		tokens.erase(tokens.begin());
		tokens.erase(tokens.begin());
		evaluate(tokens);

		manager.insertNewRelation(first);
	}

		//tokens.erase(tokens.end());
		return false;
}


bool Parser::evaluate(vector<string> tokens) 
{
	string start = "(";
	string end = ")";
	int j=0;
	string keys[] = {"union", "rename","cross", "project","select","rename"};
	int numKeys = 5;
	stack<string> commands;
		while(j<(tokens.size()-1)) 
		{
			string send = " ";
			int numStart=0;
			bool match = false;
		for(int i=0; i<numKeys; i++)
		{
			if(keys[i].compare(tokens[j]) == 0)
			{
				match = true;
				send = " " + tokens[j];
				//we have found a keyword, now need to find the expression to evaluate
				int x=j+1;
				if(x>=tokens.size())
					return false;
				if(start.compare(tokens[x]) != 0)
					return false;
				numStart++;
				x++;
				while(x<(tokens.size()-1))
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
							/*
							bool check = validate(send+" ;");		
							if(!check)
								return false;
							else 
							{
								j = x+1;
								break;
							}
							*/
							commands.push(send);
							j=x+1;
							break;
						}
					}
						send=send+" " + tokens[x];	
						x++;
				}
			}
			if(match)
				break;
		}
		if(!match)
		{
			commands.push(tokens[j]); 
			j++;
		}

	}
	//	string end = ")";
	//	string start = "(";
		while(commands.size() > 0) 
		{
			string s = commands.top();
			commands.pop();
			//cout<<s<<endl;
			handleQuery(s);
		}
}



bool Parser::matchingParenthesis(vector<string> tokens) 
{
	int start = 0;
	int end =0; 
	string open = "(";
	string close = ")";
	for(int i=0; i<tokens.size(); i++)
	{
		if(open.compare(tokens[i]) == 0)
			start ++;
		else if(close.compare(tokens[i]) == 0)
			end ++;
	}
	if(start != end) 
		return false;
	return true;
}

bool Parser::handleQuery(string input) {
	string open = "(";
	string close = ")";
	if(close.compare(input)==0)
		//igonore
			return true;
	else if(open.compare(input)==0) 
		//ignore
		return true;
	else if(input == "+")
	{
		add=true;
		return true;
	}
	else if(input == "-")
	{
		diff=true;
		return true;
	}
	else if(input == "*")
	{
		product=true;
		return true;
	}
	//not a parenthesis
	//If it is only one token, treat it like a relation name and set it as the relation the query will exectute on
	//     after the query is compeleted, be sure to reset the name back to null
	//If it MORE than one token, do the cases for the possible keywords
	vector<string> tokens = queryTokenizer(input);
	string first = tokens[0];
	if(tokens.size() == 1)
	{
		if(product || diff || add)
		{
			rel_name2 = first;
			arithmetic();
		}
		else
			rel_name=first; //found a relation name
		//rel_name="\0";
		return true;
	}
	else if(projection.compare(first) == 0)
	{
		tokens.erase(tokens.begin());
		string s = " "; //this function needs to be changed so that it doesn't accept a second string -> do this later
		bool valid = false;
		if(product || diff || add)
		{
			valid = manager.projection(tokens, rel_name2, s);
			arithmetic();
		}
		else
			valid = manager.projection(tokens, rel_name, s);
		rel_name="\0";
		return valid;
	}
	else if(rename.compare(first) == 0)
	{
		for(int i=1; i<tokens.size(); i++)
			manager.rename(rel_name, i-1, tokens[i]);
		rel_name="\0"; 
		return true;
	}
	else if(select.compare(first) == 0) 
	{
		//Need to do select
		if(tokens.size() < 5)
			return false;
		string attribute = tokens[1];
		string value = tokens[4];
		Attribute a = Attribute(attribute, 0);
		cout<<rel_name;
		manager.select(rel_name, "\0" , a, value);
		rel_name="\0";
	}
	return false;
}


bool Parser::arithmetic() 
{
	if(add) //union
	{
		manager.uni(rel_name, rel_name2, " ");
		add = false;
	}
	else if(diff) //difference 
	{
		manager.difference(rel_name, rel_name2, " ");
		diff=false;
	}
	else //product
	{
		manager.cross(rel_name, rel_name2, " ");
		product = false;
	}

	return true;

}


