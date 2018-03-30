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


enum JSON_STORAGE_TYPE{
	item,
	list,
	json
};

class JSON_DATA{
 public:
	// JSON data can have a map OR list OR value
	//	setting the JSON_DATA as one, will modify the others
	std::map< std::string, JSON_DATA > json_map;
	std::vector< JSON_DATA > data_list;
	std::string value;
	enum JSON_STORAGE_TYPE type;

	JSON_DATA();
	JSON_DATA( std::string _value );	// will init as an item

	void add( std::string _key, std::string _value );	// add to the map
	void add( std::string _key, JSON_DATA _value );
	void add_to_list( std::string _value );
	std::vector<JSON_DATA> get_list();

	// operators
	JSON_DATA operator[]( std::string _in);
	JSON_DATA operator[]( int _in );
};


class JSON{
 public:

	static JSON_DATA load_from_file			( std::string _file );
	static std::string make_all_string		( std::string _in );
	static JSON_DATA load_from_string		( std::string _in, int num );
	static JSON_DATA map_from_string		( std::string _in );
	static void pretty_print_JSON_DATA		( JSON_DATA _in, int _spacing );
};



#endif
