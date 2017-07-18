
#ifndef COMMON_H
#define COMMON_H

// this is the common file. It will include the base class that the main modules can inherit from.

// first we make an abstract class. If we want to make a button, we can inherit from this class and define all the virtual functions we need.
class Base{
public:
	float x;
	float y;
	float width;
	float height;

	virtual void render() = 0;
	//virtual void get_mouse_input() = 0;


};


#endif