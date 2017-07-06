#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#define MAX_LINE_READ_SIZE 100
#define FRAME_DELAY 10
#define FULLSCREEN 1


// this is the MAIN for stusurf. Opengl will be initialized here and the main classes will be defines. 

int WINDOW_WIDTH;
int WINDOW_HEIGHT;
float background_R = 0;
float background_G = 0;
float background_B = 0;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void render( int a ){

	std::cout << WINDOW_WIDTH << " " << WINDOW_HEIGHT << "\n";

	glutTimerFunc( FRAME_DELAY, render, 0 );
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
}

void callback_mouseFunc( int _button, int _state, int _x, int _y ){
	std::cout << "mouseFunc: button: " << _button << " state: " << _state << " x - y: " << _x << " - " << _y << "\n";
}

void callback_passiveMouseFunc( int _x, int _y ){
	std::cout << "passiveMouseFunc: x - y: " << _x << " - " << _y << "\n"; 
}

void callback_activeMouseFunc( int _x, int _y ){
	std::cout << "activeMouseFunc: x - y: " << _x << " - " << _y << "\n"; 
}

void callback_keyboardFunc( unsigned char _key, int _x, int _y ){
	std::cout << "keyboardFunc: key: " << _key << " x - y: " << _x << " - " << _y << "\n";
}

void callback_keyboardFunc_special( int _key, int _x, int _y ){
	std::cout << "specialKeyboardFunc: key: " << _key << " x - y: " << _x << " - " << _y << "\n";
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char * * argv ){

	// set the width and height to a comfortable value.
	WINDOW_WIDTH = 1200;
	WINDOW_HEIGHT = 1000;


	glutInit( &argc, argv );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "stusurf" );

	glClearColor( background_R, background_G, background_G, 1.0 );
	glutInitDisplayMode( GL_RGBA | GL_DEPTH | GL_DOUBLE );

	glutDisplayFunc( callback_disaplay );
	glutReshapeFunc( callback_reshape );


	if( FULLSCREEN == 1 )
		glutFullScreen();

	glutMainLoop();




	return 0;

}