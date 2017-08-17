#include "stusurf.h"
#include "common.h"
#include <iostream>

Base * Stusurf::create_object( std::string _type, int _x, int _y, int _width, int _height, std::string _path_data, int _ID ){
	// output log
	std::cout << "\t\t\tparsed: ";
	std::cout << _type.c_str() << " ";
	std::cout << _x << "-" <<  _y << " ";
	std::cout << _width << "-" << _height << " ";
	std::cout << _path_data.c_str() << "\n";

	Base * _output;

	if( _type == "test_module_100" ){
		_output = new Common::empty_module();
}
else if( _type == "test_module_1" ){
_output = new test_module_1;
((test_module_1 *)_output)->ID = _ID;
((test_module_1 *)_output)->x_full = _x;
((test_module_1 *)_output)->y_full = _y;
((test_module_1 *)_output)->x = (2*(float)_x / WINDOW_WIDTH) - 1;
((test_module_1 *)_output)->y = (2*(float)_y / WINDOW_HEIGHT) - 1;
((test_module_1 *)_output)->width_full = _width;
((test_module_1 *)_output)->height_full = _height;
((test_module_1 *)_output)->width = (2*(float)_width / WINDOW_WIDTH);
((test_module_1 *)_output)->height = (2*(float)_height / WINDOW_HEIGHT);
((test_module_1 *)_output)->path_data = _path_data;
((test_module_1 *)_output)->type_name = _type;
((test_module_1 *)_output)->get_ID = [_ID](){return _ID;};
((test_module_1 *)_output)->get_path_data = [_path_data](){return _path_data;};
((test_module_1 *)_output)->get_type_name = [_type](){return _type;};
}
else if( _type == "test_module_2" ){
_output = new test_module_2;
((test_module_2 *)_output)->ID = _ID;
((test_module_2 *)_output)->x_full = _x;
((test_module_2 *)_output)->y_full = _y;
((test_module_2 *)_output)->x = (2*(float)_x / WINDOW_WIDTH) - 1;
((test_module_2 *)_output)->y = (2*(float)_y / WINDOW_HEIGHT) - 1;
((test_module_2 *)_output)->width_full = _width;
((test_module_2 *)_output)->height_full = _height;
((test_module_2 *)_output)->width = (2*(float)_width / WINDOW_WIDTH);
((test_module_2 *)_output)->height = (2*(float)_height / WINDOW_HEIGHT);
((test_module_2 *)_output)->path_data = _path_data;
((test_module_2 *)_output)->type_name = _type;
((test_module_2 *)_output)->get_ID = [_ID](){return _ID;};
((test_module_2 *)_output)->get_path_data = [_path_data](){return _path_data;};
((test_module_2 *)_output)->get_type_name = [_type](){return _type;};
}
else if( _type == "test_module_3" ){
_output = new test_module_3;
((test_module_3 *)_output)->ID = _ID;
((test_module_3 *)_output)->x_full = _x;
((test_module_3 *)_output)->y_full = _y;
((test_module_3 *)_output)->x = (2*(float)_x / WINDOW_WIDTH) - 1;
((test_module_3 *)_output)->y = (2*(float)_y / WINDOW_HEIGHT) - 1;
((test_module_3 *)_output)->width_full = _width;
((test_module_3 *)_output)->height_full = _height;
((test_module_3 *)_output)->width = (2*(float)_width / WINDOW_WIDTH);
((test_module_3 *)_output)->height = (2*(float)_height / WINDOW_HEIGHT);
((test_module_3 *)_output)->path_data = _path_data;
((test_module_3 *)_output)->type_name = _type;
((test_module_3 *)_output)->get_ID = [_ID](){return _ID;};
((test_module_3 *)_output)->get_path_data = [_path_data](){return _path_data;};
((test_module_3 *)_output)->get_type_name = [_type](){return _type;};
}
else{
		_output = new Common::empty_module();
		((Common::empty_module * )_output)->ID = _ID;
	}

	return _output;
}
