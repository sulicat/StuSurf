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
}
else if( _type == "test_module_2" ){
_output = new test_module_2;
((test_module_2 *)_output)->ID = _ID;
}
else if( _type == "test_module_3" ){
_output = new test_module_3;
((test_module_3 *)_output)->ID = _ID;
}
else{
		_output = new Common::empty_module();
		_output->set_path( ( char * ) _path_data.c_str() );
		((Common::empty_module * )_output)->ID = _ID;
	}

	_output->set_size( _width, _height );
	_output->set_pos( _x, _y );

	return _output;
}
