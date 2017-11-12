#include "../include/common.h"

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

	void onKeyDown( int _code ){
	}

	void onKeyUp( int _code ){
	}

	void onMouseMove( int _x, int _y ){
	}

	void onMouseDown( int _button, int _x, int _y ){
	}

	void onMouseUp(int _button, int _x, int _y ){
	}

	void render(){
		window.draw( rect1 );
	}

};
