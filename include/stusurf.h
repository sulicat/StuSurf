#ifndef STUSURF_H
#define STUSURF_H

#include "common.h"

// this is the main class. It will contain all the objects we need. This is the class we will interface with in main. 
// It will deal with the other data types for us.
class STUSURF{
public:
	char * path_start_screen;
	FILE * file_start_screen;

	int * width;
	int * height;

	//store a list of pointers that point to the base class. 
	// This class is guaranteed to have the functions we have such as render() and the input function. This is defined in the file common.h
	Base * * main_list;
	int main_list_len;

	// constructor. Takes in the path of the file that the program will start to display from. If file does not exist it will create it. 
	STUSURF( char * _start );

	// setting the program up
	void give_window_size( int * _w, int * _h );

	void mouse_press( int _button, int _state, int _x, int _y );
	void mouse_move_passive( int _x, int _y );
	void mouse_move_active( int _x, int _y );
	void key_press( unsigned char _key, int _x, int _y );
	void key_press_special( unsigned char _key, int _x, int _y );

	void add( Test t );

	void render( void );

	void toString( void );

};


#endif