#include "../include/ScreenManager.h"
#include "../include/common.h"
#include "../include/Managers.h"

void temp_print1( void* _a ){
	std::cout << "hello world 1111 \n";
	std::cout << _a << "\n";
}

void temp_print2( void* _a ){
	std::cout << "hello world 22222 \n";
	std::cout << _a << "\n";
}

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


	command_test1 = KeyBind( "This is the command that allows you to switch between different screens" );
	command_test1.add_command( sf::Keyboard::LControl );
	command_test1.add_command( sf::Keyboard::D );


	menu_screens = Menu( "Screens" );
	menu_screens.set_position( 10, 10 );
	menu_screens.set_size( 300, 400 );
	menu_screens.add( MenuItem("hello worlf") );
	menu_screens.add( MenuItem("test1", temp_print1) );
	menu_screens.add( MenuItem("test2", temp_print2) );
	menu_screens.add( MenuItem("test1", temp_print1, &menu_test1) );
	menu_screens.add( MenuItem("test2") );
	menu_screens.add( MenuItem("test1") );
	menu_screens.add( MenuItem("test2") );
	menu_screens.add( MenuItem("test1") );
	menu_screens.add( MenuItem("test2") );
	menu_screens.add( MenuItem("test1") );
	menu_screens.add( MenuItem("test2") );
	menu_screens.add( MenuItem("test1") );
	menu_screens.add( MenuItem("test2") );
	menu_screens.add( MenuItem("test1") );
	menu_screens.add( MenuItem("test2") );

	menu_test1 = Menu( "test1" );
	menu_test1.set_position( 200, 10 );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf", temp_print1, &menu_test2) );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );
	menu_test1.add( MenuItem("hello worlf") );
	menu_test1.add( MenuItem("test1") );


	menu_test2 = Menu( "test1" );
	menu_test2.set_position( 400, 10 );
	menu_test2.add( MenuItem("bbbbb") );
	menu_test2.add( MenuItem("aaaa") );
	menu_test2.add( MenuItem("bbbbb") );
	menu_test2.add( MenuItem("aaaa") );
	menu_test2.add( MenuItem("bbbbb") );
	menu_test2.add( MenuItem("aaaa") );

}

void ScreenManager::add( ModuleBase * _item ){
	current_screen.push_back( std::unique_ptr<ModuleBase>( _item ) );
}

void ScreenManager::render(){
	for( int i = 0; i < current_screen.size(); i++ ){
		current_screen[i]->render();
	}

	if( state == COMMAND ){
		std::cout << "commands\n";

	}else if( state == SCREEN_CHANGE ){

	}else{

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
				menu_screens.disable();

			}else if( command_screen_change.isTriggered( input_buffer ) ){
				state = SCREEN_CHANGE;
				menu_screens.enable();

			}else if( command_escape.isTriggered( input_buffer ) ){
				state = USE;
				menu_screens.disable();

			}else if( command_test1.isTriggered( input_buffer ) ){
				menu_test1.enable();
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
