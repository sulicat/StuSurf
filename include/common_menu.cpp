#include <GL/glut.h>
#include "common.h"


MenuItem::MenuItem( ){
	x_full				= 0;
	y_full				= 0;
	width_full			= 10;
	height_full			= 10;
	text_size			= 0.65;
	text_margin_left	= 0.05;
	text_margin_bottom	= 0.25;
	selected 			= false;
	reshape();
}

void MenuItem::create(std::string _name, int (*_callback)(std::string)){
	name = _name;
	callback = _callback;
	reshape();
}

void MenuItem::render( float _x, float _y, float _z ){
	float x_start = x + _x + 1;
	float y_start = y + _y + 1;

	if( selected ){
		glColor3f(1.0, 0.0, 0.0);
	}else{
		glColor3f(1.0, 1.0, 1.0);
	}


	glBegin( GL_QUADS );
		glVertex3f( x_start,			y_start, 					_z );
		glVertex3f( x_start + width, 	y_start, 					_z );
		glVertex3f( x_start + width, 	y_start + height * 0.9, 	_z );
		glVertex3f( x_start, 			y_start + height * 0.9, 	_z );
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	Common::render_string( 	x_start + width * text_margin_left,
							y_start + height * text_margin_bottom,
							height * text_size,
							name );

}

void MenuItem::reshape(){
	x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
	y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
	width 		= (2*(float)width_full/WINDOW_WIDTH);
	height 		= (2*(float)height_full/WINDOW_HEIGHT);
}


void MenuItem::set_size( int _w, int _h ){
	width_full = _w;
	height_full = _h;
	reshape();
}

void MenuItem::set_height( int _h ){
	height_full = _h;
	reshape();
}

void MenuItem::set_param( std::string _p ){
	callback_param = _p;
}

int MenuItem::trigger(){
	return callback( callback_param );
}

// ------------------------------------------------------------------ //

int temp_callback(std::string a){
	std::cout << a << "\n";
	return 1;
}


Menu::Menu(){
	std::cout << "created a menu\n";
	// start off with an empty menu, until new objects are added to it.
	items 			= new MenuItem[0];
	items_len 		= 0;
	items_full 		= new MenuItem[0];
	items_full_len 	= 0;
	name			= "untitled";

	x_full 		= 100;
	y_full 		= 100;
	width_full 	= 100;
	height_full = 100;
	is_shown 	= false;
	item_offset = 0;
	num_of_items_shown = 15;
	selected_index = 0;
	scroll_speed = 10;
	scroll_counter = 0;

	last_mouse_active_hold_x = 0;
	last_mouse_active_hold_y = 0;
	search_term = "";

	outside_scroll_speed = 0.01;


	select(selected_index);

}

void Menu::reshape( ){
	x 			= (2*(float)x_full/WINDOW_WIDTH) - 1;
	y 			= (2*(float)y_full/WINDOW_HEIGHT) - 1;
	width 		= (2*(float)width_full/WINDOW_WIDTH);
	height 		= (2*(float)height_full/WINDOW_HEIGHT);

	// we will calculate the size of every item.
	height_per_item_full 	= height_full/num_of_items_shown;
	height_per_item			= height/num_of_items_shown;

	// must reshape all list items, so they update their sizes
	for( int i = 0; i < items_len; i++ ){
		items[i].set_size( width_full, height_per_item_full );
		items[i].reshape();
	}
}

void Menu::render(){
	if( is_shown ){
		// background rect
		glColor3f( 1,1,1 );
		glBegin( GL_QUADS );
			glVertex3f( x, y, 0 );
			glVertex3f( x + width, y, 0 );
			glVertex3f( x + width, y + height, 0 );
			glVertex3f( x, y + height, 0 );
		glEnd();

		// menu title
		glBegin( GL_QUADS );
			glVertex3f( x,			y + height * 1.18,		0 );
			glVertex3f( x + width, 	y + height * 1.18,		0 );
			glVertex3f( x + width, 	y + height * 1.32, 		0 );
			glVertex3f( x,			y + height * 1.32,		0 );
		glEnd();
		Common::render_string( x + width * 0.05, y + height*1.2, height * 0.1, name, 1.0, 0.0, 0.0 );

		// render a scroll bar
		//	related to item_offset
		//	items_len
		float sbar_x = x - width*0.03;
		float sbar_y = y + height + height_per_item/2;
		float sbar_width = width*0.01;
		float sbar_height = - height;

		glColor3f(1.0, 1.0, 1.0);
		glBegin( GL_QUADS );
			glVertex3f( sbar_x,					sbar_y,						0 );
			glVertex3f( sbar_x + sbar_width,	sbar_y,						0 );
			glVertex3f( sbar_x + sbar_width,	sbar_y + sbar_height,		0 );
			glVertex3f( sbar_x,					sbar_y + sbar_height,		0 );
		glEnd();

		if( !(items_len < num_of_items_shown) && items_len > 0){
			sbar_height = 	sbar_height/(items_len - num_of_items_shown);
			sbar_y 		-=  (height/(items_len - num_of_items_shown)) * item_offset;
		}
		glColor3f(1.0, 0.0, 0.0);
		glBegin( GL_QUADS );
			glVertex3f( sbar_x,					sbar_y,						0 );
			glVertex3f( sbar_x + sbar_width,	sbar_y,						0 );
			glVertex3f( sbar_x + sbar_width,	sbar_y + sbar_height,		0 );
			glVertex3f( sbar_x,					sbar_y + sbar_height,		0 );
		glEnd();

		float _start_x = x;
		float _start_y = y + height;

		int temp_mult = 0;
		for( int i = item_offset; i <= item_offset + num_of_items_shown && i < items_len; i++ ){
			items[i].render( _start_x, _start_y - (temp_mult * height_per_item), 0 );
			temp_mult += 1;
		}
		// we now want to render the search string
		Common::render_string( x + width*1.1 , y, height * 0.2, search_term, 1, 0, 0 );
	}
}

void Menu::set_pos( int _x, int _y ){
	x_full = _x;
	y_full = _y;

	reshape();
}

void Menu::set_name( std::string _n ){
	name = _n;
}

void Menu::select( int _i ){
	for( int i = 0; i < items_len; i++ ){
		items[i].selected = false;
	}

	if( _i < items_len && _i >= 0 ){
		items[_i].selected = true;
		// scrolling
		if( _i > item_offset + num_of_items_shown ){
			item_offset += 1;
		}else if( _i < item_offset ){
			item_offset -= 1;
		}
	}
}

void Menu::scroll( int _x ){

	if( items_len > num_of_items_shown ){
		if( scroll_counter > scroll_speed ){
			item_offset += _x;
			// check bounds of the offset
			if( item_offset + num_of_items_shown + 1 > items_len ){
				item_offset = items_len - num_of_items_shown - 1;

			}else if( item_offset < 0 ){
				item_offset = 0;
			}
			scroll_counter = 0;
		}else{ scroll_counter += 1; }
	}
}

void Menu::set_number_of_items( int _n ){
	num_of_items_shown = _n;
	reshape();
}

void Menu::set_height( int _h ){
	height_full = _h;
	reshape();
}

void Menu::set_width( int _w ){
	width_full = _w;
	reshape();
}

void Menu::set_shortcut( unsigned char _c ){
	shortcut = _c;
}

void Menu::show(){
	is_shown = true;
	refill_items();
	search_term = "";
}

void Menu::hide(){
	is_shown = false;
	refill_items();
	search_term = "";
}

void Menu::toggle_show(){
	is_shown = !is_shown;
	refill_items();
	search_term = "";
}

void Menu::add( std::string _name, int (*_callback)(std::string), std::string _param ){
	// reallocate and move memory to bigger items array
	MenuItem * temp = new MenuItem[items_len + 1];
	std::copy( items, items + items_len, temp );
	delete[] items;
	items = temp;

	items[ items_len ] = MenuItem();
	items[ items_len ].create( _name, _callback );
	items[ items_len ].set_param( _param );

	items_len += 1;

	items_full = items;
	items_full_len = items_len;
}

void Menu::trigger(){
	if( selected_index < items_len && selected_index >= 0 ){
		if( items[ selected_index ].trigger() == 1 ){
			is_shown = false;
		}
	}
}

// ----------------------------------------------------------------------------- //

void Menu::key_press_special( unsigned char _key, int _x, int _y ){
	if( is_shown ){
		if( (int)_key == 101 ){						// up
			selected_index -= 1;

		}else if( (int)_key == 103 ){				// down
			selected_index += 1;
		}

		// bound check the index.
		// 	stop at top and bottom of the list
		if( selected_index < 0 ){
			selected_index = 0;
		}else if( selected_index >= items_len ){
			selected_index = items_len - 1;
		}
		select( selected_index );

	}
}

void Menu::key_press( unsigned char _key, int _x, int _y ){
	if( is_shown ){
		if( (int)_key == 13 ){								// ENTER Key
			trigger();

		}else if( (int)_key > 31 && (int)_key < 127 ){		// every printable keyboard charecter
			search_term += _key;
			selected_index = 0;
			select( selected_index );
			search();

		}else if( (int)_key == 8 ){							// backspace
			if( search_term.length() > 0 ){
				search_term = search_term.substr( 0, search_term.length()-1 );
				selected_index = 0;
				select( selected_index );
				search();
			}
		}

	}
}

void Menu::mouse_press( int _button, int _state, int _x, int _y ){
	if( is_shown && _button == 0 && _state == 0 ){
		// only trigger if mouse pressed inside the menu
		if( Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ) ){
			trigger( );
		}
		last_mouse_active_hold_x = _x;
		last_mouse_active_hold_y = _y;
	}
}

void Menu::mouse_move_passive( int _x, int _y ){
	// is the mouse inside the menu ?
	if( is_shown == true && Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full )){
		// which item is it hoevering over ?
		int temp_selected_index = num_of_items_shown - (int)(((float)(_y - y_full)/(height_full + height_per_item)) * (num_of_items_shown + 1 ));
		temp_selected_index += item_offset;
		for( int i = 0; i < items_len; i++ ){
			items[i].selected = false;
		}

		selected_index = temp_selected_index;
		select( temp_selected_index );
	}
}

void Menu::mouse_move_active( int _x, int _y ){
	if( is_shown && !(Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full ))){
		scroll( (last_mouse_active_hold_y - _y) * outside_scroll_speed );
	}
}


void Menu::search(){
	refill_items();
	if( search_term.length() > 0 ){
		for( int i = 0; i < items_len; i++ ){
			if( !(items[i].name.substr( 0,search_term.length() ) == search_term) ){
				pop_item( i );
				i -= 1;
			}
		}
	}

}

void Menu::refill_items(){
	items = items_full;
	items_len = items_full_len;
}

void Menu::pop_item( int _i ){
	if( items_len > 0 && _i < items_len ){
		MenuItem * temp	= new MenuItem[ items_len - 1 ];
		std::copy( items, items + _i, temp );
		std::copy( items + _i + 1, items + items_len, temp + _i );
		items = temp;
		items_len -= 1;
	}
}



// ----------------------------------------------------------------------------- //

unsigned char Menu::get_shortcut(){
	return shortcut;
}

