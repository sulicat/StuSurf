#include "../include/JSON.h"
#include <iostream>
#include <fstream>

void JSON::test(){
	std::cout << "sdasdasd\n";
}


// replace all words that arnt in string brackets in place,
std::string JSON::make_all_string( std::string _in ){
	std::string _out = "";
	bool is_string = false;
	bool added = false;

	for( int i = 0; i < _in.size(); i++){
		// if it is not a syntax charecter
		if( _in[i] != '}' && _in[i] != '{' && _in[i] != ',' && _in[i] != '[' && _in[i] != ']' && _in[i] != ':' && _in[i] != ' ' && _in[i] != '\n' ){
			// we are not in string
			if( is_string == false ){
				if( _in[i] == '"'){
					is_string = true;
					_out += _in[i];
				}else{
					if( added == false ){ _out += '"'; added = true;}
					_out += _in[i];
				}
			}else{
				_out += _in[i];
				if( _in[i] == '"' ){
					is_string = false;
				}
			}
		}else{
			if( added == true ){_out += '"'; added = false;}
			_out += _in[i];
		}
	}
	return _out;
}


JSON_DATA JSON::load_from_string( std::string _in){
	JSON_DATA out;

	std::cout << "started created data from json \n\n";

	for( int i = 0; i < _in.size(); i++ ){
		// finish this later
	}

	return out;
}



JSON_DATA JSON::load_from_file( std::string _file ){
	JSON_DATA _out;

	std::fstream file_open;
	std::string json_string;

	// read the file into a string
	file_open.open( _file, std::ios::in );
	char line[512];
	while( file_open.getline( line, 512 ) != 0){
		json_string += line;
		json_string += "\n";
	}
	file_open.close();

	// we want to standardize it. everything will be in the form of a string
	// first we must convert all the ints and bools into strings.
	// this could be a bad design choice, however I am choosing to lose a little bit of information
	// if it means using this parser can be as easy as calling hashmaps

	json_string = make_all_string( json_string );
	// now the json file is full of strings.
	// we want ot generate a JSON_CONTAINER from this json string

	JSON_DATA temp = load_from_string( json_string );

	return _out;
}
