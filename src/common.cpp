#include "../include/common.h"

#define KEY_REPEAT false

// Labels
Label::Label( std::string _t, int _x, int _y, int _w, int _h ){
	set_pos( _x, _y );
	set_size( _w, _h );
	label_text.setString( _t );
	label_text.setFont( MAIN_FONT );
	label_text.setString( _t );
	label_text.setColor( COLOR_BLACK );
	backdrop.setFillColor( COLOR_CommandBox_1 );
}

void Label::set_pos( int _x, int _y ){
	x = _x;
	y = _y;
	backdrop.setPosition( sf::Vector2f(_x, _y) );
	label_text.setPosition( sf::Vector2f(_x, _y) );
}

void Label::set_size( int _w, int _h ){
	width = _w;
	height = _h;
	backdrop.setSize( sf::Vector2f(_w, _h) );
}

void Label::select(){
	backdrop.setFillColor( COLOR_CommandBox_3 );
}

void Label::render(){
	window.draw( backdrop );
	window.draw( label_text );
}

/*************************************************************************/


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
	std::string command = "ls -1F " + _dir + " | grep -vE /$ > cache/temp_filelist";
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
	std::string command = "ls -R -1 -d " + _dir + "*/ 2>/dev/null | xargs -n 1 2>/dev/null basename > cache/temp_filelist";
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


bool common::varToFile( std::string _file, std::string var_name, std::string _var ){
	std::fstream file;
	std::vector<std::string> buffer_file;

	file.open( _file, std::ios::in );
	char line[255];
	while( file.getline( line, 256 ) != 0 ){
		buffer_file.push_back( line );
		std::cout << line << "--\n";
	}
	file.close();

	file.open( _file, std::ios::out | std::ios::trunc );
	for( int i = 0; i < buffer_file.size(); i++ ){


		if( buffer_file[i] == (var_name) ){
			i += 1;
		}else{
			file << buffer_file[i] << "\n";
		}
	}

	file << var_name << "\n";
	file << _var << "\n";
	file.close();

	return true;
}

std::string common::varFromFile( std::string _file, std::string var_name ){
	std::fstream file;
	std::string _out;

	file.open( _file, std::ios::in );
	char line[255];
	while( file.getline( line, 256 ) != 0 ){
		if( var_name == line ){
			file.getline( line, 256 );
			_out = line;
			return _out;
		}
	}

	file.close();
}



std::vector<std::string> common::splitString( std::string _in, std::string _delim ){
	std::vector<std::string> out;

	int start = 0;
	for( int i = 0; i < _in.size() - _delim.size(); i++ ){

		if( _in.substr(i, _delim.size()) == _delim ){
			out.push_back( _in.substr(start, i - start ));
			start = i + 1;
			i += _delim.size();
		}

	}
	out.push_back( _in.substr(start, _in.size() - start  ));

	return out;
}
