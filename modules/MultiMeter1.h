#include "../include/common.h"
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../include/Managers.h"


class MultiMeter1 : public ModuleBase{
public:
	sf::RectangleShape rect1;
	sf::Color c;
	int sfd;
	struct termios options;

	MultiMeter1( int _x, int _y, int _w, int _h  ){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		isFocused = false;

		// non standard
		rect1 = sf::RectangleShape( sf::Vector2f(width, height) );
		rect1.setPosition( x, y );
		c = sf::Color( 255, 0, 255 );
		rect1.setFillColor( c );

		sfd = open("/dev/ttyUSB0", O_RDWR  | O_NOCTTY );
		// set the speed to 115200 baud
		tcgetattr(	sfd, &options);
		cfsetspeed(	&options, B115200);
		options.c_cflag &= ~CSTOPB;
		options.c_cflag |= CLOCAL;
		options.c_cflag |= CREAD;
		cfmakeraw(	&options);
		tcsetattr(	sfd, TCSANOW, &options);
		// port open check
		if( sfd < 0 ){
			printf("error opening the port\n");
		}



	}

	void onKeyDown( int _code ){
		//std::cout << "code: " << _code << "\n";
	}

	void onKeyUp( int _code ){
	}

	void onMouseMove( int _x, int _y ){
	}

	void onMouseDown( int _button, int _x, int _y ){
		std::cout << common::varFromFile( screenManager.currentScreenPath, "var1" ) << "\n";
	}

	void onMouseUp(int _button, int _x, int _y ){
		//std::cout << "_button: " << _button << "\n";
	}

	void render(){
		window.draw( rect1 );
		char buf[20] 	= "";
		read( sfd, buf, 20);

		//		printf( "%s\n", buf);


	}

};
