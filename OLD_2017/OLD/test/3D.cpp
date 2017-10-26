#include "GL/glut.h"










void render( int a ){
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	gluLookAt( 	0.0, 0.0, 0.0,
				0.0, 0.0, 0.0,
				0.0, 1.0, 0.0 	 );

	glRotatef( 0, 0.0, 1.0, 0.0 );

	glBegin( GL_TRIANGLES );
		glVertex3f( -2.0, -2.0, 0.0 );
		glVertex3f( 2.0, 0.0, 0.0 );
		glVertex3f( 0.0, 2.0, 0.0 );
	glEnd();

	glutSwapBuffers();

	glutTimerFunc( 10, render, 0 );

}



void display(){

	glutTimerFunc( 10, render, 0 );

}

int main( int argc, char * * argv ){

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 1000, 1000 );

	glutCreateWindow( "test_3D" );

	glutDisplayFunc( display );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glViewport( 0, 0, 1000, 1000 );
	gluPerspective( 45, 1, 0.1, 1000 );

	glMatrixMode( GL_MODELVIEW );

	glutMainLoop();


	
	return 0;

}