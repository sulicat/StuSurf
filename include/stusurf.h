#ifndef STUSURF_H
#define STUSURF_H

#include "common.h"
#include "headers.h"

#include <iostream>

// this is the main class. It will contain all the objects we need. This is the class we will interface with in main. 
// It will deal with the other data types for us.
class Stusurf{
private:
	int   add_mode;
	int   add_mode_mouse;
	int   add_x_start;
	int   add_x_end;
	int   add_y_start;
	int   add_y_end;
	int   add_x_start_mouse;
	int   add_x_end_mouse;
	int   add_y_start_mouse;
	int   add_y_end_mouse;

public:

	std::string screens_dir_path;
	std::string current_selected_screen;

	int * width;
	int * height;

	std::string	object_to_add;

	//store a list of pointers that point to the base class.
	// This class is guaranteed to have the functions we have such as render() and the input function. This is defined in the file common.h
	Base * * main_list;
	int main_list_len;

	//Menu menu_screen_select;	// shows to help select screen
	Menu * menus;
	int menus_len;

	std::function<int(std::string)> change_selected_screen_callback;

	// constructor. Takes in the path of the file that the program will start to display from. If file does not exist it will create it. 
	Stusurf( std::string _start );

	// setting the program up
	void give_window_size( int * _w, int * _h );

	void mouse_press( int _button, int _state, int _x, int _y );
	void mouse_move_passive( int _x, int _y );
	void mouse_move_active( int _x, int _y );
	void key_press( unsigned char _key, int _x, int _y );
	void key_press_special( unsigned char _key, int _x, int _y );
	void reshape();

	void add( Base * a );
	void add( Menu _m );

	void render( void );

	void 	set_current_screen();
	void 	evaluate_screen( void );
	Base * 	create_object( std::string _type, int x, int y, int width, int height, std::string _path_data );
	int 	change_selected_screen( std::string _n );
	int 	add_object_to_screen( std::string _n );
	void 	evaluate_screen_list();
	void 	evaluate_module_list();

	void toString( void );

};


#endif
