sfml = -lsfml-system -lsfml-window -lsfml-graphics
cpp  = -std=c++11

all: headers \
	 main

main: src/main.cpp
	g++ src/main.cpp include/mother_module.cpp  -o bin/run $(sfml) $(cpp)

headers: include/headers.h
	echo "TBD you must fill thea headers"
