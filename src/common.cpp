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
// INPUTS

/*********************************/
// text input
Text_Input::Text_Input( std::string _name ) : Input_Base( _name ){
	name = _name;

	text.setPosition( 0, 0 );
	text.setFont( MAIN_FONT );
	text.setColor( COLOR_WHITE );						// color
	text.setCharacterSize( 20 );

	backdrop.setFillColor( sf::Color(255, 0, 0, 0) ); 	// color
	backdrop.setOutlineColor( sf::Color(0, 0, 0) ); 	// color
	backdrop.setOutlineThickness( 2 );

	text_name.setString(name);
	text_name.setFont(MAIN_FONT);
	text_name.setColor( COLOR_BLACK );					// color
	text_name.setCharacterSize( 20 );
}

void Text_Input::render(){
	backdrop.setPosition( (x + width*0.4) + 2, y + height*0.1);
	backdrop.setSize( sf::Vector2f( (width*0.6) - 4, height*0.8) );
	window.draw( backdrop );

	text_name.setPosition( x + 2, y );
	text_name.setStyle(sf::Text::Bold);
	window.draw( text_name );

	text.setPosition( x + width*0.4 + 2, y );
	window.draw( text );
}


void Text_Input::input( sf::Event e ){
	switch( e.type ){
		case sf::Event::KeyPressed:
			// ALPHABETS
			if( e.key.code >= sf::Keyboard::A && e.key.code <= sf::Keyboard::Z ){
				value += (char)(e.key.code - sf::Keyboard::A + 'a');

			// NUMBERS 0 - 9
			}else if( e.key.code >= sf::Keyboard::Num0 && e.key.code <= sf::Keyboard::Num9 ){
				value += (char)(e.key.code - sf::Keyboard::Num0 + '0');

			// NUMPAD 0 - 9
			}else if( e.key.code >= sf::Keyboard::Numpad0 && e.key.code <= sf::Keyboard::Numpad9 ){
				value += (char)( e.key.code - sf::Keyboard::Numpad0 + '0');

			// SPACE
			}else if( e.key.code == sf::Keyboard::Space ){
				value += " ";

			// BACKSPACE
			}else if( e.key.code == sf::Keyboard::BackSpace ){
				if( value.length() > 0 ){
					value.pop_back();
				}

			}
		default:
			break;
	}

	text.setString( value );
}

/*********************************/
// check box input
Check_Box_Input::Check_Box_Input( std::string _name, std::vector<std::string> _contents ) : Input_Base(_name){
	contents = _contents;
	number_of_boxes = 3;
	scroll = 0;
	selected_index = 0;

	for( int i = 0; i < _contents.size(); i++ ){
		content_values.push_back( false );
	}

	text_name.setFont( MAIN_FONT );
	text_name.setString( _name );
	text_name.setColor( sf::Color(0,0,0) );		// color
	text_name.setCharacterSize( 20 );

	box_name.setFont( MAIN_FONT );
	box_name.setCharacterSize( 15 );
	box_name.setStyle( sf::Text::Bold );
	box_name.setColor( sf::Color(0,0,0) );		// color

	temp_texture.loadFromFile( "images/icon_checkmark.png" );
	checkmark.setTexture( temp_texture );
}

void Check_Box_Input::render(){
	box.setOutlineColor( sf::Color(0,0,0) );
	box.setOutlineThickness( 2 );
	box.setFillColor( sf::Color(0,0,0,0) );

	int padding_x = 50;
	int s_x = x + width * 0.4;
	int s_y = y + height * 0.5;
	float box_width = std::min((width*0.6)/number_of_boxes, height*0.4);
	float box_height = std::min((width*0.6)/number_of_boxes, height*0.4);

	box.setSize( sf::Vector2f( box_width , box_height) );
	checkmark.setScale( box_width / temp_texture.getSize().x, box_height / temp_texture.getSize().y );

	for( int i = scroll; i < contents.size() && i < scroll + number_of_boxes - 1; i++ ){
		int x_offset = (i-scroll)*(width*0.6)/number_of_boxes + (padding_x/number_of_boxes)*(i-scroll);
		int y_offset = 0;

 		box.setPosition( s_x + x_offset, s_y + y_offset);
		box.setFillColor( sf::Color(0,0,0,0) );
		if( i == selected_index ){ box.setFillColor( sf::Color(255, 0, 255) ); }
		box_name.setPosition( s_x + x_offset, y );
		box_name.setString( contents[i] );

		checkmark.setPosition( s_x + x_offset, s_y );


		window.draw(box);
		window.draw(box_name);
		if( content_values[i] == true )
			window.draw(checkmark);
	}

	text_name.setPosition( x, y );
	text_name.setStyle(sf::Text::Bold);
	window.draw(text_name);
}

void Check_Box_Input::input( sf::Event _e ){
	if( _e.type == sf::Event::KeyPressed ){

		// right arrow
		if( _e.key.code == sf::Keyboard::Right ){
			if( selected_index - scroll == number_of_boxes - 2 ){ scroll += 2; }
			selected_index += 1;
			if( selected_index >= contents.size() ){ selected_index = contents.size() - 1; }

		// left arrow
		}else if( _e.key.code == sf::Keyboard::Left ){
			if( selected_index - scroll == number_of_boxes - 3 && scroll != 0 ){ scroll -= 2; }
			selected_index -= 1;
			if( selected_index < 0){ selected_index = 0;}

		// enter key
		}else if( _e.key.code == sf::Keyboard::Return ){
			content_values[selected_index] = !(content_values[selected_index]);
		}
	}

}


/*********************************/
// slider input
Slider_Input::Slider_Input( std::string _name, int _min, int _max, int _start ) : Input_Base( _name ){
	number = _start;
	min = _min;
	max = _max;

	bar.setFillColor( COLOR_BLACK );
	slider.setFillColor( sf::Color(255, 0, 255) );

	text_name.setString( _name );
	text_value.setString( std::to_string(_start) );

	text_name.setFont( MAIN_FONT );
	text_value.setFont( MAIN_FONT );

	text_name.setCharacterSize( 20 );
	text_value.setCharacterSize( 15 );

	text_name.setColor( COLOR_BLACK );
	text_value.setColor( COLOR_BLACK );
}

void Slider_Input::render(){
	int x_start = x + width * 0.4;
	int y_start = y;

	bar.setPosition( x_start + width*0.1, y_start + height * 0.4 );
	bar.setSize( sf::Vector2f( width*0.4, height * 0.2 ));

	slider.setPosition( x_start + width*0.1 + width*0.4*(number-min)/(max - min) - width*0.025, y + height*0.2 );
	slider.setSize( sf::Vector2f( width*0.05, height*0.6) );

	text_name.setPosition( x, y );
	text_name.setStyle(sf::Text::Bold);

	text_value.setPosition( x + width*0.9, y );
	text_value.setStyle(sf::Text::Bold);

	window.draw( bar );
	window.draw( slider );
	window.draw( text_name);
	window.draw( text_value);
}

void Slider_Input::input( sf::Event _e ){
	if( _e.type == sf::Event::KeyPressed ){
		// right arrow
		if( _e.key.code == sf::Keyboard::Right ){
			number += (max-min)*0.05;

		// left arrow
		}else if( _e.key.code == sf::Keyboard::Left ){
			number -= (max-min)*0.05;
		}
	}

	if( number < min){  number = min;}
	if( number > max ){ number = max;}

	value = std::to_string( number );
	text_value.setString( value );
}


/*************************************************************************/
// useful functions

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
