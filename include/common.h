#ifndef COMMON_H
#define COMMON_H

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

#include <iostream>
#include <sstream>

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

	class empty_module : public Base {
	public:
		int 	x_full;
		int 	y_full;
		float 	width_full;
		float 	height_full;
		float 	x;
		float 	y;
		float 	width;
		float 	height;

		empty_module( ){
			std::cout << "creating an EMPTY MODULE\n";
			x_full 			= 0;
			y_full 			= 0;
			width_full 		= 0;
			height_full 	= 0;
		}

		// none of the functions do anything
		void reshape(){}
		void set_size( int _w, int _h ){}
		void set_pos( int _x, int _y ){}
		void render(){}
		void mouse_press( int _button, int _state, int _x, int _y ){}
		void mouse_move_passive( int _x, int _y ){}
		void mouse_move_active( int _x, int _y ){}
		void key_press( unsigned char _key, int _x, int _y ){}
		void key_press_special( unsigned char _key, int _x, int _y ){ }
	};



   	static bool 			check_inside_rect	( int _x, int _y, int rect_x, int rect_y, int rect_width, int rect_height );
	static std::string 		int_to_string		( int _num );
	static int 				string_to_int		( std::string _input );
	static float 			string_to_float		( std::string _input );
	static std::string * 	split_string		( char * input, char delim  ); // the length is in retval[0] as a string
	static std::string * 	split_string		( std::string input, char delim  ); // the length is in retval[0] as a string

};

#endif
