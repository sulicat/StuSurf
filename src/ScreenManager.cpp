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

	// Text Boxes
	textbox_commands = CommandBox( );
	textbox_commands.set( &Main_Commands );
}

void ScreenManager::changeScreen( std::string _p ){
	currentScreenPath = _p;
	updateScreen();
}

void ScreenManager::changeState( enum PROGRAM_STATE _s ){
	state = _s;

	// in the case of edit we want to:
	//		enable the menu that will add new modules
	if( state == EDIT ){
		add_items.enable();
	}
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
	for( int i = 0; i < MODULE_FACTORY.size(); i++ ){
		add_items.add( MenuItem( "hello world" ) );
	}

}

void ScreenManager::add( ModuleBase * _item ){
	current_screen.push_back( std::unique_ptr<ModuleBase>( _item ) );
}

void ScreenManager::render(){
	for( int i = 0; i < current_screen.size(); i++ ){
		current_screen[i]->render();
	}

	if( state == COMMAND ){

	}else if( state == SCREEN_CHANGE ){

	}else if( state == EDIT ){
		
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
			}

			// we will give every module in the crurrent screen the keyboard command.
			for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onKeyDown( _event.key.code );
			}
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
