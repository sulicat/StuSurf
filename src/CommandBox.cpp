#include "../include/common.h"
#include "../include/Managers.h"


CommandBox::CommandBox( ){
	number_of_guesses = 10;
	scroll = 0;
	label_search.setString( "" );
	selected = -1;
	commands = new std::vector<Command>;
	update();
}

void CommandBox::render(){
	window.draw( backdrop );
	//	window.draw( backdrop_commands );
  	label_search.setStyle(sf::Text::Bold );

	for( int i = 0; i < guesses.size(); i++ ){
		guesses[i].render();
	}
	window.draw( label_search );
}

void CommandBox::enable(){
	guiManager.enable(this);
	update();
}

void CommandBox::disable(){
	guiManager.disable(this);
	search_term = "";
	update();
}

void CommandBox::update(){
	int x = 10;
	int y = window.getSize().y - 40;
	int width = window.getSize().x - 20;
	float height = window.getSize().y * 0.03;
	label_search.setString( search_term );

	backdrop = sf::RectangleShape( sf::Vector2f(width,height) );
	backdrop.setPosition( x, y );
	backdrop.setFillColor( COLOR_CommandBox_1 );

	backdrop_commands = sf::RectangleShape( sf::Vector2f( width, window.getSize().y * 0.4) );
	backdrop_commands.setPosition( x, y - height - 10 - window.getSize().y * 0.4 );
	backdrop_commands.setFillColor( COLOR_CommandBox_1 );

	label_search.setColor( COLOR_CommandBox_2 );
	label_search.setFont( MAIN_FONT );
	label_search.setCharacterSize( 20 );
	label_search.setPosition( x + 10, y );

	int temp_h = (window.getSize().y * 0.4) / number_of_guesses;

	guesses.clear();
	commands_shown.clear();
	if( search_term.size() <= 0 ){
		for( int i = scroll; i < number_of_guesses + scroll && i < commands->size(); i++ ){
			guesses.push_back( Label( (*commands)[i].name, x, y - height - 10 - (i-scroll + 1) * temp_h, width, temp_h ) );
			commands_shown.push_back( (*commands)[i] );
		}

	}else{

		int count = 0;
		for( int i = 0; i < commands->size() && guesses.size() < number_of_guesses; i++ ){
			if( (*commands)[i].name.compare( 0, search_term.size(), search_term ) == 0 ){
				if( count >= scroll ){
					guesses.push_back( Label( (*commands)[i].name, x, y - height - 10 - (guesses.size() + 1) * temp_h, width, temp_h ) );
					commands_shown.push_back( (*commands)[i] );
				}
				count += 1;
			}
		}

	}

	if( guesses.size() > 0 )
		guesses[0].select();


}

void CommandBox::set( std::vector<Command> *_c ){
	commands = _c;
	commands_shown = *_c;
}

void CommandBox::event( sf::Event e ){
	switch( e.type ){
		case sf::Event::KeyPressed:
			// ARROW UP
			if( e.key.code == sf::Keyboard::Up ){
				if( scroll < commands->size() )
					scroll += 1;
			// ARROW DOWN
			}else if( e.key.code == sf::Keyboard::Down ){
				if( scroll > 0 )
					scroll -= 1;

			// ARROW LEFT
			}else if( e.key.code == sf::Keyboard::Left ){

			// ARROW RIGHT
			}else if( e.key.code == sf::Keyboard::Right ){

			//ESCAPE
			}else if( e.key.code == sf::Keyboard::Escape ){
				scroll = 0;
				search_term = "";
				guiManager.clear();

			// ALPHABETS
			}else if( e.key.code >= sf::Keyboard::A && e.key.code <= sf::Keyboard::Z ){
				search_term += (char)(e.key.code - sf::Keyboard::A + 'a');
				scroll = 0;

			// NUMBERS 0 - 9
			}else if( e.key.code >= sf::Keyboard::Num0 && e.key.code <= sf::Keyboard::Num9 ){
				search_term += (char)(e.key.code - sf::Keyboard::Num0 + '0');
				scroll = 0;

			// NUMPAD 0 - 9
			}else if( e.key.code >= sf::Keyboard::Numpad0 && e.key.code <= sf::Keyboard::Numpad9 ){
				search_term += (char)( e.key.code - sf::Keyboard::Numpad0 + '0');
				scroll = 0;

			// SPACE
			}else if( e.key.code == sf::Keyboard::Space ){
				search_term += " ";
				scroll = 0;

			// BACKSPACE
			}else if( e.key.code == sf::Keyboard::BackSpace ){
				if( search_term.length() > 0 ){
					search_term.pop_back();
				}

			// ENTER
			}else if( e.key.code == sf::Keyboard::Return ){
				if( commands_shown.size() > 0 && scroll >= 0){
					commands_shown[0].call( );
				}

				/*else if( commands->size() > 0 && scroll >= 0 && scroll < commands->size() ){
					(*commands)[scroll].call();
					}*/
			}

			update();
			break;

		default:
			break;
	}
}
