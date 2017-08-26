#include "../include/common.h"
#include <GL/glut.h>

class text_spinning : public Base{
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
	std::string type;
	std::string path_data;

	float angle;

	text_spinning( ){
		
	}

	void reshape(){
		x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
		y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
		width 		= (2*(float)width_full/WINDOW_WIDTH);
		height 		= (2*(float)height_full/WINDOW_HEIGHT);
	}

	void render(){
		
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

};
