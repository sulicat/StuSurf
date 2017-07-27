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
		x_full 			= 0;
		y_full 			= 0;
		width_full 		= 0;
		height_full 	= 0;

		x 			= (float)x_full/WINDOW_WIDTH;
		y 			= (float)y_full/WINDOW_HEIGHT;
		width 		= (float)width_full/WINDOW_WIDTH;
		height 		= (float)height_full/WINDOW_HEIGHT;
	}

	void reshape(){
		std::cout << "reshaping the test_module\n";
		x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
		y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
		width 		= (2*(float)width_full/WINDOW_WIDTH);
		height 		= (2*(float)height_full/WINDOW_HEIGHT);
	}

	void set_size( int _w, int _h ){
		width_full 	= _w;
		height_full = _h;

		width 	= (2*(float)width_full/WINDOW_WIDTH);
		height 	= (2*(float)height_full/WINDOW_HEIGHT);
	}

	void set_pos( int _x, int _y ){
		x_full = _x;
		y_full = _y;

		x = (2*(float)x_full/WINDOW_WIDTH) - 1;
		y = (2*(float)y_full/WINDOW_HEIGHT) - 1;
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
	  	if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			// do something.... we are inside the objects space
			std::cout << "test_module_press \n";
		}
	}

	void mouse_move_passive( int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			std::cout << "test_module_passive_m: " << _x << " " << _y << "\n";
		}
	}

	void mouse_move_active( int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			std::cout << "test_module_active_m: " << _x << " " << _y << "\n";
		}
	}

	void key_press( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			std::cout << "key_press: " << _key << " " << _x << " " << _y << "\n";
		}
	}

	void key_press_special( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			std::cout << "key_press_special: " << _key << " " << _x << " " << _y << "\n";
		}
	}
};
