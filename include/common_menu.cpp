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

void MenuItem::create(std::string _name, void (*_callback)(std::string)){
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

void MenuItem::trigger(){
	callback( callback_param );
}

// ------------------------------------------------------------------ //

void temp_callback(std::string a){
	std::cout << a << "\n";
}


Menu::Menu(){
	std::cout << "created a menu\n";
	// start off with an empty menu, until new objects are added to it.
	items 		= new MenuItem[0];
	items_len 	= 0;

	x_full 		= 100;
	y_full 		= 100;
	width_full 	= 100;
	height_full = 100;
	is_shown 	= false;
	item_offset = 0;
	num_of_items_shown = 15;
	selected_index = 0;


	scroll(0);

	add( "helo", temp_callback, "hello" );
	add( "helo_asd", temp_callback, "hello2" );
	add( "helo_3", temp_callback, "hello2" );
	add( "helo_p4", temp_callback, "hello2" );
	add( "helo_asdlonger", temp_callback, "hello2" );
	add( "helo_im a cat", temp_callback, "hello2" );
	add( "1", temp_callback, "hello2" );
	add( "2", temp_callback, "hello2" );
	add( "3", temp_callback, "hello2" );
	add( "4", temp_callback, "hello2" );
	add( "5", temp_callback, "hello2" );
	add( "6", temp_callback, "hello2" );
	add( "7", temp_callback, "hello2" );
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
		glColor3f( 1,1,1 );
		glBegin( GL_QUADS );
			glVertex3f( x, y, 0 );
			glVertex3f( x + width, y, 0 );
			glVertex3f( x + width, y + height, 0 );
			glVertex3f( x, y + height, 0 );
		glEnd();

		float _start_x = x;
		float _start_y = y + height;

		int temp_mult = 0;
		for( int i = item_offset; i <= item_offset + num_of_items_shown && i < items_len; i++ ){
			items[i].render( _start_x, _start_y - (temp_mult * height_per_item), 0 );
			temp_mult += 1;
		}
	}
}

void Menu::set_pos( int _x, int _y ){
	x_full = _x;
	y_full = _y;

	reshape();
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
}

void Menu::hide(){
	is_shown = false;
}

void Menu::toggle_show(){
	is_shown = !is_shown;
}

void Menu::scroll( int _s ){
	item_offset += _s;
	if( item_offset > num_of_items_shown - 7 ){
		item_offset = num_of_items_shown - 7;
	}else if( item_offset < 0 ){
		item_offset = 0;
	}
}

void Menu::add( std::string _name, void (*_callback)(std::string), std::string _param ){
	// reallocate and move memory to bigger items array
	MenuItem * temp = new MenuItem[items_len + 1];
	std::copy( items, items + items_len, temp );
	delete[] items;
	items = temp;

	items[ items_len ] = MenuItem();
	items[ items_len ].create( _name, _callback );
	items[ items_len ].set_param( _param );

	items_len += 1;
}

// ----------------------------------------------------------------------------- //

void Menu::key_press_special( unsigned char _key, int _x, int _y ){
	if( is_shown ){
		if( (int)_key == 101 ){						// up
			selected_index -= 1;
		}else if( (int)_key == 103 ){				// dowm
			selected_index += 1;
		}
	}

	// bounds checking
	if( selected_index < 0 ){
		selected_index = 0;
	}else if( selected_index >= items_len ){
		selected_index = items_len - 1;
	}

	update_draw();
}

void Menu::key_press( unsigned char _key, int _x, int _y ){
	if( is_shown ){
		if( (int)_key == 13 ){						// ENTER Key
			items[selected_index].trigger();
			is_shown = false;
		}
	}
}

void Menu::mouse_press( int _button, int _state, int _x, int _y ){
	std::cout << "MOUSE MENU: " << _button << " " << _x << " " << _y << "\n";
	if( is_shown ){
	}
}

void Menu::mouse_move_passive( int _x, int _y ){
	// is the mouse inside the menu ?
	if( is_shown == true && Common::check_inside_rect( _x, _y, x_full, y_full, width_full, height_full )){
		// which item is it hoevering over ?
		int temp_selected_index = num_of_items_shown - (int)(((float)(_y - y_full)/(height_full)) * num_of_items_shown);
		temp_selected_index += item_offset;
		for( int i = 0; i < items_len; i++ ){
			items[i].selected = false;
		}
		items[ temp_selected_index ].selected = true;
		selected_index = temp_selected_index;
	}

}

void Menu::mouse_move_active( int _x, int _y ){
	std::cout << "move a MENU " << _x << " " << _y << "\n";
}


void Menu::update_draw(){

	if( selected_index > item_offset + num_of_items_shown ){
		item_offset = selected_index - num_of_items_shown ;

	}else if( selected_index < item_offset ){
		item_offset = selected_index;
	}

	for( int i = 0; i < items_len; i++ ){
		items[i].selected = false;
	}
	items[ selected_index ].selected = true;
}

// ----------------------------------------------------------------------------- //

unsigned char Menu::get_shortcut(){ return shortcut; }

