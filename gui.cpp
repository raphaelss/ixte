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

#include "gui.hpp"
#include <algorithm>
#include "config.hpp"

namespace xts {

const char *const font_path = "assets/FreeSans.ttf";

gui::gui()
    : _window(sf::VideoMode(800, 600), "xts"), _font(), _error_msgr(), _ruler(line_width, _font),
    _system(_ruler, _font, _error_msgr), _proc(_system, _error_msgr),
    _text_buffer(13, _font, _proc), _mouse(_ruler, _font) {
	_window.setFramerateLimit(60);
	_font.loadFromFile(font_path);
	auto size = _window.getSize();
	resized(size.x, size.y);
	auto mouse_pos = sf::Mouse::getPosition(_window);
	_mouse.update_position(mouse_pos.x, mouse_pos.y);
}

void gui::run() {
	while (_window.isOpen()) {
		sf::Event event;
		while (_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				_proc.request_exit();
				break;
			case sf::Event::Resized:
				resized(event.size.width, event.size.height);
				break;
			case sf::Event::TextEntered:
				_text_buffer.insert(event.text.unicode);
				break;
			case sf::Event::KeyPressed:
				if (_text_buffer.active()) {
					_text_buffer.keypress(event.key.code);
				} else {
					key_pressed(event.key.code);
				}
				break;
			case sf::Event::MouseMoved:
				_mouse.update_position(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseEntered:
				_mouse.on(true);
				break;
			case sf::Event::MouseLeft:
				_mouse.on(false);
				break;
			default:
				break;
			}
		}
		if (_system.should_exit()) {
			_window.close();
			continue;
		}
		_window.clear(background);
		draw();
		_window.display();
	}
}

void gui::resized(double x, double y) {
	_window.setView(sf::View(sf::FloatRect(0, 0, x, y)));
	_ruler.resized(x, y);
	_system.resized();
	_text_buffer.resized(x, y);
	_mouse.update_t();
}

void gui::key_pressed(sf::Keyboard::Key key) {
	switch(key) {
	case sf::Keyboard::Up:
		_ruler.zoom(1);
		break;
	case sf::Keyboard::Down:
		_ruler.zoom(-1);
		break;
	case sf::Keyboard::Num0:
		_ruler.zoom_reset();
		break;
	case sf::Keyboard::Left:
		_ruler.move(0.5);
		break;
	case sf::Keyboard::Right:
		_ruler.move(-0.5);
		break;
	case sf::Keyboard::Home:
		_ruler.move_to(0);
		break;
	case sf::Keyboard::End:
		_ruler.move_to_right_on(_system.time_length());
		break;
	case sf::Keyboard::U:
		_system.undo();
		break;
	case sf::Keyboard::R:
		_system.redo();
		break;
	default:
		break;
	}
	_mouse.update_t();
}

void gui::draw() {
	_ruler.draw(_window);
	_system.draw(_window);
	_text_buffer.draw(_window);
	_mouse.draw(_window);
}

}
