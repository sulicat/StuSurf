#!/bin/bash

MODULES=modules/*.h
outFile=src/PRECOMPILE_populate_module_factory.cpp

echo -n "" > $outFile
echo '#include "../include/common.h"' >> $outFile
echo '#include "../include/headers.h"' >> $outFile
echo "" >> $outFile
echo 'std::map<std::string, std::function<ModuleBase*( int, int, int, int, std::string)> > MODULE_FACTORY;' >> $outFile
echo 'void common::PRECOMPILE_populate_module_factory(){' >> $outFile
echo "" >> $outFile

for file in $MODULES;
do
	# get the class name.
	#echo $file | rev | cut -d"/" -f1  | rev | rev | cut -d"." -f2  | rev >> $outFile

	#outputting the data to a the C file
	echo -n -e '\t' >> $outFile
	echo -n 'MODULE_FACTORY.insert( std::pair<std::string, std::function<ModuleBase*(int,int,int,int,std::string)> >("' >> $outFile
	echo $file | rev | cut -d"/" -f1  | rev | rev | cut -d"." -f2  | rev | tr -d $'\n' >> $outFile
	echo -n '",	[](int _x, int _y, int _w, int _h, std::string _f){ModuleBase* out = new ' >> $outFile
	echo $file | rev | cut -d"/" -f1  | rev | rev | cut -d"." -f2  | rev | tr -d $'\n' >> $outFile
	echo -n '(_x, _y, _w, _h); out->setDataFile(_f); out->setDataType("' >> $outFile
	echo $file | rev | cut -d"/" -f1  | rev | rev | cut -d"." -f2  | rev | tr -d $'\n' >> $outFile
	echo -n '"); return out;} ));' >> $outFile
	echo "" >> $outFile

done


echo '}' >> $outFile
