#include "../include/common.h"



// -------- Menu Item --------
void MenuItem::origin(){
	std::cout << "created a menu item\n";
	label = "un-named";
	backdrop = sf::RectangleShape( sf::Vector2f( 0, 0 ) );
	backdrop.setFillColor( COLOR_PRIMARY );
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	selected = false;

	// visuals
	label_text.setString( label );
	label_text.setFont( MAIN_FONT );
	label_text.setCharacterSize( 20 );
	label_text.setPosition( 100, 100 );
}


MenuItem::MenuItem(){
	origin();
}

MenuItem::MenuItem( std::string _t ){
	origin();
	label = _t;
}

void MenuItem::update(){
	// bg
	backdrop.setPosition( x, y );
	backdrop.setSize( sf::Vector2f(width, height * 0.95) );
	backdrop.setFillColor( COLOR_PRIMARY_PALE );
	// label
	label_text.setString( label );
	label_text.setFont( MAIN_FONT );
	label_text.setCharacterSize( 20 );
	label_text.setPosition( x + width * 0.05, y );
	if( selected == false )
		label_text.setColor( COLOR_BLACK );
	else
		label_text.setColor( COLOR_WHITE );
}

void MenuItem::setLabel( std::string _label ){
	label = _label;
	update();
}

void MenuItem::setCaption( std::string _caption ){
	caption = _caption;
	update();
}


void MenuItem::setTrigger( std::function< void(std::string) > _func ){
	trigger = _func;
}

void MenuItem::set_position( float _x, float _y ){
	x = (int)_x;
	y = (int)_y;
	update();
}

void MenuItem::set_size( float _w, float _h ){
	width = _w;
	height = _h;
	update();
}

void MenuItem::select( bool _b ){
	selected = _b;
	update();
}

void MenuItem::render(){
	// bg
	window.draw( backdrop );
	// label
	label_text.setStyle(sf::Text::Bold);
	window.draw( label_text );
}



// -------------- Menu --------------------
void Menu::origin(){
	title = "un-named";
	x = 0;
	y = 0;
	width = 200;
	height = 300;
	backdrop 	= sf::RectangleShape( sf::Vector2f(width, height) );
	backdrop.setPosition( x, y );
	backdrop.setFillColor( COLOR_SECONDARY_1_PALE );
	backdrop.setOutlineColor( COLOR_SECONDARY_1 );
	backdrop.setOutlineThickness(2);
	selected	= false;
	active		= true;
	scroll		= 0;
	number_of_items_visible = 10;
	height_per_item = height / number_of_items_visible;
	update_positions();
	selected_index = 0;
}

Menu::Menu( ){
	origin();
}

Menu::Menu( std::string _t ){
	origin();
	title 		= _t;
}

void Menu::render(){
	window.draw( backdrop );
	for( int i = scroll; i < scroll + number_of_items_visible && i < contents.size(); i++ ){
		contents[i].render();
	}
}

void Menu::set_position( int _x, int _y ){
	x = _x;
	y = _y;
	backdrop.setPosition( x, y );
}

void Menu::set_size( int _w, int _h ){
	width = _w;
	height = _h;
	height_per_item = height / number_of_items_visible;
}

void Menu::add( MenuItem _a ){
	contents.push_back(_a);
	update_positions();
}


void Menu::update_positions(){
	// scroll through the elements starting at the current scroll value.
	int j = 0;
	for( int i = scroll; i < contents.size(); i++ ){
		contents[i].select( false );
		contents[i].set_position( x, y + j * height_per_item );
		contents[i].set_size( width, height_per_item );
		j += 1;
	}

	if( selected_index < contents.size() && selected_index >= 0 ){
		contents[ selected_index ].select( true );
	}
}
