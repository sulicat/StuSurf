#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#include "include/stusurf.h"
#include "lib/tinyxml2.h"
#include "include/common.h"

// debug flags
#define DEBUG_INPUT_PRINT 0

// MAIN PROGRAM SETTINGS
#define FRAME_DELAY 10
#define FULLSCREEN 1


// MAIN VARIABLES
int WINDOW_WIDTH;
int WINDOW_HEIGHT;
float background_R = 0;
float background_G = 0;
float background_B = 0;

// this is the main program variable
std::string start_screen_path = "screens/";
Stusurf program = Stusurf( start_screen_path );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render( int a ){
	glutTimerFunc( FRAME_DELAY, render, 0 );
	// render the main program
	program.render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// this is the process that starts the render function.
void callback_disaplay(){
	glClear( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers();

	glutTimerFunc( FRAME_DELAY, render, 0 );
}

// this is the function that resizes the screen.
void callback_reshape( int _x, int _y ){
	WINDOW_WIDTH 	= _x;
	WINDOW_HEIGHT 	= _y;
	glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
	program.reshape();

}

void callback_mouseFunc( int _button, int _state, int _x, int _y ){
	if( DEBUG_INPUT_PRINT == 1)
		std::cout << "mouseFunc: button: " << _button << " state: " << _state << " x - y: " << _x << " - " << _y << "\n";
	program.mouse_press( _button, _state, _x, _y );
}

void callback_passiveMouseFunc( int _x, int _y ){
	if( DEBUG_INPUT_PRINT == 1 )
		std::cout << "passiveMouseFunc: x - y: " << _x << " - " << _y << "\n";
	program.mouse_move_passive( _x, _y );
}

void callback_activeMouseFunc( int _x, int _y ){
	if( DEBUG_INPUT_PRINT == 1 )
		std::cout << "activeMouseFunc: x - y: " << _x << " - " << _y << "\n";
	program.mouse_move_active( _x, _y );
}

void callback_keyboardFunc( unsigned char _key, int _x, int _y ){
	if( DEBUG_INPUT_PRINT == 1 )
		std::cout << "keyboardFunc: key: " << _key << " x - y: " << _x << " - " << _y << "\n";
	program.key_press( _key, _x, _y );
}

void callback_keyboardFunc_special( int _key, int _x, int _y ){
	if( DEBUG_INPUT_PRINT == 1 )
		std::cout << "specialKeyboardFunc: key: " << _key << " x - y: " << _x << " - " << _y << "\n";
	program.key_press_special( _key, _x, _y );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char * * argv ){

	// set the width and height to a comfortable value.
	WINDOW_WIDTH = 400;
	WINDOW_HEIGHT = 1000;

	program.give_window_size( &WINDOW_WIDTH, &WINDOW_HEIGHT );

	// this is a tempory test subjevct. We will add a bunch of objects to the main program throgh here. 
	// 	our end goal is to habe the main program read a bunch of files and populate itself.


	/*
	test_module_1 * test = new test_module_1();
	test->set_size( 190, 300 );
	test->set_pos( 200, 0 );

	test_module_2 * test2 = new test_module_2();
	test2->set_size( 150, 300 );
	test2->set_pos( 0, 0 );

	program.add( test );
	program.add( test2 );
	*/

	program.evaluate_screen();



	glutInit( &argc, argv );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "stusurf" );

	glClearColor( background_R, background_G, background_G, 1.0 );
	glutInitDisplayMode( GL_RGBA | GL_DEPTH | GL_DOUBLE );

	glutDisplayFunc( callback_disaplay );
	glutReshapeFunc( callback_reshape );
	glutMouseFunc( callback_mouseFunc );
	glutPassiveMotionFunc( callback_passiveMouseFunc );
	glutMotionFunc( callback_activeMouseFunc );
	glutKeyboardFunc( callback_keyboardFunc );
	glutSpecialFunc( callback_keyboardFunc_special );



	if( FULLSCREEN == 1 )
		glutFullScreen();

	glutMainLoop();




	return 0;

}
