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
	bool 		has_been_set;
	float		RED_CHOICE[7];
	float		GREEN_CHOICE[7];
	float		BLUE_CHOICE[7];
	int			current_selected;
	TextField 	input_field;
	bool		is_being_edited;

	text( ){
		// this module will have 2 vars in a file.
		// the first registers whether or not it has been set.
		// the second stores the content.
		content = "Click Me!";
		has_been_set = false;
		current_selected = 0;

		RED_CHOICE[0] = 1;	GREEN_CHOICE[0] = 0; BLUE_CHOICE[0] = 0;
		RED_CHOICE[1] = 0;	GREEN_CHOICE[1] = 1; BLUE_CHOICE[1] = 0;
		RED_CHOICE[2] = 0;	GREEN_CHOICE[2] = 0; BLUE_CHOICE[2] = 1;
		RED_CHOICE[3] = 1;	GREEN_CHOICE[3] = 1; BLUE_CHOICE[3] = 0;
		RED_CHOICE[4] = 1;	GREEN_CHOICE[4] = 0; BLUE_CHOICE[4] = 1;
		RED_CHOICE[5] = 0;	GREEN_CHOICE[5] = 1; BLUE_CHOICE[5] = 1;
		RED_CHOICE[6] = 1;	GREEN_CHOICE[6] = 0; BLUE_CHOICE[6] = 1;

		input_field.set_selected( true );
		input_field.set_pos( x_full, y_full - height_full*0.5 );
		input_field.set_size( width_full * 2, height_full * 0.5 );
		is_being_edited = false;
	}

	void reshape(){
		x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
		y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
		width 		= (2*(float)width_full/WINDOW_WIDTH);
		height 		= (2*(float)height_full/WINDOW_HEIGHT);
		input_field.set_pos( x_full, y_full - height_full*0.5 );
		input_field.set_size( width_full * 2, height_full * 0.5 );

		// if the content exists. Simply read it.
		// if it does not. The next click will open a text feild that will allow you to set the content
		if( Common::var_from_file( path_data, "content" ).size() <= 0 ){
			has_been_set = false;

		}else {
			has_been_set = true;
			content = Common::var_from_file( path_data, "content" )[0];
			current_selected = Common::string_to_int( Common::var_from_file( path_data, "current_selected_color" )[0] );
		}

	}

	void render(){
		glColor3f( RED_CHOICE[current_selected], GREEN_CHOICE[current_selected], BLUE_CHOICE[current_selected] );
		Common::render_string( x, y + height*0.3, height * 0.5, content );
		if( is_being_edited ) input_field.render();
	}

	void mouse_press( int _button, int _state, int _x, int _y ){
		// first we check if there is an intersection
	  	if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			std::cout << path_data << "\n";
			// do something.... we are inside the objects space
			if( _state == 0 ){
				// if the content has not been decided, this next click will create the content.
				if( has_been_set == false ){
					is_being_edited = true;
					Common::var_to_file( path_data, "content", "haha" );
					Common::var_to_file( path_data, "current_selected_color", Common::int_to_string(0) );
					content = Common::var_from_file( path_data, "content" )[0];
					has_been_set = true;

				}else{
					current_selected += 1;
					if(current_selected >= 7 ){ current_selected = 0; }
					Common::var_to_file( path_data, "current_selected_color", Common::int_to_string(current_selected) );
				}
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
		if( is_being_edited ){
			if( (int)_key == 8 ){
				input_field.backspace();

			}else if( (int)_key == 13 ){
				content = input_field.value();
				is_being_edited = false;
				Common::var_to_file( path_data, "content", content );
				Common::var_to_file( path_data, "current_selected_color", "0" );
				input_field.clear();

			}else{
				input_field.add( _key );
			}
		}
	}

	void key_press_special( unsigned char _key, int _x, int _y ){
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){

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
