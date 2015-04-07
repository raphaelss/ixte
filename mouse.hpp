#ifndef MOUSE_HPP_XTS_INCLUDED
#define MOUSE_HPP_XTS_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include "ruler.hpp"

namespace xts {

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
