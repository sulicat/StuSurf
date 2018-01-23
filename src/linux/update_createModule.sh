#!/bin/bash

MODULES=../../modules/*.h

for file in $MODULES;
do
	# get the class name.
	echo $file | rev | cut -d"/" -f1  | rev | rev | cut -d"." -f2  | rev

done
