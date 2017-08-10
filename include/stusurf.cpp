#include <iostream>
#include "stusurf.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <GL/glut.h>

/************************************************************************************************************************************/


// the constructor
Stusurf::Stusurf( std::string _start ){
	// set the path
	screens_dir_path = _start;
	current_selected_screen = _start + "main.txt";
	std::cout << "Loading New screen located at: " << _start << "\n";

	// start off with ana empty list of objects
	main_list = new Base*[0];
	main_list_len = 0;

	Menu menu_screen_select = Menu();
	menu_screen_select.set_number_of_items(8);
	menu_screen_select.set_height( 200 );
	menu_screen_select.set_width( 300 );
	menu_screen_select.set_shortcut( STUSURF_MENU_KEY );

	Menu menu_screen_add = Menu();
	menu_screen_add.set_number_of_items(8);
	menu_screen_add.set_height( 200 );
	menu_screen_add.set_width( 300 );
	menu_screen_add.set_shortcut( 'A' );

	add(menu_screen_select);
	add(menu_screen_add);

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



