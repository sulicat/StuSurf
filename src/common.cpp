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

void common::EMPTY(void*){

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
	std::string command = "ls -R -1 -d data/" + _dir + "*/ 2>/dev/null | xargs -n 1 2>/dev/null basename > cache/temp_filelist";
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


Menu * common::menuFromDir( std::string _dir, std::function<void(void*)> _func ){

	Menu * out = new Menu( _dir );

	// folders
	std::vector<std::string> menu_list_folders = common::folders_in( _dir );
	std::string * argument_folders;

	for( int i = 0; i < menu_list_folders.size(); i++ ){
		argument_folders 	= new std::string();
		*argument_folders	= _dir + menu_list_folders[i] + "/";
		out->add( MenuItem( menu_list_folders[i], common::menuFromDir(*argument_folders, _func)) );
	}

	// files
	std::vector<std::string> menu_list_files = common::files_in( _dir );
	std::string * argument_files;

	for( int i = 0; i < menu_list_files.size(); i++ ){
		argument_files 	= new std::string();
		*argument_files	= menu_list_files[i];
		*argument_files = _dir + *argument_files;
		out->add( MenuItem( menu_list_files[i], _func, argument_files) );
	}

	return out;
}
