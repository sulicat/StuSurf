#include "../include/common.h"

std::string common::toLower( std::string _in ){
	std::string _out = _in;
	for( int i = 0; i < _out.size(); i++ ){
		_out[i] =  tolower(_out[i]);
	}

	return _out;
}

std::string common::toUpper( std::string _in ){
	std::string _out = _in;
	for( int i = 0; i < _out.size(); i++ ){
		_out[i] =  toupper(_out[i]);
	}

	return _out;
}
