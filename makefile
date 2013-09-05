# 			MAKEFILE 
#		  CSCE 315-503
#		Database Project
#		   Fall 2013
#		  --Authors--
#		 Grace Coffman
#	 	  Sidian Wu
#		 Wesley Tang

all: dbmain

Entity.o: Entity.cpp Entity.h 
	g++ -c -g Entity.cpp

Attribute.o: Attribute.cpp Attribute.h 
	g++ -c -g Attribute.cpp
	
Relation.o: Relation.cpp Relation.h 
	g++ -c -g Relation.cpp
	
Database.o: Database.cpp Database.h 
	g++ -c -g Database.cpp
	
dbms.o: dbms.cpp dbms.h 
	g++ -c -g dbms.cpp

dbmain: dbmain.cpp Entity.o Attribute.o Relation.o Database.o dbms.o
	g++ -o dbmain dbmain.cpp Entity.o Attribute.o Relation.o Database.o dbms.o

clean:
	/bin/rm -f *.o dbmain

	