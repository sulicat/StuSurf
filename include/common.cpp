// this includes the definitions of any functions in the Common class located in the common.h file

#include "common.h"
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

bool Common::check_inside_rect( int _x, int _y, int rect_x, int rect_y, int rect_width, int rect_height ){
	// check the left and bottom intesections
	if( _x >= rect_x && _y >= rect_y ){
		// check bottom and right boandaries
		if( _x <= rect_x + rect_width && _y <= rect_y + rect_height ){
			return true;
		}
	}
	return false;
}

std::string Common::int_to_string( int _num ){
	std::ostringstream str;
	str << _num;
	return str.str();
}

std::string * Common::split_string( char * input, char delim ){
	int i = 0;
	std::string part = ""; 

	std::string * out = new std::string[1];
	int out_len = 1;
	out[0] = int_to_string(out_len);

	std::string * temp = new std::string[out_len];

	while( input[i] != '\0' ){

		if( input[i] == delim ){
			// we will add the current part to the string array then empty it.
			// adding the part to the array
			temp = new std::string[ out_len + 1 ];
			std::copy( out, out + out_len, temp );
			out = temp;
			out[ out_len ] = part;
			out_len += 1;
			// clearing the part
			part = "";
			i += 1;
			// recalc the length
			out[0] = int_to_string(out_len);
		}
		part.push_back( input[i] );
		i += 1;
	}

	// add the last element
	temp = new std::string[ out_len + 1 ];
	std::copy( out, out + out_len, temp );
	out = temp;
	out[ out_len ] = part;
	out_len += 1;
	// recalc the length
	out[0] = int_to_string(out_len);

	return out;

}

std::string * Common::split_string( std::string _input, char delim ){
	const char * input = new char[ sizeof( _input.c_str() )/sizeof(char) ];
	input = _input.c_str();

	int i = 0;
	std::string part = ""; 

	std::string * out = new std::string[1];
	int out_len = 1;
	out[0] = int_to_string(out_len);

	std::string * temp = new std::string[out_len];

	while( input[i] != '\0' ){

		if( input[i] == delim ){
			// we will add the current part to the string array then empty it.
			// adding the part to the array
			temp = new std::string[ out_len + 1 ];
			std::copy( out, out + out_len, temp );
			out = temp;
			out[ out_len ] = part;
			out_len += 1;
			// clearing the part
			part = "";
			i += 1;
			// recalc the length
			out[0] = int_to_string(out_len);
		}
		part.push_back( input[i] );
		i += 1;
	}

	// add the last element
	temp = new std::string[ out_len + 1 ];
	std::copy( out, out + out_len, temp );
	out = temp;
	out[ out_len ] = part;
	out_len += 1;
	// recalc the length
	out[0] = int_to_string(out_len);

	return out;

}

int Common::string_to_int( std::string _input ){
	return atoi( _input.c_str() );
}

float Common::string_to_float( std::string _input ){
	return atof( _input.c_str() );
}

void Common::render_char( float _x, float _y, float _scale, char _c ){
	float _size = _scale * FONT_SIZE_ROMAN;
	glPushMatrix();
		glTranslatef( _x, _y, 0 );
		glScalef( _size, _size, _size  );
		glutStrokeCharacter( GLUT_STROKE_ROMAN, _c );
	glPopMatrix();
}


void Common::render_string( float _x, float _y, float _scale, std::string _s ){
	float current_pos = 0;
	for( int i = 0; i < _s.length(); i++ ){
		render_char( _x + current_pos, _y, _scale, _s[i] );
		current_pos = current_pos + glutStrokeWidth( GLUT_STROKE_ROMAN, _s[i] )*FONT_SIZE_ROMAN*_scale;
	}
}

void Common::render_paragraph( float _x, float _y, float _width, float _height, float _scale, std::string _p ){
	float current_pos_x = 0;
	float current_pos_y = 0;

	for( int i = 0; i < _p.length(); i++ ){
		render_char( _x + current_pos_x, _y + current_pos_y, _scale, _p[i] );
		current_pos_x += glutStrokeWidth( GLUT_STROKE_ROMAN, _p[i] )*FONT_SIZE_ROMAN*_scale;

		if( current_pos_x > _x + _width + 1 ){
			current_pos_x = 0;
			current_pos_y -= _scale;
		}
	}

}
