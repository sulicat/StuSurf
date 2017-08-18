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
	int		ID;
	std::string path_data;

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

	void render(){
		glColor3f( 1.0, 0.0, 0.0 );
		glBegin( GL_QUADS );
			glVertex3f( x, y, 0 );
			glVertex3f( x + width, y, 0 );
			glVertex3f( x + width, y + height , 0 );
			glVertex3f( x, y + height, 0 );
		glEnd();

		Common::render_paragraph( x, y + height, width, height, 0.03, "hello world 1 hello world 2 a b c abcdefg this is a paragraph. It says stuff. But you shouldnt read it cuz it is lots of stuff.", 1, 1, 1, 1 );

	}

	void mouse_press( int _button, int _state, int _x, int _y ){
		// first we check if there is an intersection
	  	if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			// do something.... we are inside the objects space
			std::cout << "\ntest_module_press NEW GET \n";
			std::cout << ID << "\n";
			std::cout << get_path_data() << "\n";
			std::cout << get_type_name() << "\n";
		}
	}

	void mouse_move_passive( int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			//std::cout << "test_module_passive_m: " << _x << " " << _y << "\n";
		}
	}

	void mouse_move_active( int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			//std::cout << "test_module_active_m: " << _x << " " << _y << "\n";
		}
	}

	void key_press( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			//std::cout << "key_press: " << _key << " " << _x << " " << _y << "\n";
		}
	}

	void key_press_special( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			//std::cout << "key_press_special: " << _key << " " << _x << " " << _y << "\n";
		}
	}


	void key_release( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			//std::cout << "key_release: " << _key << " " << _x << " " << _y << "\n";
		}
	}

	void key_release_special( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			//std::cout << "key_release_special: " << _key << " " << _x << " " << _y << "\n";
		}
	}

	void set_path( char * _p ){

	}
};
