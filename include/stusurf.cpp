#include <iostream>
#include "stusurf.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <GL/glut.h>

/************************************************************************************************************************************/

// the constructor
STUSURF::STUSURF( char * _start ){
	// set the path
	path_start_screen = _start;
	std::cout << "Loading New screen located at: " << _start << "\n";
	
	// start off with ana empty list of objects
	main_list = new Base*[0];
	main_list_len = 0;
	
}

/************************************************************************************************************************************/
// this is the test print function
void STUSURF::toString( void ){
	std::cout << path_start_screen << "\n";
}

void STUSURF::give_window_size( int * _w, int * _h ){
	width = _w;
	height = _h;
}

void STUSURF::mouse_press( int _button, int _state, int _x, int _y ){
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->mouse_press( _button, _state, _x, _y );
	}
}

void STUSURF::mouse_move_passive( int _x, int _y ){
	//std::cout << "mouse move: " << _x << " " << _y << "\n";
}

void STUSURF::mouse_move_active( int _x, int _y ){
	//std::cout << "mouse move ACTIVE: " << _x << " " << _y << "\n";
}

void STUSURF::key_press( unsigned char _key, int _x, int _y ){
	//std::cout << "keypress: k x y " << _key << " " << _x << " " << _y << "\n";
}

void STUSURF::key_press_special( unsigned char _key, int _x, int _y ){
	//std::cout << "keypress SPECIAL: k x y " << _key << " " << _x << " " << _y << "\n";
}

/************************************************************************************************************************************/

// render function
void STUSURF::render( void ){
	// render all the objects in the main list
	for( int i = 0; i < main_list_len; i++ ){
		main_list[i]->render();
	}

	glutSwapBuffers();

}

/************************************************************************************************************************************/

// add function. I don't think we need this in template form, if we just use the base class.
void STUSURF::add( Base * _input ){
	// reallocating size in the array
	Base * * temp_list = new Base*[ main_list_len + 1 ];
	std::copy( main_list, main_list + main_list_len, temp_list );
	delete [] main_list;

	temp_list[main_list_len] = _input;
	main_list = temp_list;
	main_list_len += 1;

	std::cout << "done adding new element to main_list\n";
}


