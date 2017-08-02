// this includes the definitions of any functions in the Common class located in the common.h file

#include "common.h"
#include <iostream>
#include <stdlib.h>

bool Common::check_inside_rect( int _x, int _y, int rect_x, int rect_y, int rect_width, int rect_height ){
	// check the left and bottom intesections
	if( _x >= rect_x && _y >= rect_y ){
		// check bottom and right boandaries
		if( _x <= rect_x + rect_width && _y <= rect_y + rect_height ){
			return true;
		}
	}
	return false;
}

std::string Common::int_to_string( int _num ){
	std::ostringstream str;
	str << _num;
	return str.str();
}

std::string * Common::split_string( char * input, char delim ){
	int i = 0;
	std::string part = ""; 

	std::string * out = new std::string[1];
	int out_len = 1;
	out[0] = int_to_string(out_len);

	std::string * temp = new std::string[out_len];

	while( input[i] != '\0' ){

		if( input[i] == delim ){
			// we will add the current part to the string array then empty it.
			// adding the part to the array
			temp = new std::string[ out_len + 1 ];
			std::copy( out, out + out_len, temp );
			out = temp;
			out[ out_len ] = part;
			out_len += 1;
			// clearing the part
			part = "";
			i += 1;
			// recalc the length
			out[0] = int_to_string(out_len);
		}
		part.push_back( input[i] );
		i += 1;
	}

	// add the last element
	temp = new std::string[ out_len + 1 ];
	std::copy( out, out + out_len, temp );
	out = temp;
	out[ out_len ] = part;
	out_len += 1;
	// recalc the length
	out[0] = int_to_string(out_len);

	return out;

}

std::string * Common::split_string( std::string _input, char delim ){
	const char * input = new char[ sizeof( _input.c_str() )/sizeof(char) ];
	input = _input.c_str();

	int i = 0;
	std::string part = ""; 

	std::string * out = new std::string[1];
	int out_len = 1;
	out[0] = int_to_string(out_len);

	std::string * temp = new std::string[out_len];

	while( input[i] != '\0' ){

		if( input[i] == delim ){
			// we will add the current part to the string array then empty it.
			// adding the part to the array
			temp = new std::string[ out_len + 1 ];
			std::copy( out, out + out_len, temp );
			out = temp;
			out[ out_len ] = part;
			out_len += 1;
			// clearing the part
			part = "";
			i += 1;
			// recalc the length
			out[0] = int_to_string(out_len);
		}
		part.push_back( input[i] );
		i += 1;
	}

	// add the last element
	temp = new std::string[ out_len + 1 ];
	std::copy( out, out + out_len, temp );
	out = temp;
	out[ out_len ] = part;
	out_len += 1;
	// recalc the length
	out[0] = int_to_string(out_len);

	return out;

}

int Common::string_to_int( std::string _input ){
	return atoi( _input.c_str() );
}

float Common::string_to_float( std::string _input ){
	return atof( _input.c_str() );
}
