// this is the common file
// it will include the:
//	- inheritance bases for modules we make
// 	- global variables we want everything to have access to.
// 	- some common imports.
#ifndef STUSURF_COMMON
#define STUSURF_COMMON

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern sf::RenderWindow window;
extern sf::Color COLOR_PRIMARY;
extern sf::Color COLOR_SECONDARY_1;
extern sf::Color COLOR_SECONDARY_2;
extern sf::Color COLOR_PRIMARY_LIGHT;
extern sf::Color COLOR_SECONDARY_1_LIGHT;
extern sf::Color COLOR_SECONDARY_2_LIGHT;
extern sf::Color COLOR_PRIMARY_PALE;
extern sf::Color COLOR_SECONDARY_1_PALE;
extern sf::Color COLOR_SECONDARY_2_PALE;
extern sf::Color COLOR_PRIMARY_DARK;
extern sf::Color COLOR_SECONDARY_1_DARK;
extern sf::Color COLOR_SECONDARY_2_DARK;
extern sf::Color COLOR_WHITE;
extern sf::Color COLOR_BLACK;

extern sf::Font MAIN_FONT;

class Menu;
class MenuItem;

extern std::vector<int>							input_buffer;
extern std::vector< Menu* >						list_enabled_menus;

enum PROGRAM_STATE{
	EDIT,
	USE,
	COMMAND,
	SCREEN_CHANGE
};


class ModuleBase{
public:
	int 	x;
	int 	y;
	int 	width;
	int 	height;
	bool 	isFocused;

	virtual void onKeyDown		( int code )					{ std::cout << "key DOWN function UNDEFINED in module\n";	}
	virtual void onKeyUp		( int code )					{ std::cout << "key UP function UNDEFINED in module\n";		}
	virtual void onMouseMove	( int x, int y  )				{ std::cout << "mouse MOVE function UNDEFINED in module\n";	}
	virtual void onMouseDown	( int button, int x, int y )	{ std::cout << "mouse DOWN function UNDEFINED in module\n";	}
	virtual void onMouseUp		( int button, int x, int y )	{ std::cout << "mouse UP function UNDEFINED in module\n";	}
	virtual void render			()								{};
};


class KeyBind{
 public:
	std::vector<int> 			commands;
	std::string 				description;
	int 						x;
	int							y;
	std::function<void(void)>	trigger;


	KeyBind( ){
		description = "No description";
	}
	KeyBind( std::string _description ){
		description = _description;
	}

	void set_trigger( std::function<void(void)> _temp){
		trigger = _temp;
	}

	void add_command( int _temp){
		commands.push_back( _temp );
	}

	bool isTriggered( std::vector<int> _com){
		if( _com == commands ){ return true; } return false;
	}

	void compare( std::vector<int> _com ){
		if( _com == commands ){ trigger(); }
	}
};


class MenuItem{
 private:
	void	origin();
	void	update();

 public:
	std::function<void(std::string)>			trigger;
	std::string									label;
	std::string									caption;
	int						x;
	int 					y;
	float					width;
	float					height;
	bool					selected;
	// visuals
	sf::RectangleShape		backdrop;
	sf::Font				_font;
	sf::Text				label_text;

	MenuItem( );
	MenuItem( std::string _title );

	void setLabel			( std::string _label );
	void setCaption			( std::string _caption );
	void setTrigger			( std::function< void(std::string)> _func );
	void set_position		( float _x, float _y );
	void set_size			( float _w, float _h );
	void select				( bool _b );
	void render();

};


class Menu{
 private:
	void update_positions	();
	void origin				();
	int						number_of_items_visible;
	float					height_per_item;

 public:
	std::vector<MenuItem>				contents;
	std::vector<MenuItem>				contents_shown;
	std::string							title;
	std::string							caption;
	int									x;
	int 								y;
	int 								width;
	int 								height;
	int 								scroll;
	int 								selected_index;

	bool								selected;
	bool								active;
	// look and feel
	sf::RectangleShape 					backdrop;

	Menu();
	Menu( std::string _t );

	void add			( MenuItem _add );
	void set_position	( int _x, int _y );
	void set_size		( int _w, int _h );
	void event			(sf::Event e);
	void render			();
	void enable			();
	void disable		();
};



#endif
