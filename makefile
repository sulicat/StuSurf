sfml = -lsfml-system -lsfml-window -lsfml-graphics
cpp  = -std=c++11
boost = -l../lib/boost_1_66_0/boost/

all: headers \
	 main

main: src/main.cpp
	g++ src/*.cpp -o bin/run $(sfml) $(cpp)

headers: include/headers.h
	@./src/linux/update_headers.sh
	@echo "\tPRECOMPILE: updated headers in LINUX...."
	@./src/linux/update_createModule.sh
	@echo "\tPRECOMPILE: update module factory in LINUX...."
	@echo ""
