/**
* Xts - a musical temporal structure editor for musical composition and analysis
* Copyright (C) 2015  Raphael Santos, http://www.raphaelss.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef TEXT_BUFFER_HPP_INCLUDED
#define TEXT_BUFFER_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "processor.hpp"

namespace xts {

class text_buffer {
public:
	text_buffer(int size, sf::Font &font, processor &proc);
	void resized(double width, double height);
	void insert(sf::Uint32 ch);
	bool active() const;
	void keypress(sf::Keyboard::Key key);
	void draw(sf::RenderTarget &target);

private:
	void reset();
	void backspace();
	void delete_char();
	void right();
	void left();
	void execute();

	std::size_t _cursor;
	sf::String _buffer, _single_char;
	sf::Text _text;
	sf::Vertex _cursor_line [2];
	processor &_processor;
};

}

#endif
