class TextModule : public ModuleBase{
public:
	// non standard
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;

	TextModule( int _x, int _y, int _w, int _h  ){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		isFocused = false;

		// non standard
		rect1 = sf::RectangleShape( sf::Vector2f(width/2, height/2) );
		rect1.setPosition( x, y );

		rect2 = sf::RectangleShape( sf::Vector2f(width/2, height/2) );
		rect2.setPosition( x + width/2, y + height/2 );
	}

	//	void onKeyDown( int _code ){
		//std::cout << "down: " << _code << "\n";
	//	}

	void onKeyUp( int _code ){
		//std::cout << "up: " << _code << "\n";
	}

	void onMouseMove( int _x, int _y ){
		//std::cout << "\n\n" << _x << " " << _y << "\n";
	}

	void onMouseDown( int _button, int _x, int _y ){
		//std::cout << _button << " " << _x << " " << _y << "\n";
	}

	void onMouseUp(int _button, int _x, int _y ){
		//std::cout << _button << " " << _x << " " << _y << "\n";
	}

	void render(){
		rect2.setPosition( x + width/2, y + height/2 );
		rect1.setPosition( x, y );
		window.draw( rect1 );
		window.draw( rect2 );
	}

};
