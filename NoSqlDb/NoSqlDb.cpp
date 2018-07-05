
/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                       //
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

Package Operations:
==================


*/
#include "NoSqlDb.h" 
#include <iostream>
#include <ctime>
#include "../XmlDocument/XmlDocument/XmlDocument.h"

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
  std::cout << "\n  Demonstrating NoSql Helper Code";
  std::cout << "\n =================================\n";

  std::cout << "\n  Creating and saving NoSqlDb elements with string data";
  std::cout << "\n -------------------------------------------------------\n";

  NoSqlDb<StrData> db;
  
 
  Element<StrData> elem1;
  elem1.name = "elem1";
  elem1.category = "test";
  elem1.data = "elem1's StrData";
  elem1.child.push_back("elem2");
  
  
  
  db.save(elem1.name, elem1);

 

  Element<StrData> elem2;
  elem2.name = "elem2";
  elem2.category = "test";
  elem2.data = "elem2's StrData";
  elem2.child.push_back("elem3");
   //timeDate initialized using constructor
  
  db.save(elem2.name, elem2);

  Element<StrData> elem3;
  elem3.name = "elem3";
  elem3.category = "test";
  elem3.data = "elem3's StrData";
  //timeDate initialized using constructor
  db.save(elem3.name, elem3);

  
  
  std::cout << "\n  Retrieving elements from NoSqlDb<string>";
  std::cout << "\n ------------------------------------------\n";

  std::cout << "\n  size of db = " << db.count() << "\n";
  Keys keys = db.keys();
  for (Key key : keys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << db.value(key).show();
  }
  std::cout << "\n\n";

  
  std::cout << "\n  Deleting key";
  std::cout << "\n =================================\n";

  db.deleteKey(elem1.name);
  
  std::cout << "\n After Deleting key " << std::endl;

  std::cout << "\n  size of db = " << db.count() << "\n";
  Keys keys1 = db.keys();

  for (Key key : keys1)
  {
	  std::cout << "\n  " << key << ":";
	  std::cout << db.value(key).show();
  }
  std::cout << "\n\n";

  std::cout << "\n Adding key"<<std::endl;
  db.addKey(elem1.name, elem1);
  //elem1.name = elem1.getDateTime();
  

  for (Key key : keys)
  {
	  std::cout << "\n  " << key << ":";
	  std::cout << db.value(key).show();
  }
  std::cout << "\n\n";

  std::cout << "\n After editing/updating " << std::endl;
  std::cout << "\n =================================\n";
 
  elem3.name = "elem3";
  elem3.category = "test";
  elem3.data = "new data";
 
  db.update(elem3.name, elem3);
 

  for (Key key : keys)
  {
	  std::cout << "\n  " << key << ":";
	  std::cout << db.value(key).show();
  }
  



  std::cout << "\n  Creating and saving NoSqlDb elements with int data";
  std::cout << "\n ----------------------------------------------------\n";

  NoSqlDb<intData> idb;

  Element<intData> ielem1;
  ielem1.name = "elem1";
  ielem1.category = "test";
  ielem1.data = 1;
  ielem1.timeDate = ielem1.getDateTime();
  //timeDate initialized using constructor


  
  idb.save(ielem1.name, ielem1);

  Element<intData> ielem2;
  ielem2.name = "elem2";
  ielem2.category = "test";
  ielem2.data = 2;
  ielem2.timeDate = ielem2.getDateTime();
  //timeDate initialized using constructor

  idb.save(ielem2.name, ielem2);

  Element<intData> ielem3;
  ielem3.name = "elem3";
  ielem3.category = "test";
  ielem3.data = 3;
  ielem3.timeDate = ielem3.getDateTime();
  //timeDate initialized using constructor

  idb.save(ielem3.name, ielem3);

  Element<intData> ielem4;
  ielem4.name = "elem4";
  ielem4.category = "test";
  ielem4.data = 4;
  ielem4.timeDate = ielem4.getDateTime();
  //timeDate initialized using constructor
  idb.save(ielem4.name, ielem4);

  std::cout << "\n  Retrieving elements from NoSqlDb<int>";
  std::cout << "\n ---------------------------------------\n";

  std::cout << "\n  size of idb = " << idb.count() << "\n";
  Keys ikeys = idb.keys();
  for (Key key : ikeys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << idb.value(key).show();
  }
  /*std::cout << "\n\n";
  NoSqlDb<std::string> db1;
  std::cout<<db1.PersistingDatabaseContenttoXml(db) ;

  std::cout << "\n Queries" << std::endl;
  std::cout << "\n Demostrating category query" << std::endl;
  std::cout << "\n Retrieving all elements that contain a specific string in their category name" << std::endl;
  std::vector<std::string> s = db.categoryQuery(db, "test");
  for (unsigned int i = 0; i < s.size(); i++)
	  std::cout << s[i] << std::endl;

 
  std::cout << "\n Retrieving the value of a key " <<std:: endl;
  Element<StrData> t = db.value("elem2");
  std::cout<<t.show();

  std::cout << "\n Retrieving the Child of a key " << std::endl;

  for (unsigned int i = 0; i < t.child.size(); i++)
	  std::cout << t.child[i] << std::endl;*/

  
  

  
}