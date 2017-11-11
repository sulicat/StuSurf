// this is the common file
// it will include the:
//	- inheritance bases for modules we make
// 	- global variables we want everything to have access to.
// 	- some common imports.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern sf::RenderWindow window;

class ModuleBase{
public:
	int x;
	int y;
	int width;
	int height;
	bool isFocused;

	virtual void onKeydown(){};
	virtual void onKeyUp(){};
	virtual void onMouseMovePassive(){};
	virtual void render(){};
};
