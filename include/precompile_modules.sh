#!/bin/bash

output_file="include/stusurf_automated.cpp"
start_file="include/start_of_automated"
end_file="include/end_of_automated"

# we want to echo a list of all modules into a file for the program to use in the future
module_list_file="include/module_list"
# clear out the existing module_list_file
printf "%s" "" > $module_list_file

# first we cycle through all the files in the modules directory.
echo "clearing automated file: "
cat $start_file > $output_file
echo "}" >> $output_file		# closing if.

for file in modules/*.h; do

	# for every file... we want to find the class keyword. We also want to find the : Base extention. Using this information,
	#	We will update the stusurf_automated.cpp file. We will add the following to it.
	# 	For every module we find that extends base. We will create a new conditional
	#	if( _type == "module_name" ){
	#		_output = new module_name.
	#	}

	# we will look for a line in the file with the following key words.
	#		class + : + public + Base
	line=$( grep "Base" $file | grep "public" | grep "class" | grep ":" )

	if [ $? == 0 ]
	then
		# the line is found. we will now add support
		word=$(echo "$line" | awk -F 'class ' '{print $2}' | awk -F ' : ' '{print $1}' )
		echo "$word" >> $module_list_file

		echo "else if( _type == \"$word\" ){" >> $output_file
		echo "_output = new $word;" >> $output_file
		echo "(($word *)_output)->ID = _ID;" >> $output_file
		# setting the position per object
		echo "(($word *)_output)->x_full = _x;" >> $output_file
		echo "(($word *)_output)->y_full = _y;" >> $output_file
		echo "(($word *)_output)->x = (2*(float)_x / WINDOW_WIDTH) - 1;" >> $output_file
		echo "(($word *)_output)->y = (2*(float)_y / WINDOW_HEIGHT) - 1;" >> $output_file
		# setting the size per object
		echo "(($word *)_output)->width_full = _width;" >> $output_file
		echo "(($word *)_output)->height_full = _height;" >> $output_file
		echo "(($word *)_output)->width = (2*(float)_width / WINDOW_WIDTH);" >> $output_file
		echo "(($word *)_output)->height = (2*(float)_height / WINDOW_HEIGHT);" >> $output_file
		# set the path to the data
		echo "(($word *)_output)->path_data = _path_data;" >> $output_file
		echo "(($word *)_output)->type_name = _type;" >> $output_file
		# set the GET function
		echo "(($word *)_output)->get_ID = [_ID](){return _ID;};" >> $output_file
		echo "(($word *)_output)->get_path_data = [_path_data](){return _path_data;};" >> $output_file
		echo "(($word *)_output)->get_type_name = [_type](){return _type;};" >> $output_file

		echo "}" >> $output_file

		echo "$word"
	fi



done

cat $end_file >> $output_file		# closing methodsx
