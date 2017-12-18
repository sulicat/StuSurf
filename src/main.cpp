#include "../include/headers.h"
#include "../include/ScreenManager.h"

#define KEY_REPEAT false

// create the render window.
int WINDOW_WIDTH 			= 	1200;
int WINDOW_HEIGHT 			= 	1000;
enum PROGRAM_STATE State	=	USE;
sf::RenderWindow 			window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Stusurf" );
// input buffer
std::vector<int>			input_buffer;
// menus that are recieving input
std::vector< Menu* >	list_enabled_menus;
// colors
sf::Color COLOR_PRIMARY 			= sf::Color( 100,  58,   22 );
sf::Color COLOR_PRIMARY_DARK 		= sf::Color( 77,   35,   0 );
sf::Color COLOR_PRIMARY_PALE 		= sf::Color( 100,  67,   38 );
sf::Color COLOR_PRIMARY_LIGHT 		= sf::Color( 100,  46,   0 );
sf::Color COLOR_SECONDARY_1 		= sf::Color( 54,   89,   176 );
sf::Color COLOR_SECONDARY_1_LIGHT 	= sf::Color( 18,   62,   171 );
sf::Color COLOR_SECONDARY_1_PALE 	= sf::Color( 87,   117,  192 );
sf::Color COLOR_SECONDARY_1_DARK 	= sf::Color( 13,   47,   132 );
sf::Color COLOR_SECONDARY_2 		= sf::Color( 46,   204,  56 );
sf::Color COLOR_SECONDARY_2_LIGHT 	= sf::Color( 0,    201,  13 );
sf::Color COLOR_SECONDARY_2_PALE 	= sf::Color( 83,   214,  92 );
sf::Color COLOR_SECONDARY_2_DARK 	= sf::Color( 0,	   155,  10 );
sf::Color COLOR_WHITE				= sf::Color( 255,  255,  255 );
sf::Color COLOR_BLACK				= sf::Color( 0,    0,    0 );
// fonts
sf::Font MAIN_FONT;


// will handle controlled input and hold a list of modules.
ScreenManager mother 		= ScreenManager( "/home/suli/stusurf" );

/* ********************************************************************************** */
int main( int argc, char * * argv ){
	// set font
 	if (!MAIN_FONT.loadFromFile("fonts/calibri.ttf")){
		std::cout << "FONT WAS NOT ABLE TO LOAD\n";
	}

	window.setKeyRepeatEnabled( KEY_REPEAT );

	//	mother.add( new TextModule( 100, 100, 100, 100 ) );
	//	mother.add( new PinkModule( 300, 300, 100, 100 ) );
	mother.add( new MultiMeter1( 100, 100, 500, 500 ) );

	sf::Event event;
	while( window.isOpen() ){

		while( window.pollEvent( event ) ){
			switch( event.type ){

				case sf::Event::Closed:			// close the window
					window.close();
					return 0;
					break;

				default:
					if( list_enabled_menus.size() > 0 ){
						for( int i = 0; i < list_enabled_menus.size(); i++ ){
							list_enabled_menus[i]->event( event );
						}
					}else{
						mother.input( event );
					}

					break;
			}
		}

		// render
		window.clear();
		mother.render();
		for( int i = 0; i < list_enabled_menus.size(); i++ ){
			list_enabled_menus[i]->render();
		}
		window.display();

	}

	return 0;
}
