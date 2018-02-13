// this is the common file
// it will include the:
//	- inheritance bases for modules we make
// 	- global variables we want everything to have access to.
// 	- some common imports.
#ifndef STUSURF_COMMON
#define STUSURF_COMMON

#include <SFML/Graphics.hpp>
//#include "../lib/boost_1_66_0/boost/filesystem.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <functional>

// prototypes
class Menu;
class MenuItem;
class ModuleBase;
class Command;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int MENU_WIDTH;
extern int MENU_HEIGHT;
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
extern sf::Color COLOR_GREY;

extern sf::Color COLOR_Menu_1;
extern sf::Color COLOR_Menu_2;
extern sf::Color COLOR_Menu_3;
extern sf::Color COLOR_Menu_4;

extern sf::Color COLOR_CommandBox_1;
extern sf::Color COLOR_CommandBox_2;
extern sf::Color COLOR_CommandBox_3;
// font
extern sf::Font MAIN_FONT;
// images
extern sf::Texture ICON_FOLDER;
// input buffer
extern std::vector<int> input_buffer;
// map to store module types
extern std::map<std::string, std::function<ModuleBase*( int, int, int, int, std::string)> > MODULE_FACTORY;
// Command List
extern std::vector<Command> Main_Commands;


enum PROGRAM_STATE{
	EDIT,
	USE,
	COMMAND,
	SCREEN_CHANGE
};

enum MENU_ITEM_TYPE{
	OPEN_MENU,
	TRIGGER_FUNCTION,
	NOTHING
};


// class with the commonly used functions. Accessible to things within the program
class common{
 public:
	static void							EMPTY			( void* );
	static std::string 					toLower			( std::string in );
	static std::string 					toUpper			( std::string in );
	static std::vector<std::string>		files_in		( std::string _dir );
	static std::vector<std::string>		folders_in		( std::string _dir );
	static Menu*						menuFromDir		( std::string _dir, std::function<void(void*)> _func );
	static bool							varToFile		( std::string _file, std::string var_name, std::string _var );
	static std::string					varFromFile		( std::string _file, std::string var_name );
	static std::vector<std::string>		splitString		( std::string _in, std::string _delim );

	static void							PRECOMPILE_populate_module_factory();
};

class ModuleBase{
public:
	int 	x;
	int 	y;
	int 	width;
	int 	height;
	bool 	isFocused;
	std::string dataFile;

	virtual void setDataFile	( std::string _data )			{ dataFile = _data; }
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


// Used to give functions a name.
class Command {
 public:
	std::function <void(void*)> callback;
	std::string name;
	bool use_name;
	void* data;

	Command( std::function <void(void*)> _f, std::string _n ){ callback = _f; name = _n; use_name = true; }
	Command( std::function <void(void*)> _f, std::string _n, void* _d ){ callback = _f; name = _n; data = _d; use_name = false; }
	void call( ){
		if( use_name == false )
			callback( data );
		else
			callback( &name );
	}
};


class Label{
 private:
	void origin();

 public:
	std::string title;
	int x;
	int y;
	int width;
	int height;
	sf::Text				label_text;
	sf::RectangleShape		backdrop;

	Label( std::string _t, int _x, int _y, int _w, int _h );
	void set_pos( int _x, int _y );
	void set_size( int _w, int _h );
	void select();
	void render();

};

/*****************************************************************************************/
// Menus

class MenuItem{
 private:
	void	origin();
	void	update();

 public:
	std::function<void(void*)>		trigger;
	std::string						label;
	std::string						caption;
	int						x;
	int 					y;
	float					width;
	float					height;
	bool					selected;
	enum MENU_ITEM_TYPE		type;
	void*					data;
	Menu*					open_menu;
	// visuals
	sf::RectangleShape		backdrop;
	sf::Font				_font;
	sf::Text				label_text;
	sf::Sprite				icon_folder;

	MenuItem		( );
	MenuItem		( std::string _title );
	MenuItem		( std::string _title, std::function <void(void*)> _func );
	MenuItem		( std::string _title, std::function <void(void*)> _func, void* _data );
	MenuItem		( std::string _title, Menu* _m );
	MenuItem		( std::string _title, std::function <void(void*)> _func, Menu* _m );
	MenuItem		( std::string _title, std::function <void(void*)> _func, void* _data, Menu* _m );

	void setLabel			( std::string _label );
	void setCaption			( std::string _caption );
	void setTrigger			( std::function <void(void*)> _func );
	void setTrigger			( Menu* _m );
	void setTrigger			( std::function <void(void*)> _func, Menu * _m );
	void setData			( void * _a);
	void set_position		( float _x, float _y );
	void set_size			( float _w, float _h );
	void select				( bool _b );
	void call				();
	void clear				();
	void render();
};


class Menu{
 private:
	int						number_of_items_visible;
	float					height_per_item;
	void origin				();
	void update_positions	();
	void update_displays	();
	void update_search		();

 public:
	std::vector<MenuItem>				contents_full;
	std::vector<MenuItem>				contents;
	std::vector<MenuItem>				contents_shown;
	std::string							title;
	std::string							caption;
	std::string							search_term;
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
	sf::RectangleShape					hide_foreground;
	sf::Text							label_title;
	sf::Text							label_search;

	Menu();
	Menu( std::string _t );
	void add			( MenuItem _add );
	void set_position	( int _x, int _y );
	void set_size		( int _w, int _h );
	void event			(sf::Event e);
	void enable			();
	void disable		();
	void hide			();
	void unhide			();
	void render			();
	void render_hidden	( int _x, int _y, int _w, int _h );
	void clear			();
};


/******************************************************************************************/
// Text Input
class CommandBox{
 public:
	int x;
	int y;
	int width;
	int height;
	int number_of_guesses;
	int scroll;
	int selected;

	std::string				search_term;;
	// autocomplete function
	std::vector< Command > *commands;
	std::vector< Command >  commands_shown;
	// visuals
	sf::RectangleShape		backdrop;
	sf::RectangleShape		backdrop_commands;
	sf::Text				label_search;
	std::vector< Label > 	guesses;


	CommandBox();
	void event		( sf::Event _e );
	void render		();
	void update		();
	void set		(std::vector<Command> *_c);
	void enable		();
	void disable	();

};


#endif
