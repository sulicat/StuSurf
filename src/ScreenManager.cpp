#include "../include/ScreenManager.h"
#include "../include/common.h"
#include "../include/Managers.h"
#include "../include/headers.h"


////////// TEST //////////
std::string __test = "\n --- FUNCTION IS WORKING -- \n";
void temp_print1( void* _a ){
	std::cout << "hello world 1111 \n";
	std::cout << *((std::string*)_a) << "\n";
}

void temp_print2( void* _a ){
	std::cout << "hello world 22222 \n";
	std::cout << _a << "\n";
}
////////// END TEST //////////



void change_screen( void* _s ){
	screenManager.changeScreen( *((std::string*)_s) );
}


// ------------ SCREEN MANAGER ----------------------

ScreenManager::ScreenManager( std::string _topDir ){
	// when a ScreenManager is created with a certain top dir,
	//	we want to make sure that the directory exists. Throw an error otherwise
	path_topDir = _topDir;
	state = USE;
	ADD_STATE = 0;
	module_to_add = "";
	DELETE_INDEX = 0;

	// note(SULI) TBD.. .. .. GET FROM CONFIG .. .. .. . .. .. .. .. .. .. ..
	// 	in the future, we may want to add 3+ shortcut keys
	//	 In order to avoid the 2 key shortcuts from triggering first, consider storing all key bindings
	//	 in an array and sorting them by keybing command length.
	command_execute = KeyBind( "This is the commands that allows you to send commands to the major screen manager" );
	command_execute.add_command( sf::Keyboard::LControl );
	command_execute.add_command( sf::Keyboard::X );

	command_screen_change = KeyBind( "This is the command that allows you to switch between different screens" );
	command_screen_change.add_command( sf::Keyboard::LControl );
	command_screen_change.add_command( sf::Keyboard::S );

	command_escape = KeyBind( "this is what happens when the escape key is pressed" );
	command_escape.add_command( sf::Keyboard::Escape );

	menu_screens = *common::menuFromDir("data/screens/", change_screen);
	add_items = Menu("New Module");

	cursor_x = 0;
	cursor_y = 0;
	cursor_speed = 20;

	// Text Boxes
	textbox_commands = CommandBox( );
	textbox_commands.set( &Main_Commands );

	// VISUALS
	border = sf::RectangleShape( sf::Vector2f( window.getSize().x - 14, window.getSize().y - 14 ));
	border.setPosition( 7, 7 );
	border.setFillColor( sf::Color(0, 0, 0, 0) );
	border.setOutlineThickness( 7 );
	border.setOutlineColor( sf::Color(255, 255, 0) );
	state_text.setString( "" );
	state_text.setFont( MAIN_FONT );
	state_text.setPosition(window.getSize().x - 100, 100);

	cursor_vert  = sf::RectangleShape( sf::Vector2f(window.getSize().x, 0) );
	cursor_horiz = sf::RectangleShape( sf::Vector2f(0, window.getSize().y) );
	cursor_vert.setOutlineThickness(1);
	cursor_vert.setOutlineColor( sf::Color(255, 0, 0) );
	cursor_vert.setFillColor( sf::Color(255, 255, 0, 0) );
	cursor_horiz.setOutlineThickness(1);
	cursor_horiz.setOutlineColor( sf::Color(255, 0, 0) );
	cursor_horiz.setFillColor( sf::Color(255, 255, 0, 0) );

	crosshair = sf::RectangleShape( sf::Vector2f(10, 10) );
	crosshair.setFillColor( sf::Color(255, 0, 0) );

	new_add_box = sf::RectangleShape( sf::Vector2f(0, 0));
	new_add_box.setFillColor(sf::Color( 255, 255, 0 ));

	deleteBoundingBox.setOutlineColor(sf::Color(255, 0, 0));
	deleteBoundingBox.setFillColor( sf::Color(0, 0, 0, 0));
	deleteBoundingBox.setOutlineThickness( 10 );

	deleteBoundingBox1.setOutlineColor(sf::Color(255, 255, 0));
	deleteBoundingBox1.setFillColor( sf::Color(0, 0, 0, 0));
	deleteBoundingBox1.setOutlineThickness( 5 );

	deleteBoundingBox2.setOutlineColor(sf::Color(255, 0, 0));
	deleteBoundingBox2.setFillColor( sf::Color(0, 0, 0, 0));
	deleteBoundingBox2.setOutlineThickness( 10 );
}

void ScreenManager::changeScreen( std::string _p ){
	currentScreenPath = _p;
	updateScreen();
}

void ScreenManager::changeState( enum PROGRAM_STATE _s ){
	state = _s;
	ADD_STATE = 0;

	// in the case of edit we want to:
	//		enable the menu that will add new modules
	if( state == EDIT || state == ADD_MODULE ){
		border.setOutlineColor( sf::Color(255, 255, 0) );
		state_text.setString("Add a Module");
		state_text.setPosition(  window.getSize().x - state_text.getGlobalBounds().width - 20, 8);
		add_items.enable();
	}

	// ADD module - This happens after EDIT mode
	if( state == ADD_MODULE ){
		cursor_x = 0;
		cursor_y = 0;
	}

	// DELETING A MODULE
	if( state == DELETE_MODULE ){
		border.setOutlineColor( sf::Color(255, 0, 0, 125) );
		state_text.setString("DELETE Module");
	}
}

void ScreenManager::resize(){
	border.setSize(sf::Vector2f( window.getSize().x - 14, window.getSize().y - 14 ));
	state_text.setPosition(  window.getSize().x - state_text.getGlobalBounds().width - 20, 8);
	cursor_vert.setSize(  sf::Vector2f(window.getSize().x, 0) );
	cursor_horiz.setSize( sf::Vector2f(0, window.getSize().y) );

}

void ScreenManager::move_cursor( sf::Event _e){
	if( _e.key.code == sf::Keyboard::Left ){
		move_cursor( -1, 0 );
	}else if( _e.key.code == sf::Keyboard::Right ){
		move_cursor( 1, 0 );
	}else if( _e.key.code == sf::Keyboard::Up ){
		move_cursor( 0, -1 );
	}else if( _e.key.code == sf::Keyboard::Down ){
		move_cursor( 0, 1 );
	}
}

void ScreenManager::move_cursor( int _x, int _y ){
	_x = _x * cursor_speed;
	_y = _y * cursor_speed;

	if( cursor_x + _x >= 0 &&  cursor_x + _x <= window.getSize().x){
		cursor_x += _x;
	}
	if( cursor_y + _y >= 0 &&  cursor_y + _y <= window.getSize().y){
		cursor_y += _y;
	}

	cursor_horiz.setPosition( cursor_x, 0 );
	cursor_vert.setPosition( 0, cursor_y );
}

void ScreenManager::postKeyPress( sf::Event _e){
	if( current_screen.size() > 0 ){
		if( state == DELETE_MODULE ){
			// this is the part that allows us to cycle through modules to pich which one to delete
			if( _e.key.code == sf::Keyboard::Left ){
				if( DELETE_INDEX == 0 )
					DELETE_INDEX = current_screen.size() - 1;
				else
					DELETE_INDEX -= 1;

			}else if( _e.key.code == sf::Keyboard::Right || _e.key.code == sf::Keyboard::Tab){
				if( DELETE_INDEX == current_screen.size() - 1 )
					DELETE_INDEX = 0;
				else
					DELETE_INDEX += 1;

			}else if( _e.key.code == sf::Keyboard::Return ){
				deleteModule( DELETE_INDEX );
			}
		}

		if( current_screen.size() > 0 ){
			// we want ot make the bounding box go around the selected index
			int _x = current_screen[DELETE_INDEX]->x;
			int _y = current_screen[DELETE_INDEX]->y;
			int _w = current_screen[DELETE_INDEX]->width;
			int _h = current_screen[DELETE_INDEX]->height;

			deleteBoundingBox.setSize( sf::Vector2f( _w, _h ) );
			deleteBoundingBox.setPosition( _x, _y );

			deleteBoundingBox1.setSize( sf::Vector2f( _w + 20, _h + 20 ) );
			deleteBoundingBox1.setPosition( _x - 10, _y - 10 );

			deleteBoundingBox2.setSize( sf::Vector2f( _w + 30, _h + 30 ) );
			deleteBoundingBox2.setPosition( _x - 15, _y - 15 );
		}
	}
}

void ScreenManager::deleteModule( int _m ){
	std::string _file_contents = "";
	std::string _to_delete;
	std::string _out;
	std::fstream _file;
	char line[255];

	_file.open( currentScreenPath, std::ios::in );
	while( _file.getline( line, 256 ) != 0 ){
		_file_contents += line;
		_file_contents += "\n";
	}
	_file.close();

	// now we search we remove the part of the string that is similar to our deleted module
	_to_delete  = current_screen[ _m ]->dataType;
	_to_delete += " ";
	_to_delete += std::to_string(current_screen[ _m ]->x);
	_to_delete += " ";
	_to_delete += std::to_string(current_screen[ _m ]->y);
	_to_delete += " ";
	_to_delete += std::to_string(current_screen[ _m ]->width);
	_to_delete += " ";
	_to_delete += std::to_string(current_screen[ _m ]->height);
	_to_delete += " ";
	_to_delete += current_screen[ _m ]->dataFile;

	int _pos = _file_contents.find( _to_delete );
	_out = _file_contents.replace( _pos, _to_delete.size() + 1, "" );

	_file.open( currentScreenPath, std::ios::out | std::ios::ate );
	_file << _out;
	_file.close();

	updateScreen();
}

void ScreenManager::updateScreen(){
	std::fstream file;
	current_screen.clear();
	file.open( currentScreenPath, std::ios::in );
	char line[255];
	std::vector<std::string> split;
	int line_number = 0;

	while( file.getline( line, 256 ) != 0 ){
		split = common::splitString( line, " " );
		// this is where we want to create a module object.
		// 	we will pass the values of the split string to a function
		//	that is edited before compile. This function will spit out an
		//	object of type unique_prt<ModuleBase>. We will then add it 
		//	to the current_screen array.
		// SPLIT is in this form:
		//	moduleName x y width height pathToData
		//	any other configuration will spit out an error.
		if( split.size() == 6 ){
			//add( common::PRECOMPILE_createModule( split[0], std::stoi(split[1]), std::stoi(split[2]), std::stoi(split[3]), std::stoi(split[4]), split[5] ) );
			//add( MODULE_FACTORY["PinkModule"]() );
			add( MODULE_FACTORY[split[0]](std::stoi(split[1]), std::stoi(split[2]), std::stoi(split[3]), std::stoi(split[4]), split[5]) );
		}else{
			std::cout << "-> ERROR: could not parse module in " << currentScreenPath << " line: " << line_number << "\n";
		} line_number++;
	}

	file.close();

	// we will fill the add_items menu with the list of possible modules to add
	add_items.clear();
	for( const auto &item : MODULE_FACTORY ){
		add_items.add( MenuItem( item.first, [this](void* _s){this->addModule_start( _s );}, new std::string(item.first) ));
	}

}

void ScreenManager::add( ModuleBase * _item ){
	current_screen.push_back( std::unique_ptr<ModuleBase>( _item ) );
}

void ScreenManager::addModule_start( void* _d ){
	module_to_add =  *((std::string*)_d);
	state = ADD_MODULE;
	cursor_vert.setPosition(0, 0);
	cursor_horiz.setPosition(0, 0);
}

void ScreenManager::addModule_screen( ){
	//	std::cout << "creating new module\n";
	//	std::cout << "\t" << "x1: " << cursor_x_start << " x2: " << cursor_x << " y1: " << cursor_y_start << " y2: " << cursor_y << "\n";
	int _x = cursor_x_start > cursor_x ? cursor_x : cursor_x_start;
	int _y = cursor_y_start > cursor_y ? cursor_y : cursor_y_start;
	int _w = abs(cursor_x - cursor_x_start);
	int _h = abs(cursor_y - cursor_y_start);

	// HERE WE WILL ADD NEW MODULE TO THE SCREEN FILE, THEN WE WILL UPDATE THAT FILE.
	// 	First we have to create a data path for the module -- The name must be unique
	//	Then we will string it along in the following format.
	//		name x y w h path
	//	Then we append to the current screen file
	std::string _out = module_to_add + " " + std::to_string(_x) + " " + std::to_string(_y) + " " + std::to_string(_w) + " " + std::to_string(_h);
	_out += " ";
	_out += "data/module_data/";
	_out += module_to_add;
	_out += "_";
	_out +=  std::to_string(std::time(nullptr));	// not the solution I would have liked. Would rather uniqueness guarantee be a little more dicriptive

	state = EDIT;
	add_items.enable();

	cursor_x = 0;
	cursor_y = 0;

	//	std::cout << x << " + " << w << "\n";
	//	std::cout << y << " + " << h << "\n";
	std::cout << currentScreenPath << "\n";
	std::fstream file;
	file.open( currentScreenPath, std::fstream::out | std::fstream::app );
	file << _out << "\n";
	file.close();

	updateScreen();

}

void ScreenManager::render(){
	for( int i = 0; i < current_screen.size(); i++ ){
		current_screen[i]->render();
	}

	if( state == COMMAND ){

	}else if( state == SCREEN_CHANGE ){

	}else if( state == EDIT ){
		window.draw(border);
		window.draw(state_text);

	}else if( state == ADD_MODULE ){
		window.draw(state_text);
		window.draw( cursor_vert  );
		window.draw( cursor_horiz );
		if( ADD_STATE == 1 ){
			window.draw( new_add_box );
			window.draw( crosshair );
		}
	}else if( state == DELETE_MODULE ){
		window.draw( border );
		window.draw( state_text );
		window.draw( deleteBoundingBox );
		window.draw( deleteBoundingBox1 );
		window.draw( deleteBoundingBox2 );
	}
}

void ScreenManager::input( sf::Event _event ){

	switch( _event.type ){
		case sf::Event::KeyPressed:		// key pressed

			// we will add the keypressed to the buffer when the key is pressed down
			input_buffer.push_back( _event.key.code );

			// handle special inputs
			if( command_execute.isTriggered( input_buffer ) ){
				state = COMMAND;
				textbox_commands.enable();

			}else if( command_screen_change.isTriggered( input_buffer ) ){
				state = SCREEN_CHANGE;
				menu_screens.enable();

			}else if( command_escape.isTriggered( input_buffer ) ){
				state = USE;
				menu_screens.disable();
				textbox_commands.disable();

			}else if( state == ADD_MODULE ){
				move_cursor( _event );
				new_add_box.setSize( sf::Vector2f( cursor_x - new_add_box.getPosition().x, cursor_y - new_add_box.getPosition().y ) );

				if( _event.key.code == sf::Keyboard::Return && (ADD_STATE == 0 || ADD_STATE == -1) ){
					ADD_STATE = 1;
					crosshair.setPosition( cursor_x - 0.5*crosshair.getSize().x, cursor_y - 0.5*crosshair.getSize().y );
					new_add_box.setPosition( cursor_x, cursor_y );
					new_add_box.setSize(sf::Vector2f(0, 0));
					cursor_x_start = cursor_x;
					cursor_y_start = cursor_y;

				}else if( _event.key.code == sf::Keyboard::Return && ADD_STATE == 1 ){
					addModule_screen();
					ADD_STATE = 0;
				}
			}

			// we will give every module in the crurrent screen the keyboard command.
			for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onKeyDown( _event.key.code );
			}
	 		postKeyPress( _event );
			break;

		case sf::Event::LostFocus:		// when the window is out of focus, dont log the keys pressed before.
			input_buffer.clear();
			break;

		case sf::Event::KeyReleased:	// key released
			// we will search the input buffer list for the key code then we will remove that index
			for( int i = 0; i < input_buffer.size(); i++ ){
				if( input_buffer[i] == _event.key.code ){ input_buffer.erase( input_buffer.begin() + i ); }
			}
			// we will give every module in the crurrent screen the keyboard command.
			for( int i = 0; i < current_screen.size(); i++ ){
				current_screen[i]->onKeyUp( _event.key.code );
			}
			break;

		case sf::Event::MouseMoved:		// mouse move
				// we will give every module in the crurrent screen the keyboard command.
			for( int i = 0; i < current_screen.size(); i++ ){
				current_screen[i]->onMouseMove( _event.mouseMove.x, _event.mouseMove.y );
			}
			break;

		case sf::Event::MouseButtonPressed:		// mouse press
			// we will give every module in the crurrent screen the keyboard command.
			for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onMouseDown( _event.mouseButton.button, _event.mouseButton.x, _event.mouseButton.y );
			}
			break;

		case sf::Event::MouseButtonReleased:		// mouse press
			// we will give every module in the crurrent screen the keyboard command.
			for( int i = 0; i < current_screen.size(); i++ ){
				current_screen[i]->onMouseUp( _event.mouseButton.button, _event.mouseButton.x, _event.mouseButton.y );
			}
			break;

		default:
			break;
	}

}

void ScreenManager::test(){
	std::cout << "test\n\n";
}
