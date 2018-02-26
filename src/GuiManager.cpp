#include "../include/GuiManager.h"

GuiManager::GuiManager(){
}


// Menu addition/subtractions
//**************************************************************
void GuiManager::enable( Menu* _m ){
	for( int i = 0; i < menus.size(); i++ ){
		if( menus[i] == _m ){
			menus.erase( menus.begin() + i );
		}
	}
	_m->set_position( menus.size() * MENU_WIDTH, 0 );
	_m->set_size( MENU_WIDTH, MENU_HEIGHT );
	menus.push_back( _m );
	std::cout << "ADDED: " << _m->title << " len: " << menus.size() << "\n";
}

void GuiManager::disable( Menu* _m ){
	for( int i = 0; i < menus.size(); i++ ){
		if( menus[i] == _m ){
			menus.erase( menus.begin() + i );
		}
	}
	std::cout << "\tDISABLING MENU: " << _m->title << "\n";
}

void GuiManager::hide( Menu* _m ){
	disable( _m );

	// remove menu_item from main list
	for( int i = 0; i < menus.size(); i++ ){
		if( menus[i] == _m ){
			menus.erase( menus.begin() + i );
		}
	}
	// make sure no copies of it are in hidden list
	for( int i = 0; i < menus_hidden.size(); i++ ){
		if( menus_hidden[i] == _m ){
			menus_hidden.erase( menus_hidden.begin() + i );
		}
	}
	// add it to the hidden list
	menus_hidden.push_back( _m );
}


// Textbox addition/subtractions
//**************************************************************
void GuiManager::enable( CommandBox* _m ){
	for( int i = 0; i < textBoxes.size(); i++ ){
		if( textBoxes[i] == _m ){
			textBoxes.erase( textBoxes.begin() + i );
		}
	}
	textBoxes.push_back( _m );
}


void GuiManager::disable( CommandBox* _m ){
	for( int i = 0; i < textBoxes.size(); i++ ){
		if( textBoxes[i] == _m ){
			textBoxes.erase( textBoxes.begin() + i );
		}
	}
}

//**************************************************************

void GuiManager::clear(){
	for( int i = 0; i < menus.size(); i++ )
		menus[i]->search_term.erase();

	for( int i = 0; i < menus_hidden.size(); i++ )
		menus_hidden[i]->search_term.erase();

	menus.clear();
	menus_hidden.clear();
	textBoxes.clear();
	input_buffer.clear();
}

bool GuiManager::is_intercepting_input(){
	if( menus.size() > 0 )
		return true;
	if( textBoxes.size() > 0 )
		return true;

	return false;
}

void GuiManager::input( sf::Event _e ){
	// menus
	for( int i = 0; i < menus.size(); i++ ){
		menus[i]->event( _e );
	}
	// textBoxes
	for( int i = 0; i < textBoxes.size(); i++ ){
		textBoxes[i]->event( _e );
	}
}

void GuiManager::reverse_menu(){
	if( menus_hidden.size() > 0 ){
		menus.clear();
		menus.push_back( menus_hidden[ menus_hidden.size()-1 ] );
		menus_hidden.pop_back();
	}
	for( int i = 0; i < menus.size(); i++ ){
		menus[i]->unhide();
	}
}

void GuiManager::render(){
	int _x, _y, _w, _h;
	_w = window.getSize().x * 0.1;
	_h = window.getSize().y * 0.1;

	for( int i = 0; i < menus_hidden.size(); i++ ){
		_x = i * _w * 0.2;
		_y = window.getSize().y -_h - (i) * _h * 0.2;

		menus_hidden[i]->render_hidden( _x, _y, _w, _h );
	}

	for( int i = 0; i < menus.size(); i++ ){
		menus[i]->render();
	}

	for( int i = 0; i < textBoxes.size(); i++ ){
		textBoxes[i]->render();
	}
}
