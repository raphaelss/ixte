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

#include "text_buffer.hpp"
#include <algorithm>
#include <string>
#include "config.hpp"

namespace xts {

const double left_margin = 10;
const double bot_margin = 20;

text_buffer::text_buffer(int size, sf::Font &font, processor &proc)
    : _cursor(0), _buffer(), _single_char('\0'), _text(),
    _cursor_line{sf::Vertex(sf::Vector2f(0, 0), quasi_black), sf::Vertex(sf::Vector2f(0, 0), quasi_black)},
    _processor(proc) {
	_text.setCharacterSize(size);
	_text.setColor(quasi_black);
	_text.setFont(font);
}

void text_buffer::resized(double width, double height) {
	_text.setPosition(left_margin, height - bot_margin);
}

void text_buffer::insert(sf::Uint32 ch) {
	if (!active() && ch != '\u003A') { //:
		return;
	}
	switch (ch) {
	case '\u000D': //\r
	case '\u000A': //\n
		execute();
		//FALLTHROUGH
	case '\u001B': //ESC
		reset();
		return;
	case '\u0008': //BACKSPACE
		backspace();
		return;
	case '\u007F': //DELETE
		delete_char();
		return;
	default:
		break;
	}
	_single_char[0] = ch;
	if (_cursor == _buffer.getSize()) {
		_buffer += _single_char;
	} else {
		_buffer.insert(_cursor, _single_char);
	}
	++_cursor;
}

bool text_buffer::active() const {
	return _cursor || _buffer.getSize();
}

void text_buffer::keypress(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Left:
		left();
		break;
	case sf::Keyboard::Right:
		right();
		break;
	case sf::Keyboard::Home:
		_cursor = 1;
		break;
	case sf::Keyboard::End:
		_cursor = _buffer.getSize();
		break;
	default:
		break;
	}
}

void text_buffer::draw(sf::RenderTarget &target) {
	if (active()) {
		sf::Vector2f char_pos = _text.findCharacterPos(_cursor);
		_cursor_line[0].position = char_pos;
		char_pos.y += 15;
		_cursor_line[1].position = char_pos;
		_text.setString(_buffer);
		target.draw(_text);
		target.draw(_cursor_line, 2, sf::Lines);
	}
}

void text_buffer::reset() {
	_cursor = 0;
	_buffer.clear();
}

void text_buffer::backspace() {
	if (_cursor > 1 || (_cursor && _buffer.getSize() ==1)) {
		_buffer.erase(--_cursor, 1);
	}
}

void text_buffer::delete_char() {
	if (_cursor != _buffer.getSize()) {
		_buffer.erase(_cursor, 1);
	}
}

void text_buffer::right() {
	_cursor = std::min<int>(_cursor + 1, _buffer.getSize());
}

void text_buffer::left() {
	if (_cursor > 1) {
		--_cursor;
	}
}

void text_buffer::execute() {
	if (_buffer.getSize()  > 1) {
		std::string tmp;
		sf::Utf32::toUtf8(_buffer.begin() + 1, _buffer.end(), std::back_inserter(tmp));
		_processor.execute(std::move(tmp));
	}
}

}
