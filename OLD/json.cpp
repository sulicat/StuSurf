// JSON

//#ifndef H_JSON_GUARD
//#define H_JSON_GUARD

#include <fstream>
#include <iostream>
#include "lib/rapidjson/document.h"


class JSON{
	char * input;



};


int main( int argc, char * * argv ){

	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";

	rapidjson::Document d;
	d.Parse( json );

	rapidjson::Value & s = d["project"];
	std::cout << s.GetString() << "\n";

	return 0;
}


//#endif