class TextModule : public ModuleBase{
public:
	// standard
	int	 	x;
	int		y;
	int 	width;
	int 	height;
	bool 	isFocused;
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

	void testPrint(  ){ std::cout << "hello \n"; }

	void onKeyDown(){

	}

	void onKeyUp(){

	}

	void onMouseMovePassive( int _x, int _y ){

	}

	void render(){
		testPrint();
		window.draw( rect1 );
		window.draw( rect2 );
	}

};
