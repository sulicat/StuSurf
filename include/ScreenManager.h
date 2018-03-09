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
	int											cursor_x_start;
	int											cursor_y_start;
	int											cursor_speed;
	int											ADD_STATE;
	int											DELETE_INDEX;
	std::string									module_to_add;

	KeyBind										command_execute;
	KeyBind										command_screen_change;
	KeyBind										command_escape;
	Menu										menu_screens;
	Menu										add_items;
	CommandBox									textbox_commands;
	OptionInput									option_standard_text;


	// VISUALS
	sf::RectangleShape		border;
	sf::RectangleShape		crosshair;
	sf::RectangleShape		new_add_box;
	sf::Text				state_text;
	sf::RectangleShape		cursor_vert;
	sf::RectangleShape		cursor_horiz;
	sf::RectangleShape		deleteBoundingBox;
	sf::RectangleShape		deleteBoundingBox1;
	sf::RectangleShape		deleteBoundingBox2;



	ScreenManager			( std::string _topDir );
	void add				( ModuleBase * _item );
	void input				( sf::Event _event);
	void changeScreen		( std::string _p );
	void changeState		( enum PROGRAM_STATE _s );
	void addModule_start	( void* _d);
	void addModule_screen	();
	void move_cursor		( sf::Event _e );
	void move_cursor		( int _x, int _y );
	void updateScreen		();
	void render				();
	void resize				();
	void test				();
	void postKeyPress		( sf::Event _e );
	void deleteModule		( int _m );
};


#endif
