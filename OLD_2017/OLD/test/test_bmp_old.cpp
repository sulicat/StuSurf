#include <iostream>
#include <stdio.h>
#include <fstream>
#include <GL/glut.h>
#include <math.h>


struct info{
	int start;
	int end;
	char * name;
	unsigned char * value;

	info( int s, int e, char * n, unsigned char * val ){
		start = s;
		end = e;
		name = n;
		value = val;
	}

};




int main( int argc, char * * argv ){
	

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize(1224, 1224);
    glutCreateWindow("windowname");


	// create file object
	std::ifstream f;
	size_t size;

	// open file
	f.open( "test_4.bmp", std::ios::in | std::ios::binary  );
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


	// the info of the parts before the pixel array.
	info import[] = { 	info( 0,   2, 		(char*) "signature",   				NULL ),	//0
						info( 2,   6, 		(char*) "file size",   				NULL ),	//1
						info( 6,   10, 		(char*) "reserved",   				NULL ),	//2
						info( 10,  14, 		(char*) "offset to array", 			NULL ),	//3
						info( 14,  18, 		(char*) "dip_header",  				NULL ),	//4
						info( 18,  22, 		(char*) "width",	    			NULL ),	//5
						info( 22,  26, 		(char*) "height", 	   				NULL ),
						info( 26,  28, 		(char*) "planes", 	   				NULL ),
						info( 28,  30, 		(char*) "bits per pixel", 	   		NULL ),
						info( 30,  34, 		(char*) "compression",	 	   		NULL ),	
						info( 34,  38, 		(char*) "image size",	 	   		NULL ),	//10
						info( 38,  42,	 	(char*) "X pixels per meter",  		NULL ),
						info( 42,  46, 		(char*) "Y pixels per meter", 		NULL ),
						info( 46,  50, 		(char*) "Colors in color table", 	NULL ),
						info( 50,  54, 		(char*) "Important Color Count", 	NULL ),
						info( 54,  58, 		(char*) "red chanel bitmask", 		NULL ),	//15
						info( 58,  62, 		(char*) "blue chanel bitmask", 		NULL ),
						info( 62,  66, 		(char*) "green chanel bitmask", 	NULL ),
						info( 66,  70, 		(char*) "alpha chanel bitmask",		NULL ),
						info( 70,  74, 		(char*) "color space type", 		NULL ),
						info( 74,  78, 		(char*) "color space enpoints",		NULL ),	//20
						info( 78,  82, 		(char*) "gamma for red chanel", 	NULL ),
						info( 82,  86, 		(char*) "gamma for green chanel", 	NULL ),
						info( 86,  90, 		(char*) "gamma for blue chanel", 	NULL ),
						info( 90,  94, 		(char*) "intent",				 	NULL ),
						info( 94,  98, 		(char*) "ICC profile data",	 		NULL ),	//25
						info( 98,  102, 	(char*) "ICC profile size", 		NULL ),
						info( 102, 104, 	(char*) "reserved", 				NULL )
						
					};


	// get the size of the list above
	int import_size = sizeof( import )/sizeof( info );

	
	//cycle through char array.
	//	for every charecter check if there is a property that corresponds to it. If there is, read it and store it in the above array.
	unsigned short temp;
	for( int i = 0; i < size; i++ ){
		for( int c = 0; c < import_size; c++ ){

			if( i == import[ c ].start ){
				temp = new unsigned short[ import[c].end - import[c].start ];
		
				std::copy( file + import[c].start, file + import[c].end, temp );
		
				import[ c ] = info( i, import[c].end, import[c].name, temp );
				i = import[ c ].end-1;
			}
		}

	}


	// testing 
	


	// ********************************************************************************************************************************* //
	// ********************************************************************************************************************************* //
	// 	we have the header data we needed
	// 	we can now jump to the pixel array and read it, as that is the end goal.

	// find the pixel offset using the list gatherd up top.
	int pixel_offset = 		(unsigned int)	(*import[ 3 ].value);
	
	//int image_width =		(unsigned int)	(*import[ 5 ].value);
	//int image_height =		(unsigned int)	(*import[ 6 ].value);
	
	int image_width =		(unsigned int)	(*import[ 5 ].value);
	int image_height =		(unsigned int)	(*import[ 6 ].value);
	

	int bits_per_pixel = 	(unsigned int)	(*import[ 8 ].value);

	

	std::cout << "width: " << image_width << " height: " << image_height << "\n";
	std::cout << "BPP: " << bits_per_pixel << "\n";


	// every pixel is given three bytes. we know the width and height, therefore we know the number of pixels.
	// now we loop through them and store each pixel in a two byte data type.
	GLubyte image_data[ image_width * image_height * 3 ];


	// we know the bits per pixel so we know the size of every pixel

	// 24 bbp 	= 3 bytes per pixel
	//			= 1 byte  per color.
	if( bits_per_pixel == 24 || bits_per_pixel == 32 ){
		for( int i = 0; i < (image_width * image_height * 3) - 2; i++ ){
			

			image_data[ i ] = (GLubyte)255;
			image_data[ i+1 ] = 0;
			image_data[ i+2 ] = 0;	
			i += 2;
		
		}
	}

	GLubyte * texDat = image_data;
	

/*
	int total_pixel_count = image_width * image_height * 3;
	for( int i = 0; i < total_pixel_count; i++ ){
		std::cout << std::dec << (int)texDat[i] << " ";

	}
*/

/*
	// print the array and all the components
	for( int i = 0; i < import_size; i++ ){
		std::cout << std::dec << "info: " << import[ i ].name;
		std::cout << "\n\t" << import[ i ].start << " - " << import[ i ].end << " data: " << std::dec <<  (int)(*import[ i ].value) << "\n\n"; 
	}
*/











    //upload to GPU texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat); 
    glBindTexture(GL_TEXTURE_2D, 0);


    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1224, 0, 1224, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    //clear and draw quad with texture (could be in display callback)
    
    
    glColor3f( 255, 0, 0 );
    glBegin(GL_QUADS);
     	glVertex3f(0, 0, 0);
     	glVertex3f(0, 1224, 0);
     	glVertex3f(1224, 1224, 0);
     	glVertex3f(1224, 0, 0);
    glEnd();

    glFlush(); //don't need this with GLUT_DOUBLE and glutSwapBuffers

    glEnable(GL_TEXTURE_2D);
    glColor3f( 1.0, 1.0, 1.0 );

    glBindTexture(GL_TEXTURE_2D, tex);
    
    glBegin(GL_QUADS);
	    glTexCoord2f(0, 0); glVertex2i(100, 100);
   		glTexCoord2f(0, 1); glVertex2i(100, 1124);
    	glTexCoord2f(1, 1); glVertex2i(1124, 1124);
    	glTexCoord2f(1, 0); glVertex2i(1124, 100);
    glEnd();

    //getchar(); //pause so you can see what just happened
    //System("pause"); //I think this works on windows

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    


    glFlush(); //don't need this with GLUT_DOUBLE and glutSwapBuffers
    glutMainLoop();

    return 0;










	return 0;
}