#ifndef GUI_HPP_XTS_INCLUDED
#define GUI_HPP_XTS_INCLUDED
#include <string>
#include <SFML/Graphics.hpp>
#include "error_msgr.hpp"
#include "text_buffer.hpp"
#include "ruler.hpp"
#include "mouse.hpp"
#include "graphic_system.hpp"
#include "processor.hpp"

namespace xts {

class gui {
public:
	gui();

	void run();

private:
	void resized(double x, double y);
	void key_pressed(sf::Keyboard::Key key);

	void draw_lines();
	void draw();

	sf::RenderWindow _window;
	sf::Font _font;
	error_msgr _error_msgr;
	ruler _ruler;
	graphic_system _system;
	processor _proc;
	text_buffer _text_buffer;
	mouse _mouse;
};

}

#endif
