#include "../include/common.h"
#include "../include/Managers.h"


OptionInput::OptionInput(){
	defaultSettings();

	// start at center of screen? eh why not
	x 		= 2 * window.getSize().x / 3;
	width 	= window.getSize().x / 3;
	y 		= window.getSize().y / 4;
	height	= window.getSize().y / 2;

	updateVisuals();
}


OptionInput::OptionInput( int _x, int _y, int _w, int _h ){
	defaultSettings();
	x = _x;
	y = _y;
	width = _w;
	height = _h;
}

void OptionInput::defaultSettings(){
	isIntercept 	= true;
	isPermenant		= false;
	retainState		= false;
	number_of_items_shown = 10;
	scroll			= 0;
	current_selected = 0;
	resize_optional = [](int* _x, int* _y, int* _w, int* _h){};

	// visuals
	selected_outline.setFillColor( sf::Color(255, 0, 255, 0) );		// color
	selected_outline.setOutlineColor( COLOR_Menu_3 );				// color
	selected_outline.setOutlineThickness( 2 );
	backdrop.setFillColor( COLOR_Menu_1 );
	
}

void OptionInput::updateVisuals(){
	backdrop.setSize( sf::Vector2f(width, height));
	backdrop.setPosition( x, y );

	for( int i = scroll; i < inputs.size() && i < scroll + number_of_items_shown; i++ ){
		inputs[i]->x = x;
		inputs[i]->y = y + (height/number_of_items_shown)*(i - scroll);
		inputs[i]->width = width;
		inputs[i]->height = height / number_of_items_shown;
	}

	selected_outline.setPosition( x, y + (current_selected - scroll) * (height/number_of_items_shown) );
	selected_outline.setSize( sf::Vector2f(width, height/number_of_items_shown) );
}

void OptionInput::setIntercept( bool _b ){
	isIntercept = _b;
}

void OptionInput::add( Input_Base* _t ){
	inputs.push_back( std::unique_ptr<Input_Base>( _t ) );
}

void OptionInput::render(){
	window.draw( backdrop );

	for( int i = scroll; i < inputs.size() && i < scroll + number_of_items_shown; i++ ){
		inputs[i]->render();
	}

	window.draw( selected_outline );
}

void OptionInput::enable(){
	guiManager.enable( this );
}

void OptionInput::hide(){
	guiManager.hide(this);
}

void OptionInput::disable(){
	guiManager.disable( this );
}


void OptionInput::resize(){
	resize_optional( &x, &y, &width, &height );
	// visuals
	backdrop.setSize( sf::Vector2f( width, height ) );
	backdrop.setPosition( x, y );

	updateVisuals();
}

void OptionInput::setResize( std::function<void(int* _x, int* _y, int* _w, int* _h)> _f){
	resize_optional = _f;
}

void OptionInput::event( sf::Event _e ){
	// we will parse input here depending on whats going on in the input box
	if( _e.type == sf::Event::KeyPressed ){
		// ESCAPE
		if( _e.key.code == sf::Keyboard::Escape ){
			if( isPermenant == false )
				this->disable();
			else
				this->hide();
		// down
		}else if( _e.key.code == sf::Keyboard::Down ){
				current_selected += 1;
				if( current_selected > inputs.size() - 1 ){ current_selected = 0; scroll = 0;}
				if( current_selected > number_of_items_shown + scroll - 1 ){ scroll += 1; }

		// Up
		}else if( _e.key.code == sf::Keyboard::Up ){
				current_selected -= 1;
				if( current_selected < 0 ){ current_selected = inputs.size() - 1; scroll = inputs.size() - number_of_items_shown;}
				if( current_selected < scroll ){ scroll -= 1; }

		}else{
			if( current_selected >= 0 && current_selected < inputs.size() ){ 
				inputs[current_selected]->input( _e );
			}
		}
	}

	updateVisuals();

}
