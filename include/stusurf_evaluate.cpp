#include <iostream>
#include "stusurf.h"
#include <fstream>

#define MAX_LINE_READ 256

// the goal of evaluate....
// 	this is a function that will be written by a bash script
//	the bash script will look through all the models


void Stusurf::evaluate_screen(){
	// we must first clear out the data located in the old screen
	delete[] main_list;
	main_list = new Base * [0];
	main_list_len = 0;

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
			std::cout << "\t\t" << line;
			// at this point. we are going to assume that for every line, there is the required info. We will perform an error check...
			// length must be 7.
			std::string * line_arr = Common::split_string( line, ' ' );
			if( line_arr[0] != "7" ){
				std::cout << " ... ERROR. Could not parse line in file: " << current_selected_screen << "\n";

			}else{
				std::cout << " ... GOOD\n";
				// we will send the split data into another function.
				// this is a function that is written by a bash script after reading the modules.
				// this function will return an object that we can add to main_list. And that way we can render things in file
				// line template :
				//			Object_name x y width height path_data
				//index:	1			2 3 4	  5		 6

				Base * temp_add;
				temp_add  = 	create_object( 	line_arr[1],
												Common::string_to_int( line_arr[2] ),
												Common::string_to_int( line_arr[3] ),
												Common::string_to_int( line_arr[4] ),
												Common::string_to_int( line_arr[5] ),
												line_arr[6] 							);

				add( temp_add );
			}

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
