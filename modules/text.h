#include "../include/common.h"
#include <GL/glut.h>

class text : public Base{
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
	std::string type_name;
	std::string path_data;

	std::string content;

	text( ){
		content 		= "Click Me";
	}

	void reshape(){
		x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
		y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
		width 		= (2*(float)width_full/WINDOW_WIDTH);
		height 		= (2*(float)height_full/WINDOW_HEIGHT);
	}

	void render(){
		glColor3f( 0.0, 1.0, 0.0 );
		Common::render_string( x, y + height*0.3, height * 0.5, content );
	}

	void mouse_press( int _button, int _state, int _x, int _y ){
		// first we check if there is an intersection
	  	if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			// do something.... we are inside the objects space
			if( _state == 0 ){
				std::cout << path_data << "\n";
			}
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

};
