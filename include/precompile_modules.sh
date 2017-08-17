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
		echo "}" >> $output_file

		echo "$word"
	fi



done

cat $end_file >> $output_file		# closing methodsx
