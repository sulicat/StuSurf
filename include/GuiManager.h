#include "common.h"


#ifndef STUSURF_GUIMANAGER
#define STUSURF_GUIMANAGER

class GuiManager{
 public:
	std::vector <Menu*> 	menus;
	std::vector <Menu*> 	menus_hidden;
	std::vector <CommandBox*> 	textBoxes;

	GuiManager();
	void enable						( Menu* _m );
	void disable					( Menu* _m );
	void hide						( Menu* _m );
	void enable						( CommandBox* _m );
	void disable					( CommandBox* _m );
	void clear						();
	bool is_intercepting_input		();
	void input						( sf::Event e );
	void render						();
	void reverse_menu				();
};

#endif
