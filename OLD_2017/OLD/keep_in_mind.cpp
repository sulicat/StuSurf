#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GL/glut.h"
#include "GL/glu.h"	



#define DEBUG_PRINT 		1
#define FRAME_DELAY 		20




/* 
 
  Goals of this program:
	We want to make it simple, It does't have to be all encompassing. 
	- there will be a main screen. Simply a startup screen save. 
	- At any point in the program you can hit a key to open the main menu.
	- This menu will have links to all other parts of the program as well as commands to do certain things. 
	- Every part of the program has its own shortcuts defined within that class. It will recognize that input and act accordingly. 


*/

float window_width = 1200;
float window_height  = 1000;
int frame_delay = 10;
float background_R = 0.0;
float background_G = 0.0;
float background_B = 0.0;
int step_rate = 1;

float last_x = 0;
float last_y = 0;
int current_step = 0;



float angle = 0.0;


class SCREEN{
public:
	SCREEN(){

	}



	void render(){
		
		

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		gluLookAt( 	0.0f, 0.0f, 10.0f,
					0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.2f	 );


		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
		glTranslatef(3,0,0);


		glBegin( GL_QUADS );

			glColor3f( 1.0, 0.0, 0.0 );
			// z = 0
			glVertex3f(		0.0f,	0.0f, 	0.0f );
			glVertex3f(		1.0f,	0.0f, 	0.0f );
			glVertex3f(		1.0f,	1.0f, 	0.0f );
			glVertex3f(		0.0f,	1.0f, 	0.0f );

			glColor3f( 0.0, 1.0, 0.0 );
			// z = 1
			glVertex3f(		0.0f,	0.0f, 	1.0f );
			glVertex3f(		1.0f,	0.0f, 	1.0f );
			glVertex3f(		1.0f,	1.0f, 	1.0f );
			glVertex3f(		0.0f,	1.0f, 	1.0f );

		glEnd();


		glPopMatrix();

		glPushMatrix();
		glTranslatef(-3,0,0);
		glRotatef(2 * angle, 0.0, 1.0, 0.0);

		glBegin( GL_QUADS );

			glColor3f( 1.0, 0.0, 0.0 );
			// z = 0
			glVertex3f(		0.0f,	0.0f, 	0.0f );
			glVertex3f(		1.0f,	0.0f, 	0.0f );
			glVertex3f(		1.0f,	1.0f, 	0.0f );
			glVertex3f(		0.0f,	1.0f, 	0.0f );

			glColor3f( 0.0, 1.0, 0.0 );
			// z = 1
			glVertex3f(		0.0f,	0.0f, 	1.0f );
			glVertex3f(		1.0f,	0.0f, 	1.0f );
			glVertex3f(		1.0f,	1.0f, 	1.0f );
			glVertex3f(		0.0f,	1.0f, 	1.0f );

		glEnd();

		glPopMatrix();

		angle += 1;

		glutSwapBuffers();


	}

};


	




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class PROGRAM{
public:

	SCREEN * screens;
	int screens_len;

	int current_screen_i;


	PROGRAM(){
		screens = new SCREEN[0];
		screens_len = 0;
		current_screen_i = -1;
	}


	void render(){

		if( screens_len > 0 ){
			screens[current_screen_i].render();
		}
		
		glutSwapBuffers();

	}


};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PROGRAM program = PROGRAM();
SCREEN screen_1 = SCREEN();
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
	//program.render();
	screen_1.render();

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

	glutDisplayFunc( callback_disaplay );


	init_glut();







	glutMainLoop();




	return 0;

}