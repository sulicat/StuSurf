#include "../include/common.h"
#include "../include/Managers.h"


OptionInput::OptionInput(){
	defaultSettings();

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
	isCustomSize	= false;
	isPermenant		= false;
}

void OptionInput::updateVisuals(){
	backdrop.setSize( sf::Vector2f(width, height));
	backdrop.setPosition( x, y );
}

void OptionInput::setIntercept( bool _b ){
	isIntercept = _b;
}

void OptionInput::render(){
	window.draw( backdrop );
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
	if( isCustomSize == false ){
		x 		= 1 * window.getSize().x / 3;
		width 	= window.getSize().x / 3;
		y 		= window.getSize().y / 4;
		height	= window.getSize().y / 2;

		// visuals
		backdrop.setSize( sf::Vector2f( width, height ) );
		backdrop.setPosition( x, y );
	}
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
		}
	}

}
