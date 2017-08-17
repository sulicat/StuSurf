#ifndef COMMON_H
#define COMMON_H

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

#include <iostream>
#include <sstream>
#include <functional>

// this is the common file. It will include the base class that the main modules can inherit from.
// first we make an abstract class. If we want to make a button, we can inherit from this class and define all the virtual functions we need.
class Base{
public:
	int 	x_full;
	int 	y_full;
	int 	width_full;
	int 	height_full;
	float 	x;
	float 	y;
	float 	width;
	float 	height;
	int   	ID;
	char * 	path_data;

	virtual void render() = 0;
	virtual void mouse_press( int _button, int _state, int _x, int _y  ) = 0;
	virtual void reshape() = 0;
	virtual void mouse_move_passive( int _x, int _y ) = 0;
	virtual void mouse_move_active( int _x, int _y ) = 0;
	virtual void key_press( unsigned char _key, int _x, int _y ) = 0;
	virtual void key_release( unsigned char _key, int _x, int _y ) = 0;
	virtual void key_press_special( unsigned char _key, int _x, int _y ) = 0;
	virtual void key_release_special( unsigned char _key, int _x, int _y ) = 0;
	virtual void set_path( char * _p ) = 0;
};


/*************************************************************************/

// these are some functions that can be used by the modules that need them
class Common{
public:

	class empty_module : public Base {
	public:
		int 	x_full;
		int 	y_full;
		float 	width_full;
		float 	height_full;
		float 	x;
		float 	y;
		float 	width;
		float 	height;
		int 	ID;
		char *	path_data;

		empty_module( ){
			std::cout << "creating an EMPTY MODULE\n";
			x_full 			= 0;
			y_full 			= 0;
			width_full 		= 0;
			height_full 	= 0;
		}

		// none of the functions do anything
		void reshape(){}
		void render(){}
		void mouse_press( int _button, int _state, int _x, int _y ){}
		void mouse_move_passive( int _x, int _y ){}
		void mouse_move_active( int _x, int _y ){}
		void key_press( unsigned char _key, int _x, int _y ){}
		void key_press_special( unsigned char _key, int _x, int _y ){ }
		void key_release( unsigned char _key, int _x, int _y ){}
		void key_release_special( unsigned char _key, int _x, int _y ){ }
		void set_path( char * _p ){}
	};

	// Vars | Functions tha can be used by the rest of the progra,

	static constexpr float		FONT_SIZE_ROMAN 			= 1/152.38;

		template <typename T>
	static T MIN( T _one, T _two ){ return ((_one < _two) ? _one : _two); }
		template <typename T>
	static T MAX( T _one, T _two ){ return ((_one > _two) ? _one : _two); }
		template <typename T>
	static T ABS( T _one ){ return ((_one < 0) ? -1 * _one : _one); }

   	static bool 			check_inside_rect	( int _x, int _y, int rect_x, int rect_y, int rect_width, int rect_height );
	static std::string 		int_to_string		( int _num );
	static int 				string_to_int		( std::string _input );
	static float 			string_to_float		( std::string _input );
	static std::string * 	split_string		( char * input, char delim  ); // the length is in retval[0] as a string
	static std::string * 	split_string		( std::string input, char delim  ); // the length is in retval[0] as a strin

	static void				render_char			( float x, float y, float scale, char c);
	static void				render_char			( float x, float y, float scale, char c, float R, float G, float B );

	static void				render_string		( float x, float y, float scale, std::string s );
	static void				render_string		( float x, float y, float scale, std::string s, float R, float G, float B );

	static void				render_paragraph	( float x, float y, float w, float h, float scale, std::string p );
	static void				render_paragraph	( float x, float y, float w, float h, float scale, std::string p, float R, float G, float B );

	static void				render_paragraph	( float x, float y, float w, float h, float scale, std::string p, float _line_spacing );
	static void				render_paragraph	( float x, float y, float w, float h, float scale, std::string p, float _line_spacing, float R, float G, float B);
};


class MenuItem{
public:
	std::string 	name;
	std::function<int(std::string)>	callback;
	std::string		callback_param;
	int				x_full;
	int				y_full;
	int 			width_full;
	int 			height_full;
	float			x;
	float			y;
	float 			width;
	float 			height;
	float			text_size;
	float			text_margin_left;
	float			text_margin_bottom;
	bool			selected;

			MenuItem( );
	void 	create( std::string _name, std::function<int(std::string)> _callback  );
	void	render( float _x, float _y, float _z );
	void	reshape();
	void	set_size( int _w, int _h );
	void	set_height( int _h );
	void 	set_param( std::string _p );
	int 	trigger();

};


class Menu{
private:
	int last_mouse_active_hold_x;
	int last_mouse_active_hold_y;

public:
	float 	x;
	float 	y;
	float 	width;
	float 	height;
	int 	x_full;
	int		y_full;
	int		width_full;
	int		height_full;
	bool	is_shown;

	int 	num_of_items_shown;
	int		height_per_item_full;
	float 	height_per_item;
	int 	item_offset;
	int		selected_index;
	float	outside_scroll_speed;
	int 	scroll_speed;
	int		scroll_counter;


	std::string		name;
	unsigned char 	shortcut;
	std::string		search_term;

	MenuItem * 	items;
	int			items_len;
	MenuItem * 	items_full;
	int			items_full_len;

				Menu();
	void 		render();
	void		set_pos( float x, float y );
	void 		set_pos( int x, int y );
	void		set_width( float w );
	void		set_name( std::string _name );
	void		reshape();
	void		show();
	void		hide();
	void		toggle_show();
	void		add( std::string _name, std::function<int(std::string _c)>, std::string _callback_param );
	void		select( int _index );
	void		set_number_of_items( int _n );
	void		set_height( int _h );
	void 		set_width( int _w );
	void		set_shortcut( unsigned char c );
	void		mouse_move_passive( int _x, int _y );
	void		mouse_move_active( int _x, int _y );
	void		mouse_press( int _button, int _state, int _x, int _y );
	void 		key_press( unsigned char _key, int _x, int _y );
	void 		key_press_special( unsigned char _key, int _x, int _y );
	void		scroll( int _ammount );
	void		search();
	void		refill_items();
	void		pop_item( int _i );
	void		trigger();

	unsigned char	get_shortcut();

};


#endif
