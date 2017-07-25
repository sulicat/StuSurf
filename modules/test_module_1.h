#include "../include/common.h"
#include <GL/glut.h>

class test_module_1 : public Base{
public:

	int 	x_full;
	int 	y_full;
	float 	width_full;
	float 	height_full;
	float 	x;
	float 	y;
	float 	width;
	float 	height;

	test_module_1( ){
		std::cout << "creating a new testing_module\n";
		x_full 		= 0;
		y_full 		= 0;
		width_full 	= 200;
		height_full = 100;

		x_full -= 100;
		y_full -= 100;

		x 		= (float)x_full/WINDOW_WIDTH;
		y 		= (float)y_full/WINDOW_HEIGHT;
		width 	= (float)width_full/WINDOW_WIDTH;
		height 	= (float)height_full/WINDOW_HEIGHT;
	}

	void set_size( int _w, int _h ){
		width_full = _w;
		height_full = _h;

		width 	= (float)width_full/WINDOW_WIDTH;
		height 	= (float)height_full/WINDOW_HEIGHT;
	}

	void set_pos( int _x, int _y ){
		x_full = _x;
		y_full = _y;

		x 		= (float)x_full/WINDOW_WIDTH;
		y 		= (float)y_full/WINDOW_HEIGHT;
	}

	void render(){
		glColor3f( 1.0, 0.0, 0.0 );
		glBegin( GL_QUADS );
			glVertex3f( x, y, 0 );
			glVertex3f( x + width, y, 0 );
			glVertex3f( x + width, y + height , 0 );
			glVertex3f( x, y + height, 0 );
		glEnd();

	}

	void mouse_press( int _button, int _state, int _x, int _y ){
		// first we check if there is an intersection
		//check_inside_rect( _x, _y,  )
	}

};