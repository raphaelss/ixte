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

#ifndef GRAPHIC_SYSTEM_HPP_IXTE_INCLUDED
#define GRAPHIC_SYSTEM_HPP_IXTE_INCLUDED
#include <string>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "system.hpp"
#include "ruler.hpp"
#include "error_msgr.hpp"

namespace ixte {

class graphic_system {
public:
  graphic_system(const ruler &ruler_arg, sf::Font &font, error_msgr &msgr);

  void resized();
  void draw(sf::RenderTarget &target);

  void undo();
  void redo();

  void mkline(std::vector<std::string> labels);
  void rmline(std::vector <std::string> labels);
  void mkpoint(std::string label, std::vector<double> points);
  void rmpoint(std::string label, std::vector<double> points);

  void save();
  void bind(std::string path);

  double time_length();

  void exit();
  bool should_exit();

private:
  void draw_label(sf::RenderTarget &target, const std::string &str, double y);
  void draw_single_line(sf::RenderTarget &target, double y);
  void draw_points(sf::RenderTarget &target, line::const_iterator begin,
      line::const_iterator end, double y);

  void modified();

  std::mutex _lock;
  system _system;
  const ruler &_ruler;
  sf::Text _label_text;
  sf::RectangleShape _line_rect;
  sf::CircleShape _point_circle;
  bool _modified, _modified_noticed, _exit;
  error_msgr &_error_msgr;
  std::string _current_file;
};

}
#endif
