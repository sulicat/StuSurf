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

	// this is the screen select menu, it will
	Menu menu_screen_select = Menu();
	menu_screen_select.set_number_of_items(8);
	menu_screen_select.set_height( 200 );
	menu_screen_select.set_width( 300 );
	menu_screen_select.set_shortcut( 'S' );
	menu_screen_select.set_name( "Screens" );

	// this is the add menu, it will add new modules to the current screen
	Menu menu_screen_add = Menu();
	menu_screen_add.set_number_of_items(8);
	menu_screen_add.set_height( 200 );
	menu_screen_add.set_width( 300 );
	menu_screen_add.set_shortcut( 'A' );
	menu_screen_add.set_name( "Add" );

	// adding the menus to a list of menus. Makes sending input and rendering
	//	simpler
	add(menu_screen_select);
	add(menu_screen_add);

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
}


int temp( std::string a ){
	std::cout << a << "\n";
	return 1;
}

void Stusurf::evaluate_screen_list(){
	// read the file with all the screen names. Create menu items with these names
	char _line[256];
	std::string _line_string;
	std::ifstream screen_list;
	screen_list.open( "include/screen_list", std::ifstream::in );

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
		menus[1].add( _line_string, [this](std::string _a){return this->add_object_to_screen(_a);}, _line_string );
		std::cout << "... ... " << _line_string << "\n";
	}

	std::cout << "... ... ... DONE evaluating modules\n";
	module_list.close();
}

int Stusurf::add_object_to_screen( std::string _n ){
	object_to_add = _n;
	add_mode = 1;
	add_mode_mouse = 1;
	add_x_start = 0;
	add_y_start = 0;
	add_x_end 	= 0;
	add_y_end	= 0;
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

	}else if( _state == 1 && add_mode_mouse == 3 ){
		add_x_end = _x;
		add_y_end = recalc_y;
		add_mode_mouse = 0;
	}

	// enter key add handling
	/*	 if( _state == 0 && add_mode == 1 ){
		add_x_start = _x;
		add_y_start = recalc_y;
		add_x_end = _x;
		add_y_end = recalc_y;

	}else if( _state == 1 && add_mode == 1 ){
		add_x_end = _x;
		add_y_end = recalc_y;
		add_mode = 0;
		}*/

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
		if( _key == menus[m].get_shortcut() ){
			_m_open = true;
			if( recalc_y < WINDOW_HEIGHT/2 ){
				menus[m].set_pos( _x, recalc_y );
			}else{
				menus[m].set_pos( _x, recalc_y - menus[m].height_full );
			}
			menus[m].toggle_show();
		}
		if( menus[m].is_shown == true ){ any_menus_open = true; }
	}

	if( _m_open == false && any_menus_open == false ){
		for( int i = 0; i < main_list_len; i++ ){
			main_list[i]->key_press( _key, _x, recalc_y );
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
}

/************************************************************************************************************************************/

// render function
void Stusurf::render( void ){
	// render all the objects in the main list
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->render();
	}

	// render the main menus for the program.
	// not a list because they are the same
	for( int i = 0; i < menus_len; i++ ){
		menus[i].render();
	}

	// render adding a new module
	if( add_mode != 0 && add_mode_mouse != 0 ){

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

		//		std::cout << _bnd_x_start << " " << _bnd_y_start << "\n";
		//		std::cout << _bnd_x_end << " " << _bnd_y_end << "\n\n";

	}
	std::cout <<"reg: " <<  add_mode << " mouse: " << add_mode_mouse << "\n";

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



