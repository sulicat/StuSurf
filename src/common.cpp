#include "../include/common.h"

// return the lower case version of a string
std::string common::toLower( std::string _in ){
	std::string _out = _in;
	for( int i = 0; i < _out.size(); i++ ){
		_out[i] =  tolower(_out[i]);
	}

	return _out;
}

// return the uppercase version of a string
std::string common::toUpper( std::string _in ){
	std::string _out = _in;
	for( int i = 0; i < _out.size(); i++ ){
		_out[i] =  toupper(_out[i]);
	}

	return _out;
}


// OS SPECIFIC
// return a list of file paths located within a certain directory.
// NOTE(suli) ~~~~~
//	in future, implement windows support
std::vector<std::string> common::files_in( std::string _dir ){
	std::vector<std::string> out;
	// pipe the ls into cache
	std::string command = "ls -1F data/" + _dir + " | grep -vE /$ > cache/temp_filelist";
	system( command.c_str() );

	std::fstream file;
	file.open( "cache/temp_filelist", std::ios::in );

	char line[255];
	while( file.getline( line, 256 ) != 0 ){
		out.push_back( line );
	}

	file.close();
	return out;
}


// OS SPECIFIC
// return a list of file paths located within a certain directory.
// NOTE(suli) ~~~~~
//	in future, implement windows support
std::vector<std::string> common::folders_in( std::string _dir ){
	std::vector<std::string> out;
	// pipe the ls into cache
	std::string command = "ls -1 -d data/" + _dir + "*/ | xargs -n 1 basename > cache/temp_filelist";
	system( command.c_str() );

	std::fstream file;
	file.open( "cache/temp_filelist", std::ios::in );

	char line[255];
	while( file.getline( line, 256 ) != 0 ){
		out.push_back( line );
	}

	file.close();
	return out;
}
