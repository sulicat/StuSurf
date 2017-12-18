sfml = -lsfml-system -lsfml-window -lsfml-graphics
cpp  = -std=c++11

all: headers \
	 main

main: src/main.cpp
	g++ src/*.cpp -o bin/run $(sfml) $(cpp)

headers: include/headers.h
	./src/linux/update_headers.sh
	echo "PRECOMPILE: updated headers in LINUX....\n"
