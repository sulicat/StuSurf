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
else if( _type == "text" ){
_output = new text;
((text *)_output)->ID = _ID;
((text *)_output)->x_full = _x;
((text *)_output)->y_full = _y;
((text *)_output)->x = (2*(float)_x / WINDOW_WIDTH) - 1;
((text *)_output)->y = (2*(float)_y / WINDOW_HEIGHT) - 1;
((text *)_output)->width_full = _width;
((text *)_output)->height_full = _height;
((text *)_output)->width = (2*(float)_width / WINDOW_WIDTH);
((text *)_output)->height = (2*(float)_height / WINDOW_HEIGHT);
((text *)_output)->path_data = _path_data;
((text *)_output)->type_name = _type;
((text *)_output)->get_ID = [_ID](){return _ID;};
((text *)_output)->get_path_data = [_path_data](){return _path_data;};
((text *)_output)->get_type_name = [_type](){return _type;};
}
else if( _type == "text_spinning" ){
_output = new text_spinning;
((text_spinning *)_output)->ID = _ID;
((text_spinning *)_output)->x_full = _x;
((text_spinning *)_output)->y_full = _y;
((text_spinning *)_output)->x = (2*(float)_x / WINDOW_WIDTH) - 1;
((text_spinning *)_output)->y = (2*(float)_y / WINDOW_HEIGHT) - 1;
((text_spinning *)_output)->width_full = _width;
((text_spinning *)_output)->height_full = _height;
((text_spinning *)_output)->width = (2*(float)_width / WINDOW_WIDTH);
((text_spinning *)_output)->height = (2*(float)_height / WINDOW_HEIGHT);
((text_spinning *)_output)->path_data = _path_data;
((text_spinning *)_output)->type_name = _type;
((text_spinning *)_output)->get_ID = [_ID](){return _ID;};
((text_spinning *)_output)->get_path_data = [_path_data](){return _path_data;};
((text_spinning *)_output)->get_type_name = [_type](){return _type;};
}
else{
		_output = new Common::empty_module();
		((Common::empty_module * )_output)->ID = _ID;
	}

	return _output;
}
