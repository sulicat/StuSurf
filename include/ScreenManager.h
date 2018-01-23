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

	KeyBind										command_execute;
	KeyBind										command_screen_change;
	KeyBind										command_escape;
	KeyBind										command_test1;	// ~~~~

	Menu										menu_screens;
	Menu										menu_test1;		// ~~~~
	Menu										menu_test2;		// ~~~~
	Menu										menu_test3;		// ~~~~

	ScreenManager		( std::string _topDir );
	void add			( ModuleBase * _item );
	void input			( sf::Event _event);
	void changeScreen	( std::string _p );
	void updateScreen	();
	void render			();
	void test();
};


#endif
