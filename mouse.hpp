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

#ifndef MOUSE_HPP_XTS_INCLUDED
#define MOUSE_HPP_XTS_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include "ruler.hpp"

namespace ixte {

class mouse {
public:
  mouse(const ruler &ruler_arg, sf::Font &font);

  void update_t();
  void update_position(double x, double y);
  void on(bool x);
  void draw(sf::RenderTarget &target);

private:
  const ruler &_ruler;
  double _x, _y, _t_pos;
  bool _on, _in_line;
  std::string _str;
  sf::Text _text;
};

}

#endif
