#ifndef JSON_PARSER_HEADER
#define JSON_PARSER_HEADER

#include <iostream>
#include <vector>
#include <map>

// Considering a JSON file
//	it starts of like this { ... }
//  we can have something like this { "test":"test1", "testtwo":"test2" }
//		at this point it can be represented using a simple hashmap.
//		test -> test1
//		testtwo -> test2
//  however, we have the possibility of this { "letter":[ "a", "b", "c" ], "number":[ 1, 2, 3 ] }
//	now we can no longer represent everyhing in the same hashmap. we can convert all the intergers and bools into strings

//	we can have a datatype similar to this ???!?? ->
//		JSON_NODE
//			union
//				std::vector< string > ___
//				map< string, JSON_NODE >
//
//		to get data
//		if vector is empty we can assume that there is another

class JSON_DATA{
 public:
	union data{
		std::map< std::string, std::string > map;
		std::vector< std::string > values;
	};
};



class JSON{
 public:
	static void test();

	static JSON_DATA load_from_file( std::string _file );
	static std::string make_all_string( std::string _in );
	static JSON_DATA load_from_string( std::string _in );

};



#endif
