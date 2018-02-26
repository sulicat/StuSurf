#include "../include/common.h"

#ifndef STUSURF_SCREENMANAGER
#define STUSURF_SCREENMANAGER


class ScreenManager{
 public:
	std::vector<std::unique_ptr< ModuleBase >>	current_screen;		// list of open modules in screen
	std::string									currentScreenPath;	// which screen we are currently seeing
	std::string 								path_topDir;		// absolute path to top dir
	std::string									path_screenList;	// relative path to list of screens
	enum PROGRAM_STATE							state;

	int 										cursor_x;
	int 										cursor_y;
	int											cursor_speed;

	KeyBind										command_execute;
	KeyBind										command_screen_change;
	KeyBind										command_escape;
	Menu										menu_screens;
	Menu										add_items;
	CommandBox									textbox_commands;


	// VISUALS
	sf::RectangleShape		border;
	sf::Text				state_text;
	sf::RectangleShape		cursor_vert;
	sf::RectangleShape		cursor_horiz;



	ScreenManager		( std::string _topDir );
	void add			( ModuleBase * _item );
	void input			( sf::Event _event);
	void changeScreen	( std::string _p );
	void changeState	( enum PROGRAM_STATE _s );
	void addModule_start( void* _d);
	void move_cursor	( sf::Event _e );
	void move_cursor	( int _x, int _y );
	void updateScreen	();
	void render			();
	void resize			();
	void test();
};


#endif
