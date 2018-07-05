// TestExecutive.cpp : Defines the entry point for the console application.
//
/////////////////////////////////////////////////////////////////////
//                                                                    //
//                                                                    //
// source     : Jim Fawcett
// Project    : Key value database                                //                               
//Author     :    Tejaswi Nimmagadda                            //
//Language   :    C++                                          //
//Platform   :    Dell, Windows 10                            //
//                                                            //
//                                                           //
////////////////////////////////////////////////////////////////
/*
Maintenance History:
====================
ver 1.0

Required files :
==============

PersistHelp.h, PersistHelp.cpp,
*   Convert.h, Convert.cpp,
*   CppProperties.h, CppProperties.cpp,
*   XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp,
*  ---- required to build XmlDocument from file or string ----
*   XmlParser.h, XmlParser.cpp,
*   XmlElementParts.h, XmlElementParts.cpp,
*   ITokenizer.h, Tokenizer.h, Tokenizer.cpp,

Purpose
=======
To demonstrate requirements


*/

#include "stdafx.h"

#include "../NoSqlDb/NoSqlDb.h"

#include <iostream>
#include <ctime>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include <unordered_map> //standard library header file to use the built-in unordered map features
#include <string>        //standard library header file to manipulate strings
#include <sstream>      //standard library Header providing string stream classes
#include <ostream>      //standard library header to write sequence of characters and other kinds of data
#include <vector>       //standard library header file for using the vector functions
#include <iomanip>      //standard libraray header providing parametric manipulators
#include <fstream>      //standard library header to operate on files
#include <iostream>     //standard library Header that defines the standard input/output stream objects
#include "../CppProperties/CppProperties.h" //header file which includes methods that Define read/write and read only properties
#include "../Persist/PersistHelp.h"         // Header file which includes methods to persist objects to XML file 
#include "../XmlDocument/XmlDocument/XmlDocument.h" // header file to include methods required for xml processing
#include <regex>


using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
	


	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";

	NoSqlDb<StrData> db;  // instatiating NoSqlDb class


	Element<StrData> elem1;  // instatiating NoSqlDb class
	elem1.name = "elem1"; 
	elem1.category = "test";  // metadata
	elem1.data = "elem1's StrData";//data
	elem1.child.push_back("elem2");//children
    // time date initialized using constructor

	db.save(elem1.name, elem1);  // saving database



	Element<StrData> elem2;        // instatiating NoSqlDb class
	elem2.name = "elem2";
	elem2.category = "test";       // metadata
	elem2.data = "elem2's StrData";//data
	elem2.child.push_back("elem3");//children
	// time date initialized using constructor

	db.save(elem2.name, elem2);    //saving database

	Element<StrData> elem3;          // instatiating NoSqlDb class
	elem3.name = "elem3";
	elem3.category = "test";         // metadata
	elem3.data = "elem3's StrData";  //data
	//timeDate initialized using constructor
	db.save(elem3.name, elem3);  // saving database

	

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();       // Retrieving elements from NoSqlDb<string>
	for (Key key : keys)            
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";


	std::cout << "\n  Deleting key";
	std::cout << "\n =================================\n";

	db.deleteKey(elem1.name); //deleting key

	std::cout << "\n After Deleting key " << std::endl;

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys1 = db.keys();     // retrieving ellements after deleting key

	for (Key key : keys1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";

	std::cout << "\n Adding key" << std::endl;
	db.addKey(elem1.name, elem1);           // adding key
	

	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";

	std::cout << "\n After editing/updating " << std::endl;
	std::cout << "\n =================================\n";

	elem3.name = "elem3";            //editing data
	elem3.category = "test";
	elem3.data = "new data";

	db.update(elem3.name, elem3); // updating database after editing


	for (Key key : keys)       // retrievig elements from database after updating 
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}




	std::cout << "\n  Creating and saving NoSqlDb elements with int data";
	std::cout << "\n ----------------------------------------------------\n";

	NoSqlDb<intData> idb;

	Element<intData> ielem1;      //Creating and saving NoSqlDb elements with int data
	ielem1.name = "elem1";
	ielem1.category = "test";
	ielem1.data = 1;
	
	//timeDate initialized using constructor



	idb.save(ielem1.name, ielem1);      // saving elements in data base

	Element<intData> ielem2;        //Creating and saving NoSqlDb elements with int data
	ielem2.name = "elem2";
	ielem2.category = "test";
	ielem2.data = 2;
	//timeDate initialized using constructor

	idb.save(ielem2.name, ielem2);        // saving elements in data base

	Element<intData> ielem3;             //Creating and saving NoSqlDb elements with int data
	ielem3.name = "elem3";
	ielem3.category = "test";
	ielem3.data = 3;
	//timeDate initialized using constructor
	

	idb.save(ielem3.name, ielem3);     //saving elements in data base

	Element<intData> ielem4;           //Creating and saving NoSqlDb elements with int data
	ielem4.name = "elem4";
	ielem4.category = "test";
	ielem4.data = 4;
	//timeDate initialized using constructor

	idb.save(ielem4.name, ielem4);      //saving elements in data base

	std::cout << "\n  Retrieving elements from NoSqlDb<int>";
	std::cout << "\n ---------------------------------------\n";

	std::cout << "\n  size of idb = " << idb.count() << "\n";
	Keys ikeys = idb.keys();             //Retrieving elements from NoSqlDb<int>
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}
	std::cout << "\n\n";
	NoSqlDb<std::string> db1;                              
	std::cout << db1.Publish(db);    //Persisting Database Content to Xml file

	std::cout << "\n";
	std::cout << "\n Queries" << std::endl;            //demonstrating queries
	std::cout << "\n Category related query" << std::endl;  //demonstrating category related query
	std::cout << "\n Retrieving all elements that contain a specific string in their category name" << std::endl;
	std::vector<std::string> s = db.categoryQuery(db, "test");
	for (unsigned int i = 0; i < s.size(); i++)
		std::cout << s[i] << std::endl;

	std::cout << "\n key related query" << std::endl;  //demonstrating key related query
	std::cout << "\n Retrieving all elements that contain a specific string in their item name" << std::endl;
	std::vector<std::string> s7 = db.keyQuery(db, "elem");
	for (unsigned int i = 0; i < s7.size(); i++)
		std::cout << s7[i] << std::endl;

	std::cout << "\n Retrieving the value of a key " << std::endl;
	Element<StrData> t = db.value("elem2");
	std::cout << t.show();

	std::cout << "\n Retrieving the Child of key " << std::endl;

	for (unsigned int i = 0; i < t.child.size(); i++)
		std::cout << t.child[i];

	


	std::cin.get();
}
