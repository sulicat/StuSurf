#ifndef COMMON_H
#define COMMON_H

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

// this is the common file. It will include the base class that the main modules can inherit from.
// first we make an abstract class. If we want to make a button, we can inherit from this class and define all the virtual functions we need.
class Base{
public:
	int x_full;
	int y_full;
	int width_full;
	int height_full;
	float x;
	float y;
	float width;
	float height;

	virtual void render() = 0;
	virtual void mouse_press( int _button, int _state, int _x, int _y  ) = 0;
	virtual void set_size( int _w, int _h ) = 0;
	virtual void set_pos( int _x, int _y ) = 0;
	virtual void reshape() = 0;
	virtual void mouse_move_passive( int _x, int _y ) = 0;
	virtual void mouse_move_active( int _x, int _y ) = 0;
	virtual void key_press( unsigned char _key, int _x, int _y ) = 0;
	virtual void key_press_special( unsigned char _key, int _x, int _y ) = 0;
};


/*************************************************************************/

// these are some functions that can be used by the modules that need them
class Common{
public:
   	static bool check_inside_rect( int _x, int _y, int rect_x, int rect_y, int rect_width, int rect_height );

};
#endif
