header_file=include/headers.h

echo "#ifndef _ALL_HEADERS_H" > $header_file
echo "#define _ALL_HEADERS_H" >> $header_file

echo "" >> $header_file

for file in modules/*.h; do
	echo '#include "../'$file'"' >> $header_file
done

echo "" >> $header_file
echo "#endif" >> $header_file
