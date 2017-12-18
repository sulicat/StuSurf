header_file=include/headers.h

echo "#ifndef STUSURF_HEADERS" > $header_file
echo "#define STUSURF_HEADERS" >> $header_file
echo "" >> $header_file

echo '#include "../include/common.h"' >> $header_file

for file in modules/*.h; do
	echo '#include "../'$file'"' >> $header_file
done

echo "" >> $header_file
echo "#endif" >> $header_file
