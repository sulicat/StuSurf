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

}

void Stusurf::give_window_size( int * _w, int * _h ){
	width = _w;
	height = _h;
}

void Stusurf::mouse_press( int _button, int _state, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->mouse_press( _button, _state, _x, recalc_y );
	}
}

void Stusurf::mouse_move_passive( int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->mouse_move_passive( _x, recalc_y );
	}
}

void Stusurf::mouse_move_active( int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->mouse_move_active( _x, recalc_y );
	}
}

void Stusurf::key_press( unsigned char _key, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->key_press( _key, _x, recalc_y );
	}
}

void Stusurf::key_press_special( unsigned char _key, int _x, int _y ){
	int recalc_y = WINDOW_HEIGHT - _y - 1;
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->key_press_special( _key, _x, recalc_y );
	}
}

/************************************************************************************************************************************/

// render function
void Stusurf::render( void ){
	// render all the objects in the main list
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->render();
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



