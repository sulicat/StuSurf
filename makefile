all:
	chmod +x update_headers.sh
	./update_headers.sh
	chmod +x include/precompile_modules.sh
	./include/precompile_modules.sh
	g++ -o bin/run *.cpp include/*.cpp -std=c++11 -lglut -lGL -lGLU
