// this is the common file
// it will include the:
//	- inheritance bases for modules we make
// 	- global variables we want everything to have access to.
// 	- some common imports.
#ifndef STUSURF_COMMON
#define STUSURF_COMMON

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern sf::RenderWindow window;

enum PROGRAM_STATE{
	EDIT,
	USE
};

class ModuleBase{
public:
	int 	x;
	int 	y;
	int 	width;
	int 	height;
	bool 	isFocused;

	virtual void onKeyDown		( int code )					{ std::cout << "key DOWN function UNDEFINED in module\n";	}
	virtual void onKeyUp		( int code )					{ std::cout << "key UP function UNDEFINED in module\n";		}
	virtual void onMouseMove	( int x, int y  )				{ std::cout << "mouse MOVE function UNDEFINED in module\n";	}
	virtual void onMouseDown	( int button, int x, int y )	{ std::cout << "mouse DOWN function UNDEFINED in module\n";	}
	virtual void onMouseUp		( int button, int x, int y )	{ std::cout << "mouse UP function UNDEFINED in module\n";	}
	virtual void render			()								{};
};

#endif
