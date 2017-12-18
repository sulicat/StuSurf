#include "../include/ScreenManager.h"
#include "../include/common.h"

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

	testMenu = Menu( "test menu" );
	testMenu.set_position( 10, 10 );
	testMenu.add( MenuItem("hello worlf") );
	testMenu.add( MenuItem("test1") );
	testMenu.add( MenuItem("test2") );

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
		testMenu.render();

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

			}else if( command_screen_change.isTriggered( input_buffer ) ){
				state = SCREEN_CHANGE;

			}else if( command_escape.isTriggered( input_buffer ) ){
				state = USE;
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


	for( int i = 0; i < input_buffer.size(); i++ ){
		//std::cout << input_buffer[i] << " ";
	}std::cout << "\n";

}

void ScreenManager::test(){
	std::cout << "test\n\n";
}
