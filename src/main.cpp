#include "../include/headers.h"
#include "../include/common.h"
#include "../include/ScreenManager.h"
#include "../include/GuiManager.h"

#define KEY_REPEAT false

// create the render window.
int WINDOW_WIDTH 			= 	1200;
int WINDOW_HEIGHT 			= 	1000;
int MENU_WIDTH				=	300;
int MENU_HEIGHT				=	400;
// program states
enum PROGRAM_STATE State	=	USE;
// main window
sf::RenderWindow 			window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Stusurf" );
// input buffer
std::vector<int>			input_buffer;
// Main Command List
std::vector<Command>	 	Main_Commands;

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
sf::Color COLOR_GREY				= sf::Color( 100,  100,  100 );

sf::Color COLOR_Menu_1				= sf::Color( 100,  100,  100, 245 );
sf::Color COLOR_Menu_2				= sf::Color( 100,  100,  100 );
sf::Color COLOR_Menu_3				= sf::Color( 255,  100,  100 );
sf::Color COLOR_Menu_4				= sf::Color( 255,  255,  255 );

sf::Color COLOR_CommandBox_1			= sf::Color( 100,  100,  100, 245 );
sf::Color COLOR_CommandBox_2			= sf::Color( 255,  255,  255 );
sf::Color COLOR_CommandBox_3			= sf::Color( 255,  100,  100 );

// textures
sf::Texture	ICON_FOLDER;
// fonts
sf::Font 	MAIN_FONT;


// will handle controlled input and hold a list of modules.
ScreenManager screenManager 		= ScreenManager( "/home/suli/stusurf" );
// will handle Gui elements.
GuiManager guiManager 				= GuiManager();



/* ********************************************************************************** */
int main( int argc, char * * argv ){
	// set font
 	if (!MAIN_FONT.loadFromFile("fonts/calibri.ttf")){
		std::cout << "FONT WAS NOT ABLE TO LOAD\n";
	}
	// load the images
	ICON_FOLDER.loadFromFile( "images/icon_folder.png");

	window.setKeyRepeatEnabled( KEY_REPEAT );

	common::PRECOMPILE_populate_module_factory();
	screenManager.changeScreen( "data/screens/Home" );

	// ADDING commands.
	std::string _temp_test = "I am a cat";
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test1" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test2" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test3" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test4" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test5" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test6" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test7" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test8", &_temp_test) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test9" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << *(std::string*)_a << "\n"; }, "test10", &_temp_test ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test20" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test30" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test40" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test50" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test60" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test70" ) );
	Main_Commands.push_back( Command( [](void* _a){ std::cout << "It workms\n\n"; }, "test80" ) );



	sf::Event event;
	while( window.isOpen() ){

		while( window.pollEvent( event ) ){
			switch( event.type ){

				case sf::Event::Closed:			// close the window
					window.close();
					return 0;
					break;

				case sf::Event::Resized:		// resize the window
			        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					break;

				default:
					if( guiManager.is_intercepting_input() ){
						guiManager.input( event );
					}else{
						screenManager.input( event );
					}

					break;
			}
		}

		// render
		window.clear();
		screenManager.render();
		guiManager.render();
		window.display();

	}

	return 0;
}
