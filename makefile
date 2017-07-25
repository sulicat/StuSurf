all:
	./update_headers.sh
	g++ -o bin/run *.cpp include/*.cpp -lglut -lGL -lGLU
