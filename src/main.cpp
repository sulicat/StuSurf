#include "../include/common.h"
#include "../modules/TextModule.h"

// create the render window.
int WINDOW_WIDTH 	= 	1200;
int WINDOW_HEIGHT 	= 	1000;
sf::RenderWindow 		window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Stusurf" );



class PinkModule : public ModuleBase{
public:
	// standard
	int	 	x;
	int		y;
	int 	width;
	int 	height;
	bool 	isFocused;
	// non standard
	sf::RectangleShape rect1;
	sf::Color c;

	PinkModule( int _x, int _y, int _w, int _h  ){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		isFocused = false;

		// non standard
		rect1 = sf::RectangleShape( sf::Vector2f(width, height) );
		rect1.setPosition( x, y );
		c = sf::Color( 255, 0, 255 );
		rect1.setFillColor( c );

	}

	void onKeyDown(){

	}

	void onKeyUp(){

	}

	void onMouseMovePassive( int _x, int _y ){

	}

	void render(){
		window.draw( rect1 );
	}

};


/* ********************************************************************************** */
int main( int argc, char * * argv ){
	// a test list to start making the program
	TextModule testModule = TextModule( 0, 0, 100, 100 );
	PinkModule testPink = PinkModule( 200, 200, 100, 200 );

	std::vector< std::unique_ptr< ModuleBase >  > list;
	list.push_back( std::unique_ptr<ModuleBase> ( new TextModule( 100, 100, 100, 100 ) ) );
	list.push_back( std::unique_ptr<ModuleBase> ( new PinkModule( 300, 300, 100, 100 ) ) );


	sf::Event event;
	while( window.isOpen() ){

		while( window.pollEvent( event ) ){
			if( event.type == sf::Event::Closed ){
				window.close();
				return 0;
			}
		}

		// render
		window.clear();
		//testModule.render();
		//testPink.render();
		for( int i = 0; i < list.size(); i++ ){
			list[i]->render();
		}
		
		window.display();
	}






	return 0;
}
