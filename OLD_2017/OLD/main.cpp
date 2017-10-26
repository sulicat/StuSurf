#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GL/glut.h"
#include "GL/glu.h"	

#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"

float window_width = 1200;
float window_height  = 1000;
int frame_delay = 10;
float background_R = 0.0;
float background_G = 0.0;
float background_B = 0.0;
int step_rate = 1;



#define DEBUG_PRINT 				0
#define FRAME_DELAY 				20

#define KEYBIND_MAIN_MENU			116



class SCREEN{
public:

	SCREEN(){

	}


	void render(){

	}

};






class PROGRAM{
public:

	SCREEN screen;

	char * file_main_path;
	char * file_screen_path;


	PROGRAM(){
		screen = SCREEN();
	}

	PROGRAM( char * _path ){

	}


	void render(){
		screen.render();
		glutSwapBuffers();
	}



	void mouse_press( int _button, int _state, int _x, int _y ){
		if( DEBUG_PRINT )
			std::cout << "MOUSEPRESS: button: " << _button << " state: " << _state << " x:" << _x << " y:" << _y << "\n"; 
	}

	void mouse_move_passive( int _x, int _y ){
		if( DEBUG_PRINT )
			std::cout << "PASSIVE:  "  << " x:" << _x << " y:" << _y << "\n";	
	}

	void mouse_move_active( int _x, int _y ){
		if( DEBUG_PRINT )
			std::cout << "ACTIVE:  "  << " x:" << _x << " y:" << _y << "\n";	
	}

	void key_press( unsigned char _key, int _x, int _y ){
		if( DEBUG_PRINT )
			std::cout << "KEYPRESS: key: " << _key << " x:" << _x << " y:" << _y << "\n";
	}

	void key_press_special( int _key, int _x, int _y ){
			std::cout << "KEYPRESS: key: " << _key << " x:" << _x << " y:" << _y << "\n";
	}

};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PROGRAM program = PROGRAM();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



/* this is the init function
	- we will first swet the clear color. 
	- then we set the viewport to fit the screen width and height that we have.
	- set the display mode
	- set change to projection matrix, reset and then use GL ortho to use orthographic view.
*/
void init_glut(){

	glClearColor( background_R, background_G, background_G, 1.0 );
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	glEnable( GL_DEPTH_TEST );

	glViewport( 0.0, 0.0, window_width, window_height );
	gluPerspective( 45.0f, window_width * (1.0 / window_height), 0.1f, 100.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


// render function. This will render the main object which will handle all the other renders.
void render( int a ){
	program.render();
	glutTimerFunc( FRAME_DELAY, render, 0 );
}


// this is the process that starts the render function.
void callback_disaplay(){
	glClear( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers();

	glutTimerFunc( FRAME_DELAY, render, 0 );
}

// this is the function that resizes the screen.

void callback_reshape( int _x, int _y ){
	window_width 	= _x;
	window_height 	= _y;
	init_glut();
}

void callback_mouseFunc( int _button, int _state, int _x, int _y ){
	program.mouse_press( _button, _state, _x, _y );
}

void callback_passiveMouseFunc( int _x, int _y ){
	program.mouse_move_passive( _x, _y );
}

void callback_activeMouseFunc( int _x, int _y ){
	program.mouse_move_active( _x, _y );
}

void callback_keyboardFunc( unsigned char _key, int _x, int _y ){
	program.key_press( _key, _x, _y );
}

void callback_keyboardFunc_special( int _key, int _x, int _y ){
	program.key_press_special( _key, _x, _y );
}










//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main( int argc, char * * argv ){
	
	if( DEBUG_PRINT ){
		std::cout << "starting the program \n";
	}



	glutInit( &argc, argv );
	glutInitWindowSize( window_width, window_height );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "stusurf" );
	glutFullScreen();

	glutMouseFunc( callback_mouseFunc );
	glutPassiveMotionFunc( callback_passiveMouseFunc );
	glutMotionFunc( callback_activeMouseFunc );
	glutKeyboardFunc( callback_keyboardFunc );
	glutSpecialFunc( callback_keyboardFunc_special );

	glutDisplayFunc( callback_disaplay );
	

	
	

	init_glut();


	glutMainLoop();



	return 0;
}