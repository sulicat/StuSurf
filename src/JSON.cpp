#include "../include/JSON.h"
#include <iostream>
#include <fstream>

/* MOTE suli:
There is a bug with make_all_string, it strips spaces from inputs. Fix when in good mindset:/
Oh god. you idiot.
This also replaces all "}" and "{" in the string with blanks.
one would assume you were drunk when writing it.
*/


/* JSON_DATA */
//**************************************************************************************************************
JSON_DATA::JSON_DATA(){		// init empty
	type = json;
}

JSON_DATA::JSON_DATA( std::string _value ){
	type = item;
	value = _value;
	// NOTE: suli
	//	I may want to clear the other variables as a way to save space. Have to consider how needed that is
}

void JSON_DATA::add( std::string _key, std::string _value ){
	type = json;
	json_map.insert( std::pair <std::string, JSON_DATA>(_key, JSON_DATA( _value )) );
}

void JSON_DATA::add( std::string _key, JSON_DATA _value ){
	type = json;
	json_map.insert( std::pair <std::string, JSON_DATA>(_key, _value) );
}

void JSON_DATA::add_to_list( std::string _value ){
	type = list;
	data_list.push_back( _value );
}

std::vector<JSON_DATA> JSON_DATA::get_list(){
	return data_list;
}


// operators
JSON_DATA JSON_DATA::operator[]( std::string _in ){
	return json_map[_in];
}

JSON_DATA JSON_DATA::operator[]( int _in ){
	return data_list[_in];
}

/* JSON STATIC FUNCTIONs */
//**************************************************************************************************************

// replace all words that arnt in string brackets in place,
// note this function also strips spaces and tabs from the outside of variables
std::string JSON::make_all_string( std::string _in ){
	std::string _out = "";
	bool is_string = false;
	bool added = false;

	for( int i = 0; i < _in.size(); i++){
		// if it is not a syntax charecter
		if( _in[i] != '}' && _in[i] != '{' && _in[i] != ',' && _in[i] != '[' && _in[i] != ']' && _in[i] != ':' && _in[i] != ' ' && _in[i] != '\n' && _in[i] != '\t'){
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
			if( _in[i] != ' ' && is_string == false && _in[i] != '\n' && _in[i] != '\t' ){ _out += _in[i]; }		// strip ' ', '\n', '\t' outside of variable
		}
	}
	return _out;
}



/*
JSON Object
	-> hashmap of JSON Object
		-> hashmap of JSON OBJECT
		-> array of strings
	-> array of strings
*/

JSON_DATA JSON::load_from_string( std::string _in, int num){
	JSON_DATA out;

	bool reached_closing 	= false;
	int depth 				= 0;
	int string_depth		= 0;
	std::string temp_string;
	std::string temp_key;
	char brace_type_open	= ' ';
	char brace_type_close	= ' ';
	int temp_int			= 0;
	int pos_end				= 0;
	int pos_start			= 0;

	// the json will start with "{"
		// we want to create a JSON_DATA object. The initial object will be hashmap, with keys that are any top level json items

	if( _in.size() > 0 && _in[0] == '{' ){		// initial start of hasmap
		// we want to find the top level keys and link them to json objects/arrays/values
		int i = 0;
		while( _in.size() > 0 ){
			// find first '"'
			pos_start = _in.find('"') + 1;
			_in.erase(0, pos_start);
			pos_start = 0;

			// find second '"'
			pos_end = _in.find('"');
			temp_key = _in.substr( pos_start, pos_end );
			_in.erase( 0, pos_end + 2 );

			// at this point, our goal is to find where this next json object ends
			// if it starts as '"', then we can simply find the 2nd '"'
			// if it starts with [ or { then we must count depth, and stop when we are outside the object
			if( _in.size() > 0 && _in[0] == '"' ){
				pos_start = 0;
				pos_end = (_in.substr(1, _in.size()).find('"')) + 1;	// +1 because we took one out by starting at 1
				temp_string = _in.substr( pos_start + 1, pos_end - 1);		// get rid of " aswell

				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "________single______\n";
				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << temp_key << " -> " << temp_string << "\n\n";

				out.add( temp_key, temp_string );

				_in.erase( pos_start, pos_end + 1 );
				_in.erase(0,1);


			// deal with JSON objects and arrays
			}else if( _in.size() > 0 && (_in[0] == '{' || _in[0] == '[') ){	// at this poit, we want to find the closing brace
				// set brace type, either {,} or [,]
				if( _in[0] == '{' ){ brace_type_open = '{'; brace_type_close = '}'; }
				else if( _in[0] == '[' ){ brace_type_open = '['; brace_type_close = ']'; }

				// we found the opening brace, now we want to loop to find the closing brace
				depth = 1;
				i = 0;
				while( depth > 0 ){
					i += 1;
					if( _in[i] == brace_type_close ){ depth -= 1;}else if( _in[i] == brace_type_open ){ depth += 1; }
				}

				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "________JSON_______\n";
				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "Key: "<< temp_key << " == " << _in.substr( 0, i+1 ) << "\n\n";
				load_from_string( _in.substr( 0, i+1 ), num + 1 );

				out.add( temp_key, load_from_string( _in.substr( 0, i+1 ), num + 1 ) );

				_in.erase(0, i + 2);

			}else{
				std::cout << "\n\nERROR: \n";
				break;
			}
		}

	// dealing with an array
	}else if( _in.size() > 0 && _in[0] == '[' ){
		int i = 0;
		// we want to get rid of the opening and closing brace
		_in.erase( 0, 1);
		_in.erase( _in.size() - 1, 1);

		// we know we are dealing with an array. we can treat it very similar to how we did with the JSON object,
		//	however this time we do not have a key, instead we will be creating an array
		pos_start = 0;
		int current_index_out = 0;
		// we want to split the elements that are delimeted by a comma,
		//	however we want to ignore commas that are included in another array or another string
		while( _in.size() > 0 ){
			if( _in[0] == '"' ){
				_in.erase( 0, 1 );
				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "i: " << current_index_out << " == " << _in.substr( 0, _in.find('"') ) << "\n";
				current_index_out += 1;
				out.add_to_list( _in.substr(0, _in.find('"')) );

				_in.erase( 0, _in.find('"') );
				if( _in[0] == '"' ){ _in.erase( 0,1 ); }
				if( _in[0] == ',' ){ _in.erase( 0,1 ); }

			}else if( _in.size() > 0 && (_in[0] == '{' || _in[0] == '[') ){	// at this poit, we want to find the closing brace
				// set brace type, either {,} or [,]
				if( _in[0] == '{' ){ brace_type_open = '{'; brace_type_close = '}'; }
				else if( _in[0] == '[' ){ brace_type_open = '['; brace_type_close = ']'; }

				// we found the opening brace, now we want to loop to find the closing brace
				depth = 1;
				i = 0;
				while( depth > 0 ){
					i += 1;
					if( _in[i] == brace_type_close ){ depth -= 1;}else if( _in[i] == brace_type_open ){ depth += 1; }
				}

				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "i: " << current_index_out << " num: " << num << "\n";
				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "________JSON_______\n";
				for( int  f = 0; f < num; f++ ){ std::cout << "\t"; }
				std::cout << "Key: "<< temp_key << " == " << _in.substr( 0, i+1 ) << "\n\n";
				load_from_string( _in.substr( 0, i+1 ), num + 1 );


				current_index_out += 1;
				_in.erase(0, i + 2);

			}

		}

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

	std::cout << json_string << "\n";
	std::cout << "----------------------------------\n";
	std::cout << "----------------------------------\n";
	// now the json file is full of strings.
	// we want ot generate a JSON_CONTAINER from this json string

	_out = load_from_string( json_string, 0 );

	return _out;
}





// This should be called UGLY print..... I realized I suck at aligning this data :/
void JSON::pretty_print_JSON_DATA( JSON_DATA _in, int _space){

	if( _in.type == json ){
		for (auto const& x : _in.json_map){

			for( int f = 0; f < _space ; f++ ){ std::cout << " "; }
			std::cout << x.first << ":";

			if( _in[x.first].type == item ){
				std::cout << _in[x.first].value;

			}else if( _in[x.first].type == json ){
				std::cout << " { ";
				pretty_print_JSON_DATA( _in[x.first], _space + 1 );
				std::cout << " } ";

			}else if( _in[x.first].type == list ){
				std::cout << "[ ";
				for( int i = 0; i < _in[x.first].get_list().size(); i++ ){
					if( _in[x.first].data_list[i].type == item )
						std::cout << _in[x.first].data_list[i].value << ", ";
					else
						pretty_print_JSON_DATA( _in[x.first].data_list[i], _space );
				}
				std::cout << " ]";
			}

			std::cout << ", ";

		}
	}
}
