#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database                       //
//                                                                    //
// source     : Jim Fawcett 
// Project    : Key value database                                //                               
//Author     :    Tejaswi Nimmagadda, Syracuse University,       //
                  //tenimmag@syr.edu                            //
//Language   :    C++                                          //
//Platform   :    Dell, Windows 10                            //
//                                                            //
//                                                           //
////////////////////////////////////////////////////////////////
/*
 * If you elect to use this code, you will need to add
 * - manual information
 * - maintenance information
 * - query mechanism
 * - persistance mechanism
 * - TestExecutive that demonstrates the requirements you meet
 */
/*
 * - fixed bug in NoSqlDb::count() by replacing 
 *   unordered_map<key,Value>::count() with 
 *   unordered_map<key,Value>::size();
 */

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

 Module Operations:
 ==================
 create a key value pair in dtabase using an unoredered map
 It contains various methods to manipulate the keys i.e to 
 delet the keys, add keys , persist from database into Xml etc

 */

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

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//


template<typename Data>
class Element
{
public:
  using Name = std::string;   // alias declaration for name 
  using Category = std::string; // alias declaration category
  using TimeDate = std::string; // alias declaration for Time Date
  using Key = std::string; // alias declaration for key
  
  Property<Name> name;            // metadata
  Property<Category> category;    // metadata
  Property<TimeDate> timeDate;    // metadata
  Property<Data> data;            //data
  std::vector<Key> child;         //child
  std::string show();
  Element() // Element class constructor 
  {
	  timeDate = getDateTime(); // to obtain date and time
  }
  std::string getDateTime()  // function to obtain date and time
  {
	  time_t timeInstance;

	  timeInstance = time(NULL);

	  tm tlm;

	  localtime_s(&tlm, &timeInstance);

	  std::ostringstream stringToInteger;

	  stringToInteger << tlm.tm_hour << ":" << tlm.tm_min << ":" << tlm.tm_sec << "  " << tlm.tm_mon + 1 << "-" << tlm.tm_mday << "-" << tlm.tm_year + 1900;

	  return stringToInteger.str();
  }
};


template<typename Data>    // method to display information regarding keys and values 
std::string Element<Data>::show()
{

  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(8) << "name"     << " : " << name;
  out << "\n    " << std::setw(8) << "category" << " : " << category;
  out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
  out << "\n    " << std::setw(8) << "data"     << " : " << data;

  for(unsigned int i =0; i< child.size();i++) // to display child information
  out << "\n    " << std::setw(8) << "child" << " : " << child[i];
  out << "\n";
  return out.str();
}

/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - you will need to add query capability
//   That should probably be another class that uses NoSqlDb
//
template<typename Data>
class NoSqlDb
{
public:
  using Key = std::string; // alias declarations
  using Keys = std::vector<std::string>; // alias declarations

  Keys keys();
  bool save(Key key, Element<Data> elem); // method to save the database
  Element<Data> value(Key key);
  size_t count(); // methid to count the number of elements in the database
  bool deleteKey(Key key);  // method to delete keys
  bool addKey(Key key, Element<Data> elem); // method to add keys
  bool update(Key key, Element<Data> elem); // method to update database
  std::string Publish(NoSqlDb<Data>& db); // method to write database content into xml file
  std::vector<std::string> keyQuery(NoSqlDb<Data> dbinstance, std::string s);
  std::vector<std::string> categoryQuery(NoSqlDb<Data> dbinstance, std::string s); // category query-method which returns keys that match a specified pattern

private:
  using Item = std::pair<Key, Element<Data>>; 

  std::unordered_map<Key,Element<Data>> store; // instantiating the unordered map to store the data base contents
};

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
    keys.push_back(item.first);
  }
  return keys;
}

template<typename Data>  // method to save the elements into the database
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
  if(store.find(key) != store.end())
    return false;
  store[key] = elem;
  return true;
}

template<typename Data> // method to update the database
bool NoSqlDb<Data>::update(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end()) {
		store[key] = elem;
		return true;
	}
	else
	{
		return false;
	}
		
}
template<typename Data>
std::vector<std::string> NoSqlDb<Data>:: categoryQuery(NoSqlDb<Data> dbinstance, std::string s) // category query-method which returns keys that match a specified pattern
{
	std::vector<std::string> store2;
	Keys keys5 = dbinstance.keys();
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : keys5) {
		Element<Data> instance = dbinstance.value(k);
		std::string name = instance.category;
		if (regex_match(name, r)) {
			store2.push_back(instance.name);
		}
	}
	if (store2.size() == 0)
		std::cout << "No element with similar category patern";

	return store2;
}
template<typename Data>
std::vector<std::string> NoSqlDb<Data>:: keyQuery(NoSqlDb<Data> dbinstance, std::string s) //key query- method which returns keys that match a specified pattern 
{
	std::vector<std::string> store3;
	Keys keys6 = dbinstance.keys();
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : keys6) {
		Element<Data> instance = dbinstance.value(k);
		std::string name1 = instance.name;
		if (regex_match(name1, r)) {
			store3.push_back(instance.name);
		}
	}
	if (store3.size() == 0)
		std::cout << "No element with similar category patern";

	return store3;
}


template<typename Data> // method to add elements(keys) into the database
bool NoSqlDb<Data>::addKey(Key key, Element<Data> elem)
{
	store[key] = elem;
	return true;
}

template<typename Data> //method used to retrieve the value of a key
Element<Data> NoSqlDb<Data>::value(Key key)
{
  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();
}

template<typename Data>  //method to write the database contents into the xml file
std::string NoSqlDb<Data>::Publish(NoSqlDb<Data>& db)
{
	title("Creating and storing XmlDocument in xml.txt file");
	SPtr p1 = makeTaggedElement("Data Base");
	XmlDocument doc(XmlProcessing::makeDocElement(p1));
	Keys keys4 = db.keys();
	for (Key key1 : keys4)
	{
		std::cout << "\n" << key1 << ":" << db.value(key1).show();

		SPtr child_ = makeTaggedElement(db.value(key1).name);
		SPtr NameTag = makeTaggedElement("Name");
		NameTag->addChild(makeTextElement(db.value(key1).name));
		child_->addChild(NameTag);


		SPtr CategoryTag = makeTaggedElement("Category");
		CategoryTag->addChild(makeTextElement(db.value(key1).category));
		child_->addChild(CategoryTag);

		SPtr DateTimeTag = makeTaggedElement("Date Time");
		DateTimeTag->addChild(makeTextElement(db.value(key1).timeDate));
		child_->addChild(DateTimeTag);

		SPtr DataTag = makeTaggedElement("Data");
		DataTag->addChild(makeTextElement(db.value(key1).data));
		child_->addChild(DataTag);

		SPtr ChildrenofElement = makeTaggedElement("Children");
		std::vector<std::string> te = db.value(key1).child;
		for (int i = 0; i < (int)te.size(); i++) {
			ChildrenofElement->addChild(makeTextElement(te[i]));
		}
		child_->addChild(ChildrenofElement);
		p1->addChild(child_);
	}

	std::string xmlFile = doc.toString();
	std::ofstream XmlFile1;//create file
	XmlFile1.open("../xmlFile.txt");
	XmlFile1 << xmlFile;
	XmlFile1.close();
	return xmlFile;
}

template<typename Data> //method which return the number of elements in the database
size_t NoSqlDb<Data>::count()
{
  return store.size();
}

template<typename Data>  //method to delete key from the database
bool NoSqlDb<Data>::deleteKey(Key key)
{
	if (store.find(key) == store.end())
	{
		std::cout << "Key does not exist in the data base" << std::endl;
		return false;
	}

	else
	{
		store.erase(key);
		std::cout << "\n Key deleted" <<std::endl;
		return true;
	}

}



/////////////////////////////////////////////////////////////////////
// Persistance class
// - you will need to implement that using the XmlDocument class
//   from Handouts/Repository
