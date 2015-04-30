/**
* Ixte - a temporal structure editor for musical composition and analysis
* Copyright (C) 2015  Raphael Sousa Santos, http://www.raphaelss.com
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

namespace ixte {

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
