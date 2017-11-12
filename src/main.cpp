#include "../include/headers.h"

// create the render window.
int WINDOW_WIDTH 			= 	1200;
int WINDOW_HEIGHT 			= 	1000;
enum PROGRAM_STATE State	=	USE;
sf::RenderWindow 			window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Stusurf" );



/* ********************************************************************************** */
int main( int argc, char * * argv ){
	// a test list to start making the program
	TextModule testModule = TextModule( 0, 0, 100, 100 );
	PinkModule testPink = PinkModule( 200, 200, 100, 200 );

	std::vector< std::unique_ptr< ModuleBase >  > current_screen;
	current_screen.push_back( std::unique_ptr<ModuleBase> ( new TextModule( 100, 100, 100, 100 ) ) );
	current_screen.push_back( std::unique_ptr<ModuleBase> ( new PinkModule( 300, 300, 100, 100 ) ) );


	sf::Event event;
	while( window.isOpen() ){

		while( window.pollEvent( event ) ){
			switch( event.type ){

			case sf::Event::Closed:			// close the window
				window.close();
				return 0;
				break;

			case sf::Event::KeyPressed:		// key pressed
				// we will give every module in the crurrent screen the keyboard command.
				for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onKeyDown( event.key.code );
				}
				break;

			case sf::Event::KeyReleased:	// key released
				// we will give every module in the crurrent screen the keyboard command.
				for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onKeyUp( event.key.code );
				}
				break;

			case sf::Event::MouseMoved:		// mouse move
				// we will give every module in the crurrent screen the keyboard command.
				for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onMouseMove( event.mouseMove.x, event.mouseMove.y );
				}
				break;

			case sf::Event::MouseButtonPressed:		// mouse press
				// we will give every module in the crurrent screen the keyboard command.
				for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onMouseDown( event.mouseButton.button, event.mouseButton.x, event.mouseButton.y );
				}
				break;

			case sf::Event::MouseButtonReleased:		// mouse press
				// we will give every module in the crurrent screen the keyboard command.
				for( int i = 0; i < current_screen.size(); i++ ){
					current_screen[i]->onMouseUp( event.mouseButton.button, event.mouseButton.x, event.mouseButton.y );
				}
				break;

			default:
				break;
			}
		}

		// render
		window.clear();
		for( int i = 0; i < current_screen.size(); i++ ){
			current_screen[i]->render();
		}
		window.display();




	}

	return 0;
}
