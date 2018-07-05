// Queries.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Queries.h"
#include <regex>

//std::vector<std::string> Queries::SpecifiedCategory(NoSqlDb<Data> db, std::string s)
//{
//	std::vector<std::string> result;
//	Keys k2 = db.keys();
//	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
//	for (Key k : k2) {
//		Element<Data> res = db.value(k);
//		std::string name = res.category;
//		if (regex_match(name, r)) {
//			result.push_back(res.name);
//		}
//	}
//	if (result.size() == 0)
//		cout << "No element with similar category patern";
//
//	return result;
//}



