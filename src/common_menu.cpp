#include "../include/common.h"
#include "../include/Managers.h"


// -------- Menu Item --------
void MenuItem::origin(){
	label = "un-named";
	backdrop = sf::RectangleShape( sf::Vector2f( 0, 0 ) );
	backdrop.setFillColor( COLOR_PRIMARY );
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	selected = false;
	type = NOTHING;
	data = NULL;

	// visuals
	label_text.setString( label );
	label_text.setFont( MAIN_FONT );
	label_text.setCharacterSize( 20 );
	label_text.setPosition( 100, 100 );
	label_text.setColor( COLOR_BLACK );
}


MenuItem::MenuItem(){
	origin();
}

MenuItem::MenuItem( std::string _t ){
	origin();
	label = _t;
}

MenuItem::MenuItem( std::string _t, std::function<void(void*)> _func ){
	origin();
	label = _t;
	setTrigger( _func );
}

MenuItem::MenuItem( std::string _t, std::function <void(void*)> _func, Menu* _m ){
	origin();
	label = _t;
	setTrigger( _func, _m);
}

void MenuItem::update(){
	// bg
	backdrop.setPosition( x, y);
	backdrop.setSize( sf::Vector2f(width, height * 0.95) );

	// label
	label_text.setString( label );
	label_text.setFont( MAIN_FONT );
	label_text.setCharacterSize( 20 );
	label_text.setPosition( x + width * 0.05, y );
	// icon
	icon_folder.setTexture( ICON_FOLDER );
	icon_folder.setPosition( x + width * 0.9, y );
	icon_folder.setScale( height * 0.8 / ICON_FOLDER.getSize().x, height * 0.8 / ICON_FOLDER.getSize().y );


	if( selected == false ){
		label_text.setColor( COLOR_BLACK );
		backdrop.setFillColor( sf::Color::Transparent );
	}else{
		label_text.setColor( COLOR_WHITE );
		backdrop.setFillColor( COLOR_PRIMARY_PALE );
	}

	if( type == NOTHING && selected == false ){
		backdrop.setFillColor( COLOR_GREY );
	}
}

void MenuItem::setLabel( std::string _label ){
	label = _label;
	update();
}

void MenuItem::setCaption( std::string _caption ){
	caption = _caption;
	update();
}

void MenuItem::setTrigger( std::function <void(void*)> _func ){
	trigger = _func;
	type = TRIGGER_FUNCTION;
}

void MenuItem::setTrigger( std::function <void(void*)> _func, Menu* _m ){
	trigger = _func;
	type = OPEN_MENU;
	open_menu = _m;
}

void MenuItem::setData( void* _d ){
	data = _d;
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

void MenuItem::call(){
	if( type == OPEN_MENU ){
		std::cout << "OPEN MENU\n";
		open_menu->enable();
		trigger( data );

	}else if( type == TRIGGER_FUNCTION ){
		trigger( data );
	}
}

void MenuItem::render(){
	// bg
	window.draw( backdrop );
	// label
	window.draw( label_text );
	// icon
	if( type == OPEN_MENU ){
		window.draw( icon_folder );
	}
}



// -------------- Menu --------------------
void Menu::origin(){
	title = "un-named";
	search_term = "";
	x = 100;
		y = 100;
	width = 200;
	height = 300;

	// visuals
	backdrop 	= sf::RectangleShape( sf::Vector2f(width, height * 0.8) );
	backdrop.setPosition( x, y + height * 0.1 );
	backdrop.setFillColor( COLOR_SECONDARY_1_PALE );
	backdrop.setOutlineColor( COLOR_SECONDARY_1 );
	backdrop.setOutlineThickness(2);

	label_title.setString( title );
	label_title.setFont( MAIN_FONT );
	label_title.setCharacterSize( 20 );
	label_title.setPosition( x, y );
	label_title.setColor( COLOR_BLACK );

	label_search.setString( search_term );
	label_search.setFont( MAIN_FONT );
	label_search.setCharacterSize( 20 );
	label_search.setPosition( x, y );
	label_search.setColor( COLOR_BLACK );
	// end visuals

	selected	= false;
	active		= true;
	scroll		= 0;
	number_of_items_visible = 10;
	height_per_item = (height * 0.8) / number_of_items_visible;
	selected_index 	= 0;
	update_search();
	update_displays();
	update_positions();
}

Menu::Menu( ){
	origin();
}

Menu::Menu( std::string _t ){
	origin();
	title 		= _t;
	update_search();
	update_displays();
	update_positions();
}

void Menu::render(){
	window.draw( backdrop );
	window.draw( label_title );
	window.draw( label_search );
	for( int i = scroll; i < scroll + number_of_items_visible && i < contents.size(); i++ ){
		contents[i].render();
	}
}

void Menu::render_hidden( int _x, int _y, int _w, int _h ){
	backdrop.setPosition( _x, _y );
	backdrop.setSize( sf::Vector2f(_w, _h) );
	window.draw( backdrop );
	label_title.setPosition( _x + _w/2 - label_title.getLocalBounds().width/2, _y - label_title.getLocalBounds().height + _h/2 );
	window.draw( label_title );
}

void Menu::set_position( int _x, int _y ){
	x = _x;
	y = _y;
	update_displays();
}

void Menu::set_size( int _w, int _h ){
	width = _w;
	height = _h;
	height_per_item = (height * 0.8) / number_of_items_visible;
	update_displays();
	update_positions();
}

void Menu::add( MenuItem _a ){
	// NOTE(suli) ~~~
	// there will be 2 type of menu items. Those that launch a task, and those that open another menu.
	// we want to make sure those are different and placed in order. 
	//	opening other menues is on top
	//	running task is on bottom
	//	both parts are in alphabetical order.
	contents_full.push_back( _a );
}

void Menu::update_search(){
	if( search_term.length() == 0 ){
		contents = contents_full;
	}else{
		contents.clear();
		for( int i = 0; i < contents_full.size(); i++){
			if(  contents_full[i].label.size() >= search_term.size()
				 && common::toLower(contents_full[i].label.substr(0, search_term.size())) == search_term ){
				contents.push_back( contents_full[i] );
			}
		}

	}
}

void Menu::update_displays(){
	backdrop.setPosition( x, y );
	backdrop.setSize( sf::Vector2f( width, height ) );

	label_title.setString( title );
	label_title.setFont( MAIN_FONT );
	label_title.setCharacterSize( 20 );
	label_title.setPosition( x - label_title.getLocalBounds().width/2 + width/2, y );
	label_title.setColor( COLOR_BLACK );

	label_search.setString( search_term );
	label_search.setFont( MAIN_FONT );
	label_search.setCharacterSize( 20 );
	label_search.setPosition( x, y + height * 0.9 + label_search.getLocalBounds().height/2 );
	label_search.setColor( COLOR_BLACK );
}

void Menu::update_positions(){
	// scroll through the elements starting at the current scroll value.
	if( selected_index >= 7 ){
		scroll = selected_index - 7;
	}else{
		scroll = 0;
	}

	int j = 0;
	for( int i = scroll; i < contents.size(); i++ ){
		contents[i].select( false );
		contents[i].set_position( x, y + j * height_per_item + height * 0.1 );
		contents[i].set_size( width, height_per_item );
		j += 1;
	}

	if( selected_index < contents.size() && selected_index >= 0 ){
		contents[ selected_index ].select( true );
	}
}

void Menu::event( sf::Event e ){
	switch( e.type ){
		case sf::Event::KeyPressed:
			// ARROW UP
			if( e.key.code == sf::Keyboard::Up ){
				if( selected_index > 0 )
					selected_index -= 1;

			// ARROW DOWN
			}else if( e.key.code == sf::Keyboard::Down ){
				if( selected_index < contents.size() - 1 )
					selected_index += 1;

			// ARROW LEFT
			}else if( e.key.code == sf::Keyboard::Left ){

			// ARROW RIGHT
			}else if( e.key.code == sf::Keyboard::Right ){
				if( contents.size() > 0 && selected_index < contents.size() && contents[ selected_index ].type == OPEN_MENU ){
					this->hide();
					contents[ selected_index ].call();
				}

			//ESCAPE
			}else if( e.key.code == sf::Keyboard::Escape ){
				guiManager.clear();
				search_term.erase();

			// ALPHABETS
			}else if( e.key.code >= sf::Keyboard::A && e.key.code <= sf::Keyboard::Z ){
				search_term += (char)(e.key.code - sf::Keyboard::A + 'a');

			// NUMBERS 0 - 9
			}else if( e.key.code >= sf::Keyboard::Num0 && e.key.code <= sf::Keyboard::Num9 ){
				search_term += (char)(e.key.code - sf::Keyboard::Num0 + '0');

			// NUMPAD 0 - 9
			}else if( e.key.code >= sf::Keyboard::Numpad0 && e.key.code <= sf::Keyboard::Numpad9 ){
				search_term += (char)( e.key.code - sf::Keyboard::Numpad0 + '0');

			// SPACE
			}else if( e.key.code == sf::Keyboard::Space ){
				search_term += " ";

			// BACKSPACE
			}else if( e.key.code == sf::Keyboard::BackSpace ){
				if( search_term.length() > 0 ){
					search_term.pop_back();
				}else{
					guiManager.reverse_menu();
				}

			// ENTER
			}else if( e.key.code == sf::Keyboard::Return ){
				if( contents.size() > 0 && selected_index < contents.size() && contents[ selected_index ].type == OPEN_MENU ){
					this->hide();
					contents[ selected_index ].call();
				}else if( contents[ selected_index ].type != NOTHING ){
					contents[ selected_index ].call();
					this->disable();
				}
			}

			update_search();
			update_positions();
			update_displays();
			break;

		default:
			break;
	}
}

void Menu::enable(){
	update_search();
	update_positions();
	update_displays();
	guiManager.enable( this );
}

void Menu::disable(){
	guiManager.disable(this);
	input_buffer.clear();
}

void Menu::hide(){
	guiManager.hide(this);
}

void Menu::unhide(){
	update_search();
	update_positions();
	update_displays();
}
