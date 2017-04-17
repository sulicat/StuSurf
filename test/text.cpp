// this is a script that tests our text class.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <GL/glut.h>


#define IMAGE_TYPE_RGB 24
#define IMAGE_TYPE_RGBA 32
#define IMAGE_TYPE_GREYSCALE 2

struct IMAGE_INFO{
	int start;
	int end;
	char * name;
	int value;


	IMAGE_INFO( ){
		start = 0;
		end = 0;
		name = NULL;
		value = 0;
	}	

	IMAGE_INFO( int s, int e, char * n, int val ){
		start = s;
		end = e;
		name = ( char * )n;
		value = val;
	}
};









class IMAGE{
public:
	int x;
	int y;
	int width;
	int height; 
	int pixel_offset;
	int image_width;
	int image_height;
	int compression;
	int image_size;
	int bits_per_pixel;
	char * image_path;
	size_t size;

	unsigned char * texDat;
	GLuint tex;
	int type;

	IMAGE_INFO * other_data;
	int other_data_len;

	void setup_other_data(){
		
		IMAGE_INFO other_data_temp[] = { 	IMAGE_INFO( 0,   2, 		(char*) "signature",   				-9999 ),	//0
											IMAGE_INFO( 2,   6, 		(char*) "file size",   				-9999 ),	//1
											IMAGE_INFO( 6,   10, 		(char*) "reserved",   				-9999 ),	//2
											IMAGE_INFO( 10,  14, 		(char*) "offset to array", 			-9999 ),	//3
											IMAGE_INFO( 14,  18, 		(char*) "dip_header",  				-9999 ),	//4
											IMAGE_INFO( 18,  22, 		(char*) "width",	    			-9999 ),	//5
											IMAGE_INFO( 22,  26, 		(char*) "height", 	   				-9999 ),
											IMAGE_INFO( 26,  28, 		(char*) "planes", 	   				-9999 ),
											IMAGE_INFO( 28,  30, 		(char*) "bits per pixel", 	   		-9999 ),
											IMAGE_INFO( 30,  34, 		(char*) "compression",	 	   		-9999 ),	
											IMAGE_INFO( 34,  38, 		(char*) "image size",	 	   		-9999 ),	//10
											IMAGE_INFO( 38,  42,	 	(char*) "X pixels per meter",  		-9999 ),
											IMAGE_INFO( 42,  46, 		(char*) "Y pixels per meter", 		-9999 ),
											IMAGE_INFO( 46,  50, 		(char*) "Colors in color table", 	-9999 ),
											IMAGE_INFO( 50,  54, 		(char*) "Important Color Count", 	-9999 ),
											IMAGE_INFO( 54,  58, 		(char*) "red chanel bitmask", 		-9999 ),	//15
											IMAGE_INFO( 58,  62, 		(char*) "blue chanel bitmask", 		-9999 ),
											IMAGE_INFO( 62,  66, 		(char*) "green chanel bitmask", 	-9999 ),
											IMAGE_INFO( 66,  70, 		(char*) "alpha chanel bitmask",		-9999 ),
											IMAGE_INFO( 70,  74, 		(char*) "color space type", 		-9999 ),
											IMAGE_INFO( 74,  78, 		(char*) "color space enpoints",		-9999 ),	//20
											IMAGE_INFO( 78,  82, 		(char*) "gamma for red chanel", 	-9999 ),
											IMAGE_INFO( 82,  86, 		(char*) "gamma for green chanel", 	-9999 ),
											IMAGE_INFO( 86,  90, 		(char*) "gamma for blue chanel", 	-9999 ),
											IMAGE_INFO( 90,  94, 		(char*) "intent",				 	-9999 ),
											IMAGE_INFO( 94,  98, 		(char*) "ICC profile data",	 		-9999 ),	//25
											IMAGE_INFO( 98,  102, 		(char*) "ICC profile size", 		-9999 ),
											IMAGE_INFO( 102, 104, 		(char*) "reserved", 				-9999 )
									};

		other_data = other_data_temp;							
		type = IMAGE_TYPE_RGB;
		other_data_len = 27;
		other_data = new IMAGE_INFO[ other_data_len ];

		std::copy( other_data_temp, other_data_temp + other_data_len, other_data );

		x = 0;
		y = 0;
		width = 100;
		height = 100;

	}

	// no path... cannot load image until there is path.
	IMAGE(){
		image_path = NULL;
		setup_other_data();
	}

	// create image with a path
	IMAGE( char * p ){
		image_path = p;
		setup_other_data(); 	
	}

	// set the path.
	void set_path( char * p ){
		image_path = p;
	}

	void set_type( int t ){
		type = t;
	}

	void set_pos( int _x, int _y ){
		x = _x;
		y = _y;
	}

	void set_size( int _w, int _h ){
		width = _w;
		height = _h;
	}

	// will load all the data into this image object so that they can later be used.
	//	first read the file and store all the relevant information into the other data array
	//	then it will attampt to load 
	void load(){
		// check if the path exists
		if( image_path != NULL ){
			std::ifstream f;

			// open file
			f.open( image_path, std::ios::in | std::ios::binary  );
			char * file = 0;

			// find the end and size of the file
			f.seekg( 0, std::ios::end );
			size = f.tellg();
			std::cout << "size: " << size << "\n";
			f.seekg( 0, std::ios::beg );

			// read the file and store it in a char array
			file = new char[ size + 1 ];
			f.read( file, size );
			file[ size ] = '\0';
		

			// load the contents into "other_data"
			//int * temp = new int[1];
			unsigned char * temp = new unsigned char[4];
			for( int i = 0; i < size; i++ ){
				for( int c = 0; c < other_data_len; c++ ){

					if( i == other_data[ c ].start ){
						std::copy( file + other_data[c].start, file + other_data[c].end, temp );
						other_data[c].value = *(temp+3) << 24 | *(temp+2) << 16 | *(temp+1) << 8 | *temp;
						
						std::cout << std::dec << other_data[c].name << " : " << other_data[c].value << "\n";
						i = other_data[ c ].end-1;
					}
				}
			}


			
			pixel_offset 	= (unsigned int) (other_data[ 3 ].value);
			std::cout << "pixel_offset: " << pixel_offset << "\n";

			image_width 	= (unsigned int) (other_data[ 5 ].value);
			std::cout << "width: " << image_width << "\n";
				
			image_height 	= (unsigned int) (other_data[ 6 ].value);
			std::cout << "height: " << image_height << "\n";

			bits_per_pixel 	= (unsigned int) (other_data[ 8 ].value);
			std::cout << "bpp: " << bits_per_pixel << "\n";

			unsigned char * image_data;
			texDat = new unsigned char[ image_width * image_height * 3 ];



			if( bits_per_pixel == 24 ){ 
				texDat = new unsigned char[ image_width * image_height * 3 ];
				image_data = new unsigned char[ image_width * image_height * 3 ];

				for( int i = 0; i < (image_width * image_height * 3); i++ ){

					image_data[ i ] 	= 	(unsigned char)file[ pixel_offset + i + 2 ] ;		// R
					image_data[ i+1 ] 	= 	(unsigned char)file[ pixel_offset + i + 1] ;		// G
					image_data[ i+2 ] 	= 	(unsigned char)file[ pixel_offset + i ] ;			// B
									
					i += 2;
				}

				glEnable(GL_BLEND);
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat); 



			}else if( bits_per_pixel == 32 ){
				texDat = new unsigned char[ image_width * image_height * 4 ];
				image_data = new unsigned char[ image_width * image_height * 4 ];

				for( int i = 0; i < (image_width * image_height * 4); i++ ){					
					
					image_data[ i ] 	= 	(unsigned char)file[ pixel_offset + i + 3 ] ;		// R
					image_data[ i+1 ] 	= 	(unsigned char)file[ pixel_offset + i + 2 ] ;		// G
					image_data[ i+2 ] 	= 	(unsigned char)file[ pixel_offset + i + 1 ] ;		// B
					image_data[ i+3 ] 	= 	(unsigned char)file[ pixel_offset + i  ] ;			// A
									
					i += 3;
				}

				glEnable(GL_BLEND);
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat);

			}else{



			}

			texDat = image_data;

		    glBindTexture(GL_TEXTURE_2D, 0);
		    glEnable(GL_TEXTURE_2D);
	  




		}else{
			std::cout << "there is no file path specified for IMAGE object, could not load \n";
		}




	}


	void draw_setup(){
		if( bits_per_pixel == 24 ){

			glBindTexture(GL_TEXTURE_2D, tex);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat); 
		    glBindTexture(GL_TEXTURE_2D, 0);

		    glBindTexture(GL_TEXTURE_2D, tex);

		}else if( bits_per_pixel == 32 ){
			glBindTexture(GL_TEXTURE_2D, tex);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texDat); 
		    glBindTexture(GL_TEXTURE_2D, 0);

		    glBindTexture(GL_TEXTURE_2D, tex);

		}
	}


	void draw(){

		draw_setup();


		glColor3f(1,1,1);
	    glBegin(GL_QUADS);
	    	glTexCoord2i(0, 0); glVertex2i(x, y);
	    	glTexCoord2i(0, 1); glVertex2i(x, y + height);
		    glTexCoord2i(1, 1); glVertex2i(x + width, y + height);
		    glTexCoord2i(1, 0); glVertex2i(x + width, y);
	    glEnd();

	}


	// draw a part of the image at the current x and y pos
	void partial_draw_pixel( int crop_w_start, int crop_w_end, int crop_h_start, int crop_h_end ){
		
		draw_setup();


		float zero_x = (float)crop_w_start/image_width;
		float zero_y = (float)crop_h_start/image_height;

		float one_x = (float)crop_w_end/image_width;
		float one_y = (float)crop_h_end/image_height;

		// draw a part of the image
		glColor3f(1,1,1);
	    glBegin(GL_QUADS);
	    	glTexCoord2f(zero_x, zero_y); 			glVertex2i(x, y);
	    	glTexCoord2f(zero_x, one_y); 			glVertex2i(x, y + height);
		    glTexCoord2f(one_x, one_x); 			glVertex2i(x + width, y + height);
		    glTexCoord2f(one_x, zero_y); 			glVertex2i(x + width, y);
	    glEnd();


	}


	// draw a part of the image at the current x and y pos
	void partial_draw_image( int crop_w_start, int crop_w_end, int crop_h_start, int crop_h_end ){
		
		draw_setup();

		float zero_x = (float)crop_w_start/width;
		float zero_y = (float)crop_h_start/height;

		float one_x = (float)crop_w_end/width;
		float one_y = (float)crop_h_end/height;

		// draw a part of the image
		glColor3f(1,1,1);
	    glBegin(GL_QUADS);
	    	glTexCoord2f(zero_x, zero_y); 			glVertex2i(x, y);
	    	glTexCoord2f(zero_x, one_y); 			glVertex2i(x, y + height);
		    glTexCoord2f(one_x, one_x); 			glVertex2i(x + width, y + height);
		    glTexCoord2f(one_x, zero_y); 			glVertex2i(x + width, y);
	    glEnd();

	}



	// 	the main partial draw function.
	//	to use:
	//		partial_draw_pixel_resize( crop_start_x, crop_start_y, crop_end_x, crop_y_end, pos_x, pos_y, width, height )
	void partial_draw_pixel_resize( int crop_x_start, int crop_y_start, int crop_x_end, int crop_y_end, int _x, int _y, int _w, int _h ){
		draw_setup();

		float zero_x = (float)crop_x_start/image_width;
		float zero_y = (float)crop_y_start/image_height;

		float one_x = ((float)crop_x_end/image_width);
		float one_y = ((float)crop_y_end/image_height);		


		glColor3f(1,1,1);
	    glBegin(GL_QUADS);
	    	glTexCoord2f( zero_x, 	zero_y); 			glVertex2i( _x,		 	_y );
	    	glTexCoord2f( zero_x, 	one_y); 			glVertex2i( _x, 	 	_y + _h );
		    glTexCoord2f( one_x, 	one_y); 			glVertex2i( _x + _w, 	_y + _h);
		    glTexCoord2f( one_x, 	zero_y); 			glVertex2i( _x + _w,  	_y);
	    glEnd();
	}


};





class FONT{
public:
	IMAGE font_map_lower;
	IMAGE font_map_upper;

	int start_x;			// stores the pixel count start x
	int start_y;			// stores the pixel count start Y
	int letter_width;		// stores the width of every letter in pixels
	int letter_height;		// stores the height of every letter in pixels

	int * lower_map;		// an array with all ascii values as they map to image (lower_case)
	int lower_map_len;
	int * upper_map;		// an array with all ascii values as they map to image (upper_case)
	int upper_map_len;

	int rows;
	int columns;

	FONT(){
		start_x = 0;
		start_y = 0;

		lower_map = new int[ 0 ];
		lower_map_len = 0;

		upper_map = new int[ 0 ];
		upper_map_len = 0;
	
		rows = 0;
		columns = 0;
	}


	// set the amount of rows and columns in order to seperate
	FONT( int _r, int _c ){
		rows = _r;
		columns = _c;
	}





	void load( char * lower_p, char * upper_p ){
		font_map_lower = IMAGE( lower_p );
		font_map_upper = IMAGE( upper_p );

		font_map_lower.load();
		font_map_upper.load();

		int size = rows * columns;

		lower_map = new int[ size ];
		upper_map = new int[ size ];
		lower_map_len = size;
		upper_map_len = size;

		for( int i = 0; i < rows*columns; i++ ){
			lower_map[i] = 0;
			upper_map[i] = 0;
		}

	 	letter_width = font_map_lower.image_width / columns;
	 	letter_height = font_map_lower.image_height / rows;

	}

	void set_param_start( int _x, int _y ){
		start_y = _y;
		start_x = _x;
	}

	void set_param_size( int _w, int _h ){
		letter_width = _w;
		letter_height = _h;
	}

	void map_lower( int _pos, int _ascii ){
		if( _pos < columns * rows ){
			lower_map[ _pos ] = _ascii;

			for( int i = _pos; i < columns*rows; i++ ){
				lower_map[ i ] = _ascii + i - _pos;
			}
		}
	}

	void map_lower( int _pos, int _ascii, int ascii_end ){
		if( _pos < columns * rows ){
			lower_map[ _pos ] = _ascii;

			for( int i = _pos; _ascii + i - _pos < ascii_end; i++ ){
				lower_map[ i ] = _ascii + i - _pos;
			}
		}
	}

	void map_upper( int _pos, int _ascii ){
		if( _pos < columns * rows ){
			upper_map[ _pos ] = _ascii;

			for( int i = _pos; i < columns*rows; i++ ){
				upper_map[ i ] = _ascii + i - _pos;
			}
		}
	}

	void map_upper( int _pos, int _ascii, int ascii_end ){
		if( _pos < columns * rows ){
			upper_map[ _pos ] = _ascii;

			for( int i = _pos; _ascii + i - _pos < ascii_end; i++ ){
				upper_map[ i ] = _ascii + i - _pos;
			}
		}
	}


	int pos_from_RC( int _r, int _c ){
		return 0;
	}


	void draw_letter( int _x, int _y, int _w, int _h, char _letter ){
		/*for( int i = 0; i < lower_map_len; i++ ){
			if( (int)_letter == lower_map[i] ){
				font_map_lower.partial_draw_pixel_resize(  , y, x + letter_width, y + letter_height, _x, _y, )
			}
		}*/

		for( int i = 0; i < lower_map_len; i++ ){
			if( lower_map[i] == _letter ){
				int crop_x_s = (i%columns) * letter_width;
				int crop_y_s = font_map_lower.image_width - (((i+rows)/rows) * letter_height);
				font_map_lower.partial_draw_pixel_resize(crop_x_s , crop_y_s, crop_x_s + letter_width, crop_y_s + letter_width, _x, _y, _w, _h );
				break;
			}
		}

		//font_map_lower.partial_draw_pixel_resize( 0, 1400, 200, 1600, _x, _y, _w, _h );

	}


	void to_string(){
		
		std::cout << "font map data Lower: \n"; 
		for( int r = 0; r < rows; r++ ){
			for( int c = 0; c < columns; c++ ){
				std::cout << lower_map[ c + (rows*r)] << "\t";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";

		std::cout << "font map data UPPER: \n"; 
		for( int r = 0; r < rows; r++ ){
			for( int c = 0; c < columns; c++ ){
				std::cout << upper_map[ c + (rows*r)] << "\t";
			}
			std::cout << "\n";
		}
	}


};



// this is the class that will display text on the screen using the bitmap loader.
// this class will use a global object that stores different FONTS.
class TEXT{

	// First we take in a string
	// we will take a font
	// look for the path of the font, or look for the file in the font directory.
	// load the bitmap and load the file that tells you the "display interval"
		// A "display interval" is a text file that relates to every font bitmap.
		// it contains:	
		//		A starting x and y position
		//		a width and height for every letter.
		//	Format:
			//	x
			//	y
			//	width
			//	height

public:
	char * content;
	int content_len;
	FONT font;
	int size;
	int width;
	int height;
	int x;
	int y;

	TEXT(){
		content = 	(char *) "NO CONTENT";
		content_len = sizeof(content)/sizeof(char);
		size = 10;
	}

	TEXT( char * c ){
		content = c;
		content_len = sizeof(content)/sizeof(char);
		size = 10;
	}

	void set_font( FONT f ){
		font  = f;
	}

	void set_size( int a ){
		size = a;
	}

	void set_pos( int _x, int _y ){
		x = _x;
		y = _y;
	}


	void draw(){

/*		for( int i = 0; i < content_len; i++ ){
			font.draw_letter( 0 + i*size, 0, size, size, content[i] );	
		}*/

		font.draw_letter( 10, 10, 50, 50, 'a' );

	}


};
	






int main( int argc, char * * argv ){

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize(1224, 1224);
    glutCreateWindow("test_final");
	
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1224, 0, 1224, -1, 1);
    glMatrixMode(GL_MODELVIEW);


    glColor3f( 255, 255, 255 );
    glBegin(GL_QUADS);
     	glVertex3f(0, 0, 0);
     	glVertex3f(0, 1224, 0);
     	glVertex3f(1224, 1224, 0);
     	glVertex3f(1224, 0, 0);
    glEnd();



    IMAGE img2 = IMAGE( (char*) "../fonts/def_lower_case.bmp");
    img2.set_pos( 10, 10 );
    img2.set_size( 500, 500 );
    img2.load();
    img2.partial_draw_pixel_resize( 200, 0, 400, 200, 600, 600, 100, 100);


	TEXT text = TEXT( (char *)"hello" );
    text.set_pos( 100, 100 );


    FONT f1 = FONT( 8, 8 );
    f1.load( (char *)"../fonts/def_lower_case.bmp", (char *)"../fonts/def_lower_case.bmp" );

    f1.map_lower(0, 97, 127);
    f1.map_lower(30, 32, 64);

    f1.map_upper( 0, 97 );
    f1.to_string();

    f1.draw_letter( 100, 100, 500, 500, 'z' );


    glutSwapBuffers();

	glutMainLoop();
	

	return 0;
}