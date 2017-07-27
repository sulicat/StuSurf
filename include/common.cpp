// this includes the definitions of any functions in the Common class located in the common.h file

#include "common.h"
#include <iostream>

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

