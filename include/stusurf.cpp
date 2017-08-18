#include <iostream>
#include "stusurf.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <GL/glut.h>
#include <fstream>

/************************************************************************************************************************************/


// the constructor
Stusurf::Stusurf( std::string _start ){
	// set the path
	screens_dir_path = _start;
	current_selected_screen = _start + "home";
	std::cout << "Loading New screen located at: " << _start << "\n";

	// start off with ana empty list of objects
	main_list 		= new Base*[0];
	main_list_len 	= 0;
	add_mode 		= 0;	// 0=off; 1=next_click_start; 2=creating_object
	add_x_start 	= 0;
	add_x_end		= 0;
	add_y_start		= 0;
	add_y_end		= 0;
	object_to_add	= "blank";
	delete_mode		= false;
	control_pressed	= false;
	delete_bounding_box[4]  = {0};
	delete_selected_index 	= -1;
	current_ID_count		= 0;

	// this is the screen select menu, it will
	Menu menu_screen_select = Menu();
	menu_screen_select.set_number_of_items(8);
	menu_screen_select.set_height( 200 );
	menu_screen_select.set_width( 300 );
	menu_screen_select.set_shortcut( SHORTCUT_SCREEN );
	menu_screen_select.set_name( "Screens" );

	// this is the add menu, it will add new modules to the current screen
	Menu menu_screen_add = Menu();
	menu_screen_add.set_number_of_items(8);
	menu_screen_add.set_height( 200 );
	menu_screen_add.set_width( 300 );
	menu_screen_add.set_shortcut( SHORTCUT_ADD );
	menu_screen_add.set_name( "Add" );

	// adding the menus to a list of menus. Makes sending input and rendering
	//	simpler
	add(menu_screen_select);
	add(menu_screen_add);

	textfield_new_screen = TextField();
	textfield_new_screen.set_pos(0,0);
	textfield_new_screen.set_size( 900, 150 );
	textfield_new_screen.set_selected( true );


	// this will read the list of screens.
	//	It will populate the screens menu with the buttons to switch screens.
	//	it will also add a new button that will allow for the creation of new screens
	evaluate_screen_list();
	// we have a file made prior to compilation that will give us a list of
	//  available modules. So we will loop throught them and add the to the add menu
	evaluate_module_list();

}

/************************************************************************************************************************************/
// this is the test print function
void Stusurf::toString( void ){
	std::cout << "empty test function" << "\n";
}

void Stusurf::reshape(){
	std::cout << "stusurf reshape to: " << WINDOW_WIDTH << " " << WINDOW_HEIGHT << "\n";
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->reshape();
	}

	// send reshape to menus
	for( int i = 0; i < menus_len; i++ ){
		menus[i].reshape();
	}

	textfield_new_screen.reshape();
}


void Stusurf::evaluate_screen_list(){
	// read the file with all the screen names. Create menu items with these names
	char _line[256];
	std::string _line_string;
	std::ifstream screen_list;
	screen_list.open( SCREEN_LIST_FILE, std::ifstream::in );

	std::cout << "... evaluating list of Screens\n";
	std::cout << "... creating new change screens buttons\n";

	while( screen_list.getline( _line, 256 ) ){
		_line_string = _line;
		// each menu item will have the ability to switch screens,
		//	we had to use labdas because the callback is an overrided function
		menus[0].add( _line_string, [this](std::string _a){return this->change_selected_screen(_a);}, _line_string );
		std::cout << "... ... " << _line_string << "\n";
	}

	screen_list.close();
	std::cout << "... ... ... DONE evaluating screens\n";

	// We will now add the button to allow the creation of new screen.
	menus[0].add( "New...", [this](std::string _a){return this->trigger_new_screen_mode(_a);}, "Null" );
}

void Stusurf::evaluate_module_list(){
	char _line[256];
	std::string _line_string;
	std::ifstream module_list;
	module_list.open( "include/module_list", std::ifstream::in );

	std::cout << "... evaluating list of Modules\n";
	std::cout << "... creating new add buttons to add Menu\n";

	while( module_list.getline( _line, 256 ) ){
		_line_string = _line;
		// each menu item will have the ability to switch screens,
		//	we had to use labdas because the callback is an overrided function
		menus[1].add( _line_string, [this](std::string _a){return this->trigger_object_add(_a);}, _line_string );
		std::cout << "... ... " << _line_string << "\n";
	}

	std::cout << "... ... ... DONE evaluating modules\n";
	module_list.close();
}

void Stusurf::create_new_screen(std::string _name){
	std::fstream screen_file;
	screen_file.open( SCREEN_LIST_FILE, std::fstream::out | std::fstream::app );
	screen_file << _name + "\n";
	screen_file.close();
	evaluate_screen_list();
}

int Stusurf::trigger_object_add( std::string _n ){
	object_to_add = _n;
	add_mode = 1;
	add_mode_mouse = 1;
	add_x_start = 0;
	add_y_start = 0;
	add_x_end 	= 0;
	add_y_end	= 0;
	return 1;
}

int Stusurf::trigger_new_screen_mode( std::string _a ){
	add_new_screen_mode = true;
	return 1;
}

int Stusurf::change_selected_screen( std::string _n ){
	current_selected_screen = screens_dir_path + _n;
	evaluate_screen();
	return 1;
}

void Stusurf::give_window_size( int * _w, int * _h ){
	width = _w;
	height = _h;
}

void Stusurf::mouse_press( int _button, int _state, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;

	// if we are in delet mode, we want ot delete the item on the left press down
	if( delete_mode == true && _button == 0 && _state == 0 ){
		delete_item( delete_selected_index );
		push_list_to_screen();
		//evaluate_screen();
	}

	// we will only send input to the modules when none of the
	//	main menus is open
	bool _any_m_open = false;
	for( int i = 0; i < menus_len; i++ ){
		menus[i].mouse_press( _button, _state, _x, recalc_y );
		if( menus[i].is_shown ){
			_any_m_open = true;
		}
	}

	if( _any_m_open == false ){
		for( int i = 0; i < main_list_len; i++ ){
			main_list[i]->mouse_press( _button, _state, _x, recalc_y );
		}
	}

	// mouse add handling
	if( _state == 1 && add_mode_mouse == 1 ){
		add_mode_mouse = 2;

	}else if( _state == 0 && add_mode_mouse == 2){
		add_x_start = _x;
		add_y_start = recalc_y;
		add_x_end = _x;
		add_y_end = recalc_y;
		add_mode_mouse = 3;

	// this is the final mouse release
	}else if( _state == 1 && add_mode_mouse == 3 ){
		add_x_end = _x;
		add_y_end = recalc_y;
		add_mode_mouse = 0;

		int _x_1 = add_x_start;
		int _y_1 = add_y_start;
		int _x_2 = add_x_end;
		int _y_2 = add_y_end;

		// Now we can create a new object and add it to the list
		add_new_object_to_screen( Common::MIN( _x_1, _x_2 ), Common::MIN( _y_1, _y_2 ), Common::ABS( add_x_end - add_x_start ), Common::ABS( add_y_end - add_y_start), object_to_add );
	}

}

void Stusurf::delete_item( int _index ){
	if( _index >= 0 && _index < main_list_len ){
		// we want to pop the item at _index from the main_list array
		Base * * temp = new Base* [main_list_len - 1];
		std::copy( main_list, main_list + _index, temp );
		std::copy( main_list + _index + 1, main_list + main_list_len, temp + _index );
		delete[] main_list;
		main_list = temp;
		main_list_len -= 1;
	}
}

void Stusurf::push_list_to_screen(){
	std::fstream screen_file;
	screen_file.open( current_selected_screen, std::fstream::out | std::fstream::trunc );
	std::string _content = "";

	for( int i = 0; i < main_list_len; i++ ){
		_content = "";
		_content += main_list[i]->get_type_name();
		_content += " ";
		_content += Common::int_to_string(((Common::empty_module *)main_list[i])->x_full);
		_content += " ";
		_content += Common::int_to_string(((Common::empty_module *)main_list[i])->y_full);
		_content += " ";
		_content += Common::int_to_string(((Common::empty_module *)main_list[i])->width_full);
		_content += " ";
		_content += Common::int_to_string(((Common::empty_module * )main_list[i])->height_full);
		_content += " ";
		_content += main_list[i]->get_path_data();
		_content += " ";
		_content += Common::int_to_string(main_list[i]->get_ID());
		_content += "\n";
		screen_file << _content;
	}
	screen_file.close();
}

void Stusurf::add_new_object_to_screen( int _x, int _y, int _w, int _h, std::string _name ){
	std::ofstream screen_file;
	screen_file.open( current_selected_screen, std::ofstream::out | std::ofstream::app );

	// increment the ID count.
	current_ID_count += 1;

	std::string _content = _name + " ";

	_content += Common::int_to_string( _x );
	_content += " ";
	_content += Common::int_to_string( _y );
	_content += " ";
	_content += Common::int_to_string( _w );
	_content += " ";
	_content += Common::int_to_string( _h );
	_content += " None";
	_content += " ";
	_content += Common::int_to_string( current_ID_count );
	_content += "\n";

	screen_file << _content;
	screen_file.close();

	evaluate_screen();


}


void Stusurf::mouse_move_passive( int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;

	// we will only send input to the modules when none of the
	//	main menus is open
	bool _any_m_open = false;
	for( int i = 0; i < menus_len; i++ ){
		menus[i].mouse_move_passive( _x, recalc_y );
		if( menus[i].is_shown ){
			_any_m_open = true;
		}
	}

	if( _any_m_open == false ){
		for( int i = 0; i < main_list_len; i++ ){
			main_list[i]->mouse_move_passive( _x, recalc_y );
		}
	}


	// if delet mode is triggered on.
	if( delete_mode == true ){
		int _temp_x;
		int _temp_y;
		int _temp_width;
		int _temp_height;

		// check if mouse is moved over object
		// 	if yes. Edit the bounding box vars. This will be drawn in render.
		// 	if no. Set bounding box vars to zero.
		bool hovering_over_obj = false;
		for( int i = 0; i < main_list_len; i++ ){
			_temp_x 		= ((Common::empty_module * )main_list[i])->x_full;
 			_temp_y 		= ((Common::empty_module * )main_list[i])->y_full;
		 	_temp_width 	= ((Common::empty_module * )main_list[i])->width_full;
		 	_temp_height 	= ((Common::empty_module * )main_list[i])->height_full;

			if( Common::check_inside_rect( _x, recalc_y, _temp_x, _temp_y, _temp_width, _temp_height ) ){
				hovering_over_obj = true;
				// set the bounding box positions.
				delete_bounding_box[0] = (2*(float)_temp_x/WINDOW_WIDTH) - 1 - 0.01;
				delete_bounding_box[1] = (2*(float)_temp_y/WINDOW_HEIGHT) - 1 - 0.01;
				delete_bounding_box[2] = (2*(float)_temp_width/WINDOW_WIDTH) + 0.02;
				delete_bounding_box[3] = (2*(float)_temp_height/WINDOW_HEIGHT) + 0.02;
				delete_selected_index  = i;
			}
		}

		if( hovering_over_obj == false ){
			delete_bounding_box[0] = 0;
			delete_bounding_box[1] = 0;
			delete_bounding_box[2] = 0;
			delete_bounding_box[3] = 0;
			delete_selected_index  = -1;
		}

	}

}

void Stusurf::mouse_move_active( int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;

	// if we are attempting to add an object, we will update the mouse position in order to
	//	draw a bounding box and cursor
	if( add_mode == false ){
		// we will only send input to the modules when none of the
		//	main menus is open
		bool _any_m_open = false;
		for( int i = 0; i < menus_len; i++ ){
			menus[i].mouse_move_active( _x, recalc_y );
			if( menus[i].is_shown ){
				_any_m_open = true;
			}
		}

		if( _any_m_open == false ){
			for( int i = 0; i < main_list_len; i++ ){
				main_list[i]->mouse_move_active( _x, recalc_y );
			}
		}

	}else{	// if we are attempting to add a new object to the current screen
		add_x_end = _x;
		add_y_end = recalc_y;
	}

}

void Stusurf::key_press( unsigned char _key, int _x, int _y ){
	// if opening one of the main menus:
	//	Do NOT send char to the modules
	//	toggle the menus instead.
	//	the menus define these keys.
	//	the goal is to not have too many menus in the base program
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	bool _m_open = false;
	bool any_menus_open = false;

	// if you pressed a menu start key, open a menu and ignore modules
	// if there is a menu open, redirect the keyboard input to it.
	// if no menu is open, send keyboard input to all modules on screen.
	for( int m = 0; m < menus_len; m++ ){
		if( _key == menus[m].get_shortcut()){
			_m_open = true;
			if( recalc_y < WINDOW_HEIGHT/2 ){
				menus[m].set_pos( _x, recalc_y );
			}else{
				menus[m].set_pos( _x, recalc_y - menus[m].height_full );
			}
			menus[m].toggle_show();
		}
		if( menus[m].is_shown == true ){ any_menus_open = true; break; }
	}


	if( _m_open == false && any_menus_open == false && add_new_screen_mode == false ){
		for( int i = 0; i < main_list_len; i++ ){
			main_list[i]->key_press( _key, _x, recalc_y );
		}

	}else if( add_new_screen_mode ){
		// make sure it is a printable charecter,
		// get rid of:
		//	. ; _space_ : " '
		if( _key >= 48 && _key < 125 ){
			textfield_new_screen.add( _key );

		}else if( _key == 8 ){		// backspace
			textfield_new_screen.backspace();

		}else if( _key == 13 ){		// ENTER
			add_new_screen_mode = false;
			create_new_screen( textfield_new_screen.value() );
			textfield_new_screen.clear();
		}

	}else if( _m_open == false ){
		for( int i = 0; i < menus_len; i++ ){
			menus[i].key_press( _key, _x, recalc_y );
		}
	}



	if( (int)_key == 27 ){			// escape key
		for( int i = 0; i < menus_len; i++ ){
			menus[i].is_shown = false;
		}
		// make the add new screen menu disapear
		add_new_screen_mode = false;
	}




	if( (int)_key == SHORTCUT_DELETE ){				// delete
		delete_mode = !(delete_mode);
	}
}

void Stusurf::key_release( unsigned char _key, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->key_release( _key, _x, recalc_y );
	}
}

void Stusurf::key_press_special( unsigned char _key, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->key_press_special( _key, _x, recalc_y );
	}

	// will send all the keypresses to the menus regardless of whether
	// they are shown or not. The idea is that there is not going to be
	// many menus belonging to the base, hence this is a small cost,
	// and could allow for more freedom in the future.
	for( int i = 0; i < menus_len; i++ ){
		menus[i].key_press_special( _key, _x, recalc_y );
	}

	if( (int)_key == 114 ){
		control_pressed = true;
	}
}

void Stusurf::key_release_special( unsigned char _key, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->key_release_special( _key, _x, recalc_y );
	}

	if( (int)_key == 114 ){		// CTR key
		control_pressed = false;
	}
}

/************************************************************************************************************************************/

// render function
void Stusurf::render( void ){

	// render all the objects in the main list
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if( delete_mode == true ){
		glLineWidth(100);
		glColor3f( 1.0, 0.0, 0.0 );
		// render a red border around the program and show text signifying delete mode
		glBegin( GL_LINES );
			glVertex3f( -1, -1, 0 );
			glVertex3f( -1, 1, 0 );

			glVertex3f( -1, 1, 0 );
			glVertex3f( 1, 1, 0 );

			glVertex3f( 1, 1, 0 );
			glVertex3f( 1, -1, 0 );

			glVertex3f( 1, -1, 0 );
			glVertex3f( -1, -1, 0 );
		glEnd();

		// bounding box array
		//	index:	0	1	2	3
		//	var		x	y	w	h
		glBegin( GL_LINES );
			glVertex3f( delete_bounding_box[0], delete_bounding_box[1], 0 );
			glVertex3f( delete_bounding_box[0] + delete_bounding_box[2], delete_bounding_box[1], 0 );

			glVertex3f( delete_bounding_box[0] + delete_bounding_box[2], delete_bounding_box[1], 0 );
			glVertex3f( delete_bounding_box[0] + delete_bounding_box[2], delete_bounding_box[1] + delete_bounding_box[3], 0 );

			glVertex3f( delete_bounding_box[0] + delete_bounding_box[2], delete_bounding_box[1] + delete_bounding_box[3], 0 );
			glVertex3f( delete_bounding_box[0], delete_bounding_box[1] + delete_bounding_box[3], 0 );

			glVertex3f( delete_bounding_box[0], delete_bounding_box[1] + delete_bounding_box[3], 0 );
			glVertex3f( delete_bounding_box[0], delete_bounding_box[1], 0 );
		glEnd();

		// delete mode text in top left corner
		glLineWidth(3);
		Common::render_string( -0.98, 0.93, 0.05, "DELETE MODE" );

	}

	// reset the line Width for the text
	glLineWidth(1);

	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->render();
	}

	// render the main menus for the program.
	// not a list because they are the same
	for( int i = 0; i < menus_len; i++ ){
		menus[i].render();
	}

	// render adding a new module
	if( add_mode_mouse == 3 ){
		float _bnd_x_start 	= (2*(float)add_x_start / WINDOW_WIDTH) - 1;
		float _bnd_y_start 	= (2*(float)add_y_start / WINDOW_HEIGHT) - 1;
		float _bnd_x_end	= (2*(float)add_x_end / WINDOW_WIDTH) - 1;
		float _bnd_y_end 	= (2*(float)add_y_end / WINDOW_HEIGHT) - 1;

		glColor3f( 1, 1, 1);
		glBegin( GL_QUADS );
			glVertex3f( 	_bnd_x_start, 		_bnd_y_start,	 0 );
			glVertex3f( 	_bnd_x_start, 		_bnd_y_end,		 0 );
			glVertex3f( 	_bnd_x_end, 		_bnd_y_end,		 0 );
			glVertex3f( 	_bnd_x_end, 		_bnd_y_start,	 0 );
		glEnd();
	}

	if( add_new_screen_mode ){
		textfield_new_screen.render();
	}

	// apply
	glutSwapBuffers();
}

/************************************************************************************************************************************/

// add function. I don't think we need this in template form, if we just use the base class.
void Stusurf::add( Base * _input ){
	// reallocating size in the array
	Base * * temp_list = new Base*[ main_list_len + 1 ];
	std::copy( main_list, main_list + main_list_len, temp_list );
	delete [] main_list;

	temp_list[main_list_len] = _input;
	main_list = temp_list;
	main_list_len += 1;

	std::cout << "done adding new element to main_list\n";
}

void Stusurf::add( Menu m ){
	Menu * temp = new Menu[ menus_len + 1 ];
	std::copy( menus, menus + menus_len, temp );
	delete[] menus;
	menus = temp;
	menus[ menus_len ] = m;
	menus_len += 1;
}



