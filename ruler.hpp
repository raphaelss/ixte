// Ixte - a temporal structure editor for musical composition and analysis
// Copyright (C) 2014 Raphael Sousa Santos, http://www.raphaelss.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RULER_HPP_IXTE_INCLUDED
#define RULER_HPP_IXTE_INCLUDED
#include <string>
#include <SFML/Graphics.hpp>

namespace ixte {

class ruler {
public:
  ruler(double line_width, sf::Font &font);
  void zoom(int i);
  void zoom_reset();
  void resized(double width, double height);
  void move_to(double t);
  void move_to_right_on(double t);
  void move(double x);
  void draw(sf::RenderTarget &target);

  sf::Vector2f line_size() const;
  double line_first_y() const;
  double line_begin_x() const;
  double line_end_x() const;
  double left_t() const;
  double right_t() const;
  double get_time_at(double pos) const;
  double get_pos_of(double t) const;

private:
  void update_last_t();
  double time_span() const;

  sf::RectangleShape _ruler_rect, _ruler_mark_rect;
  sf::Text _number_text;
  sf::Vertex _grid_line [2];
  std::string _tmp_str;
  double _y, _line_end, _mark_offset;
  double _left_t, _right_t;
  int _zoom_i;
};

}

#endif
