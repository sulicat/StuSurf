#include "../include/common.h"

class PinkModule : public ModuleBase{
public:
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
		//std::cout << "code: " << _code << "\n";
	}

	void onKeyUp( int _code ){
	}

	void onMouseMove( int _x, int _y ){
	}

	void onMouseDown( int _button, int _x, int _y ){
	}

	void onMouseUp(int _button, int _x, int _y ){
		//std::cout << "_button: " << _button << "\n";
	}

	void render(){
		window.draw( rect1 );
	}

};
