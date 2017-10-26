#include "common.h"
#include <GL/glut.h>

TextField::TextField(){
	content = "";
	x_full 			= 0;
	y_full 			= 0;
	width_full 		= 0;
	height_full 	= 0;
	x 				= 0;
	y 				= 0;
	width 			= 0;
	height 			= 0;
	is_selected 	= false;
	title 			= "";
}

void TextField::set_pos( int _x, int _y ){
	x_full = _x;
	y_full = _y;
	reshape();
}

void TextField::set_title( std::string _t ){
	title = _t;
}

void TextField::clear(){
	content = "";
}

void TextField::toggle_selected(){
	is_selected = !(is_selected);
}

void TextField::set_selected( bool a ){
	is_selected = a;
}

void TextField::set_size( int _w, int _h ){
	width_full = _w;
	height_full = _h;
	reshape();
}

void TextField::reshape(){
	x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
	y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
	width 		= (2*(float)width_full/WINDOW_WIDTH);
	height 		= (2*(float)height_full/WINDOW_HEIGHT);
}

void TextField::add( std::string _a ){
	content += _a;
}

void TextField::add( char _a ){
	content += _a;
}

void TextField::backspace(){
	if( content.length() >= 1 )
		content = content.substr( 0, content.length() - 1 );
}

void TextField::backspace( int _b ){
	if( content.length() >= _b )
		content = content.substr( 0, content.length() - _b );
}

std::string TextField::value(){
	return content;
}

void TextField::render(){
	glColor3f( 1.0, 1.0, 1.0 );

	//	std::cout << x << " " << y << " " << width << " " << height << "\n";
	glBegin( GL_QUADS );
		glVertex3f(	x,			y, 				0 );
		glVertex3f(	x + width,	y, 				0 );
		glVertex3f(	x + width,  y + height, 	0 );
		glVertex3f(	x,			y + height, 	0 );
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(4);
	// render the border, to indicate it is selected
	if( is_selected ){
		glBegin( GL_LINES );
			glVertex3f( x, y, 0 );
			glVertex3f( x + width, y, 0 );

			glVertex3f( x + width, y, 0 );
			glVertex3f( x + width, y + height, 0 );

			glVertex3f( x + width, y + height, 0 );
			glVertex3f( x, y + height, 0 );

			glVertex3f( x, y + height, 0 );
			glVertex3f( x, y, 0 );
		glEnd();
	}
	// render contents
	Common::render_string( x, y + height * 1.05, height * 0.5, title );
	Common::render_string( x, y + height * 0.35, height * 0.5, content );

	glLineWidth(2);
}

