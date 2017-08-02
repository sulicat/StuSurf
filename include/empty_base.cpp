#include "common.h"

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

	// none of the functions do anuthing
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
