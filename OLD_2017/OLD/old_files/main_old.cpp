#include <stdio.h>
#include <iostream>
#include "GL/glut.h"


/* written by Suleiman Barakat in March 2017
	This is a tool to help me replace paper with just the tablet. */

#define FUNCTIONALITY_TYPE_REG 			"function_reg"
#define FUNCTIONALITY_LINUX_COMMAND 	"function_linux_command"
#define BUTTON_REG 						"button_reg"


void display_callback( void );
void render( int );
void init_glut( void );
void resize_callback( int, int );
void active_mouse_move_callback( int x, int y );
bool check_inside( int x, int y, int w, int h, int x2, int y2 );


// point class....
//	stores the colors of what is displayed. Just a point in 3D space
class POINT{
public:
	float x;
	float y;
	
	float R;
	float G;
	float B;
	
	// constructors
	POINT(){
		x = 0;
		y = 0;
		R = 0;
		G = 0;
		B = 0;
	}

	POINT( float _x, float _y ){
		x = _x;
		y = _y;
		R = 0;
		G = 1;
		B = 0;
	}

	POINT( float _x, float _y, int red, int green, int blue ){
		x = _x;
		y = _y;
		R = (float)red/255;
		G = (float)green/255;
		B = (float)blue/255;
	}

	// methods
	void set_color( int red, int green, int blue ){
		R = (float)red/255;
		G = (float)green/255;
		B = (float)blue/255;	
	}

	void set_pos(float _x, float _y){
		x = _x;
		y = _y;
	}
};



// Line Class
//	Has 2 POINTs 
//	represents a line drawn in 3D space. Could be used for a variety of tools.

class LINE{
public:

	POINT point_one;
	POINT point_two;
	int width;

	void set_width( int w ){
		width = w;
	}

	LINE(){
		width = 1;
		point_one = POINT( 0, 0 );
		point_two = POINT( 0, 0 );
	}


	LINE( POINT p1, POINT p2 ){
		point_two = p1;
		point_two = p2;
	}

	LINE( int _x, int _y, int _x2, int _y2 ){
		point_one = POINT( _x, _y );
		point_two = POINT( _x2, _y2 );
	}

	void set_color( int _r, int _g, int _b ){
		point_one.set_color( _r, _g, _b );
		point_two.set_color( _r, _g, _b );
	}

	void draw(){
		glLineWidth( width );
		glBegin( GL_LINES );
			glColor3f( point_one.R, point_one.G, point_one.B );
			glVertex3f( point_one.x, point_one.y, 0.0 );
			glColor3f( point_two.R, point_two.G, point_two.B );
			glVertex3f( point_two.x, point_two.y, 0.0 );
		glEnd();
	}

};


// Functionality Class...
//	This represents an ability that a higher level object could posses. Such as running a script on press or changing the state of the program
//	Will be used with buttons and sliders for example.... can be extended and you can add custom functionality

class FUNCTIONALITY{
public:
	std::string type;
	std::string name;
	std::string command;
	int ID;

	FUNCTIONALITY(){
		type = "none";
		name = " un-named";
		command = "echo 'pressed un-named button'";
	}

	FUNCTIONALITY( std::string t ){
		if( t == FUNCTIONALITY_TYPE_REG || t == FUNCTIONALITY_LINUX_COMMAND ){

		}

	}


};




// Button Class....
//	This is one of the inputs, the higher level objects can posses a button object or multiple button objects. They can all be displayed when requested. 
//	This buttons class can be presses and would in turn posses a Functionality or multiple Functionalities depending on what is needed.

class BUTTON{
public:
	std::string type;
	std::string title;
	bool has_hover;
	bool has_left_press;
	bool has_right_press;
	bool has_middle_press;


	BUTTON(){
		has_hover = false;
		has_middle_press = false;
		has_right_press = false;
		has_left_press = false;
		type = BUTTON_REG;
	}


	BUTTON( std::string t ){
		
	}

	void render(){
		
	}

};


// DRAW_AREA class...
//	This is another type of input. It will have an array of lines that the user draws. 
//	will accept input depending on mouse location.
class DRAW_AREA{
public:
	float x;
	float y;
	float width;
	float height;

	int R;
	int G;
	int B;

	LINE * lines;
	int lines_len;

	int line_width_create;
	int line_R;
	int line_G;
	int line_B;

	float last_x;
	float last_y;

	int step_rate;
	int curren_step;

	void start_vals(){
		R = 255;
		G = 0;
		B = 0;
		curren_step = 0;
		step_rate = 3;
		lines_len = 0;
		line_width_create = 2;
		line_R = 0;
		line_G = 0;
		line_B = 0;
	}

	DRAW_AREA(){
		x = 0;
		y = 0;
		width = 100;
		height = 100;
		start_vals();
	}

	DRAW_AREA( float _x, float _y, float _width, float _height ){
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		start_vals();
	}

	void set_color( int _r, int _g, int _b ){
		R = _r;
		G = _g;
		B = _b;
	}

	void set_size( float _w, float _h ){
		width = _w;
		height = _h;
	}

	void set_pos( float _x, float _y ){
		x = _x;
		y = _y;
	}

	void set_create_line_color( int _r, int _g, int _b ){
		line_R = _r;
		line_G = _g;
		line_B = _b;
	}

	void add_line( float _x, float _y, float _x2, float _y2 ){

		// add line to array
		LINE * temp = new LINE[ lines_len + 1 ];
		std::copy( lines, lines + lines_len, temp );
		lines = temp;
		lines_len += 1;


		lines[ lines_len - 1 ] = LINE( _x, _y, _x2, _y2 );
		lines[ lines_len - 1 ].set_width( line_width_create );
		lines[ lines_len - 1 ].set_color( line_R, line_G, line_B );
		std::cout << "added line to draw area \n";

	}


	void set_create_line_width( int _lw ){
		line_width_create = _lw;
	}

	void render(){

		if( lines_len == 0 || lines_len != 0 ){
			glColor3f( (float)R/255, (float)G/255, (float)B/255 );
			glBegin( GL_QUADS );
				glVertex3f( x, y, 0.0 );
				glVertex3f( x + width, y, 0.0 );
				glVertex3f( x + width, y + height, 0.0 );
				glVertex3f( x, y + height, 0.0 );
			glEnd();
		}

		for( int i = 0; i < lines_len; i++ ){
			lines[ i ].draw();
		}

	}

	void mouse_move( int _x, int _y ){

	}

	void mouse_move_press( int _x, int _y ){
		if( curren_step == step_rate ){
			add_line( last_x, last_y, _x, _y );
			last_x = _x;
			last_y = _y;
			curren_step = 0;
		}else{
			curren_step += 1;
		}
	}

	void mouse_press( int button, int state, int _x, int _y ){
		last_x = _x;
		last_y = _y;
		std::cout << "DRAW_AREA_PRESS: button: " << button << " state: " << state << " x: " << x << " y: " << y << "\n";
	}

};


class IMAGE{
public:
	std::string name;
	int ID;
	unsigned char * texDat;
	float width;
	float height;
	float x;
	float y;
	GLuint tex;
	 

	void start_vals(){
		
		// fill in test texture
		texDat = new unsigned char[ 64 ];
	    for (int i = 0; i < 64; ++i)
      	  texDat[i] = ((i + (i / 8)) % 2) * 128 + 127;

      	// fill in PIVs
      	x = 0;
      	y = 0;
      	width = 100;
      	height = 100;

      	// texture setup 
     	glGenTextures(1, &tex);
      	glBindTexture(GL_TEXTURE_2D, tex);
	    
	}

	IMAGE(  ){
		start_vals();
		name = "un-named image";
	}

	IMAGE( std::string n ){
		start_vals();
		name = n;
	}


	void set_pos( float _x, float _y ){
		x = _x;
		y = _y;
	}

	void set_size( float _w, float _h ){
		width = _w;
		height = _h;
	}


	void draw(){
		// setup texture ..... probably should move some of it to start_vals();
		glColor3f( 1, 1, 1 );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);	    
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);

	    // drawing part. stretch texture across a quad.
	    glBegin(GL_QUADS);
	    glTexCoord2i(0, 0); glVertex2i(x, y);
	    glTexCoord2i(0, 1); glVertex2i(x, y + height);
	    glTexCoord2i(1, 1); glVertex2i(x + width, y + height);
	    glTexCoord2i(1, 0); glVertex2i(x + width, y);
	    glEnd();
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void render(){
		// setup texture ..... probably should move some of it to start_vals();
		glColor3f( 1, 1, 1 );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);	    
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);

	    // drawing part. stretch texture across a quad.
	    glBegin(GL_QUADS);
	    glTexCoord2i(0, 0); glVertex2i(x, y);
	    glTexCoord2i(0, 1); glVertex2i(x, y + height);
	    glTexCoord2i(1, 1); glVertex2i(x + width, y + height);
	    glTexCoord2i(1, 0); glVertex2i(x + width, y);
	    glEnd();
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}



};


// SCREEN class ...
//	The main display class of this program. A screen will contain a compilations of buttons, lines, sliders.... which can each have functionalities to do differnet things.
//	Screens will have a Background color that is the backfround color displayed.
//	A screen represents 1 state of the program.... for example, the login window is a Screen, then when you login, the displayed screen changes to a different one, with different buttons and sliders etc...

class SCREEN{
public:
	BUTTON * buttons;
	int buttons_len;

	DRAW_AREA * draw_areas;
	int draw_areas_len;

	IMAGE * images;
	int images_len;

	std::string title;

	int R;
	int G;
	int B;
	int ID;

	int mouse_x;
	int mouse_y;


	void start_vals(){
		R = 0;
		G = 0;
		B = 0;
		mouse_x = 0;
		mouse_y = 0;
		
		draw_areas_len = 0;
		buttons_len = 0;
		images_len = 0;
	}

	SCREEN(){
		title = "un-named screen";
		start_vals();
	}

	SCREEN( std::string t ){
		title = t;
		start_vals();
	}


	// add functions... one for every type of variable.

	void add( DRAW_AREA d ){
		DRAW_AREA * temp = new DRAW_AREA[ draw_areas_len + 1 ];
		std::copy( draw_areas, draw_areas + draw_areas_len, temp ); 
		draw_areas = temp;
		draw_areas_len += 1;

		draw_areas[ draw_areas_len - 1 ] = d;
	}

	void add( BUTTON b ){
		BUTTON * temp = new BUTTON[ buttons_len + 1 ];
		std::copy( buttons, buttons + buttons_len, temp );
		buttons = temp;
		buttons_len += 1;

		buttons[ buttons_len - 1] = b;
	}

	void add( IMAGE p ){
		IMAGE * temp = new IMAGE[ images_len + 1 ];
		std::copy( images, images + images_len, temp );
		images = temp;
		images_len += 1;

		images[ images_len - 1 ] = p;
	}



	// render function
	//	called every frame
	void render(){
		// draw areas
		for( int i = 0; i < draw_areas_len; i++ ){
			draw_areas[ i ].render();
		}

		// buttons
		for( int i = 0; i < buttons_len; i++ ){
			buttons[ i ].render();
		}

		// images
		for( int i = 0; i < images_len; i++ ){
			images[ i ].render();
		}
	}

	// update function
	void update(){

	}

	void add_buttons( BUTTON * b ){
		buttons = b;
	}

	void set_color( int red, int green, int blue ){
		R = red;
		G = green;
		B = blue;
	}

	void mouse_press( int _state, int _button, int _x, int _y ){
		for( int i = 0; i < draw_areas_len; i++ ){
			if( check_inside( draw_areas[i].x, draw_areas[i].y, draw_areas[i].width, draw_areas[i].height, _x, _y ) )
				draw_areas[i].mouse_press( _state, _button, _x, _y );	
		}
	}

	void mouse_move_press(  int _x, int _y ){
		for( int i = 0; i < draw_areas_len; i++ ){
			if( check_inside( draw_areas[i].x, draw_areas[i].y, draw_areas[i].width, draw_areas[i].height, _x, _y ) )
				draw_areas[i].mouse_move_press( _x, _y );	
		}	
		mouse_x = _x;
		mouse_y = _y;
	}

	void mouse_move( int _x, int _y ){
		for( int i = 0; i < draw_areas_len; i++ ){
			if( check_inside( draw_areas[i].x, draw_areas[i].y, draw_areas[i].width, draw_areas[i].height, _x, _y ) )
				draw_areas[i].mouse_move( _x, _y );	
		}	
		mouse_x = _x;
		mouse_y = _y;
	}

};



// Window class...
//	A final abstraction that represents a collections of screens. This is the object that all screens are added to,
//	Will keep track of which screen to use. 
// 	Will display the screens as needed and send input commands to said screen.
// 	This is the class you start the program with after initializing opengl.

class WINDOW{
public:
	std::string title;
	SCREEN * screens;
	int screens_len;
	int current_screen;

	bool is_fullscreen;

	WINDOW(){
		title = "un-named window";
		screens_len = 0;
		current_screen = 0;
		is_fullscreen = false;
	}

	WINDOW( std::string t ){
		title = t;
		screens_len = 0;
		current_screen = 0;
		is_fullscreen = false;
	}

	WINDOW( std::string t, bool f ){
		title = t;
		screens_len = 0;
		current_screen = 0;
		is_fullscreen = f;
	}

	void set_fullscreen( bool t ){
		is_fullscreen = t;
		if( t == true )
			glutFullScreen();
	}

	void add_screens(  ){
	}

	void set_current_screen( int _i ){
		current_screen = _i;
	}

	void set_current_screen( std::string _n ){
		for( int i = 0; i < screens_len; i++ ){
			if( screens[ i ].title == "n" ){
				current_screen = i;
				break;
			}
		}
	}

	void add_screen( SCREEN _s ){
		SCREEN * temp = new SCREEN[ screens_len + 1 ];
		std::copy( screens, screens + screens_len, temp );
		screens = temp;
		screens_len += 1;

		screens[ screens_len - 1 ] = _s;
		current_screen = screens_len - 1;

	}

	void mouse_press( int _button, int _state, int _x, int _y ){
		std::cout << "WINDOW --- button: " << _button << " state: " << _state << " x: " << _x << " y: " << _y  << " TOTAL SCREENS: " << screens_len << "\n";		
		screens[ current_screen ].mouse_press( _button, _state, _x, _y );
	}

	void mouse_move( int _x, int _y ){
		screens[ current_screen ].mouse_move( _x, _y );
	}

	void mouse_move_press( int _x, int _y ){
		screens[ current_screen ].mouse_move_press( _x, _y );
	}

	void render(){
		screens[ current_screen ].render();	
	}


};









// GLOBALS
WINDOW window;

int window_width = 1200;
int window_height = 1000;
int frame_delay = 10;
float background_R = 0.0;
float background_G = 0.0;
float background_B = 0.0;
int step_rate = 1;

float last_x = 0;
float last_y = 0;
int current_step = 0;



// FUNCTIONS
void init_glut( void ){
	glClearColor( background_R, background_G, background_G, 1.0 );
	glViewport( 0.0, 0.0, window_width, window_height );
	glutInitDisplayMode(GLUT_RGBA);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	glOrtho( 0.0, window_width, window_height, 0.0, 1.0, -1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}




// TEST FUNCTION
/* 
void add_line( float _x, float _y, float _x2, float _y2 ){
		LINE * temp = new LINE[ lines_len + 1 ];
		std::copy( lines, lines + lines_len, temp );
		lines = temp;
		lines_len += 1;
		lines[ lines_len - 1 ] = LINE( _x, _y, _x2, _y2 );
}
*/


// funciton to help check for collisions.
bool check_inside( int x, int y, int w, int h, int x2, int y2 ){
	if( x < x2 && x + w > x2 && y < y2 && y + h > y2 ){
		return true;
	}return false;
}


// callbacks
void mouse_press_callback( int button, int state, int x, int y){
	window.mouse_press( button, state, x, y );

}

void resize_callback( int x, int y ){
	window_width = x;
	window_height = y;
	init_glut();
}


void active_mouse_move_callback( int x, int y ){
	window.mouse_move_press( x, y );
}


void display_callback( void ){
	glClearColor( background_R, background_G, background_G, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT );

	if( window.is_fullscreen == true ){
		glutFullScreen();
	}

	glutSwapBuffers();	
	glutTimerFunc( frame_delay, render, 0  );
}




void render( int a ){
	glutSwapBuffers();
	glutTimerFunc( frame_delay, render, 0  );
	window.render();
}



int main( int argc, char * * argv ){
	glutInit( &argc, argv );
	glutInitWindowSize( window_width, window_height );
	glutInitWindowPosition( 0, 0 );
	glutInitDisplayMode( GLUT_DOUBLE );
	glutCreateWindow( "StuSurf" );

	init_glut( );	
	glutDisplayFunc( display_callback );
	glutReshapeFunc( resize_callback );	
	glutMotionFunc( active_mouse_move_callback );
	glutMouseFunc( mouse_press_callback );

	window.set_fullscreen( true );
		
	DRAW_AREA a = DRAW_AREA();
	a.set_color( 0, 255, 255 );
	a.set_size( 500, 300 );
	a.set_create_line_width( 10 );

	DRAW_AREA b = DRAW_AREA();
	b.set_color( 255, 255, 255 );
	b.set_size( 900, 600 );
	b.set_pos( 500, 300 );

	IMAGE img1 = IMAGE( "image 1" );
	img1.set_size( 400,400 );

	IMAGE img2 = IMAGE( "image 2" );
	img2.set_size( 400, 400 );
	img2.set_pos( 500, 500 );


	SCREEN s1 = SCREEN("hello world");
	s1.add( a );
	s1.add( b );
	s1.add( img1 );
	s1.add( img2 );


	window.add_screen( s1 );
	

	glutMainLoop();

	return 0;

}
