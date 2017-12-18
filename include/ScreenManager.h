#include "../include/common.h"

class ScreenManager{
 public:
	std::vector<std::unique_ptr< ModuleBase >>	current_screen;		// list of open modules in screen
	std::string 								path_topDir;		// absolute path to top dir
	std::string									path_screenList;	// relative path to list of screens
	enum PROGRAM_STATE							state;

	KeyBind										command_execute;
	KeyBind										command_screen_change;
	KeyBind										command_escape;

	Menu										testMenu;

	ScreenManager	( std::string _topDir );
	void add		( ModuleBase * _item );
	void input		( sf::Event _event);
	void render		();
	void test();
};
