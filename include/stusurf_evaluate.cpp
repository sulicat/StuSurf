#include <iostream>
#include "stusurf.h"
#include <fstream>

#define MAX_LINE_READ 256

// the goal of evaluate....
// 	this is a function that will be written by a bash script
//	the bash script will look through all the models


void Stusurf::evaluate_screen(){
	std::cout << "\nstarting evaluation: \n";
	std::cout << "evaluating: " << current_selected_screen << "\n";

	// first we set the start screen as a file.
	// if the start screen already exists... we will parse it.
	// if the start screen does not exist, we will create an empty one.
	// then we will parse it.
	//	The parsing has to consist of:
	//		reading all the lines in the file
	//		for every line, we will create a relevant object.
	//		The lines have the following format.
	//		Object_name	x y width height info_file
	//		Object name will have the same name as the class it is part of.

	// we have the current screen selected. We will now check the existance
	//	of the file

	//	std::fstream file_stream_screen( current_selected_screen.c_str(), std::fstream::in | std::fstream::out );
	std::fstream file_stream_screen;
	file_stream_screen.open( current_selected_screen.c_str(), std::fstream::in | std::fstream::out );

	if( file_stream_screen.good() ){
		// the file exists.... we will now parse it and create a bunch of objects...
		std::cout << "the file " << current_selected_screen << " is good > will now start parsing\n";
		file_stream_screen.close();
		file_stream_screen.open( current_selected_screen.c_str(), std::fstream::in );	// reopen in read only

		char * line = new char[ MAX_LINE_READ ];

		std::cout << "\tstaring line parse....\n";
		while( file_stream_screen.getline( line, MAX_LINE_READ )  ){
			std::cout << "\t" << line << "\n";
			std::cout << "\t\t" << Common::string_to_int(Common::split_string( line, ' ' )[0]) + 1 << "\n";

		}
		std::cout << "\tendingstaring line parse....\n";

	}else{
		// the file doesn't exist. We will create it and make it blank...
		file_stream_screen.close();		// closing, Want to re-open in truncate mode
		file_stream_screen.open( current_selected_screen.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc );
		std::cout << "the file: " << current_selected_screen << " does not exists. Creating Blank\n";
		file_stream_screen << "";


	}

	file_stream_screen.close();
}
