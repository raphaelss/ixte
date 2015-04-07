#include "ruler.hpp"
#include "config.hpp"
#include <array>

namespace xts {

const double top_margin = 50;
const double left_margin = 60;
const double right_margin = 50;
const double bot_margin = 50;
const double mark_pixel_spacing = 100;
const std::array<double, 21> zoom_values =
    {40.0, 20.0, 10.0, 7.5, 5.0, 3.0, 2.5, 2, 1.5, 1.25,
     1.0,
     0.75, 0.5, 0.4, 0.3, 0.25, 0.15, 0.1, 0.05, 0.025, 0.01};
const int zoom_reset_index = 10;
const int zoom_last_i = 20;


/* helper */
static double map_range(double x, double a1, double a2, double b1, double b2) {
  return b1 + (((x - a1) / (a2 - a1)) * (b2 - b1));
}

ruler::ruler(double line_width, sf::Font &font)
    : _ruler_rect(), _ruler_mark_rect(), _number_text(),
      _grid_line({sf::Vertex(sf::Vector2f(0, 0), light_grey),
                  sf::Vertex(sf::Vector2f(0, 0), light_grey)}),
      _tmp_str(), _y(-1), _mark_offset(line_width / 2), _left_t(0),
      _right_t(-1), _zoom_i(zoom_reset_index) {
  _number_text.setColor(quasi_black);
  _number_text.setCharacterSize(12);
  _number_text.setFont(font);
  _ruler_rect.setFillColor(quasi_black);
  _ruler_rect.setOrigin(0, line_width / 2);
  _ruler_mark_rect.setFillColor(quasi_black);
  _ruler_mark_rect.setSize(sf::Vector2f(line_width, line_width * 3));
  _ruler_mark_rect.setOrigin(0, line_width * 3);
}

void ruler::zoom(int i) {
  _zoom_i = std::min<int>(std::max<int>(_zoom_i + i, 0), zoom_last_i);
  update_last_t();
}

void ruler::zoom_reset() {
  _zoom_i = zoom_reset_index;
  update_last_t();
}

double ruler::line_first_y() const {
  return top_margin;
}

void ruler::resized(double width, double height) {
  _y = height - bot_margin;
  double line_size = width - right_margin - left_margin;
  _line_end = line_size + left_margin;
  auto size_vec = sf::Vector2f(line_size, line_width);
  _ruler_rect.setPosition(left_margin, _y);
  _ruler_rect.setSize(size_vec);
  update_last_t();
}

void ruler::move_to(double t) {
  _left_t = std::max<double>(t, 0);
  update_last_t();
}

void ruler::move_to_right_on(double t) {
  move_to(t - time_span());
}

void ruler::move(double x) {
  move_to(_left_t - zoom_values[_zoom_i] * x);
}

void ruler::draw(sf::RenderTarget &target) {
  target.draw(_ruler_rect);
  for (double x = left_margin; x <= _line_end; x += mark_pixel_spacing) {
    _ruler_mark_rect.setPosition(x, _y);
    double line_x = x + _mark_offset;
    _grid_line[0].position = sf::Vector2f(line_x, _y);
    _grid_line[1].position = sf::Vector2f(line_x, top_margin);
    _tmp_str = std::to_string(get_time_at(x));
    _tmp_str.erase(_tmp_str.find_last_not_of('0') + 1, std::string::npos);
    _number_text.setString(_tmp_str);
    _number_text.setPosition(x, _y + 10);
    target.draw(_grid_line, 2, sf::Lines);
    target.draw(_ruler_mark_rect);
    target.draw(_number_text);
  }
}

sf::Vector2f ruler::line_size() const {
  return _ruler_rect.getSize();
}

double ruler::line_begin_x() const {
  return left_margin;
}

double ruler::line_end_x() const {
  return _line_end;
}


double ruler::left_t() const {
  return _left_t;
}

double ruler::right_t() const {
  return _right_t;
}

double ruler::get_time_at(double pos) const {
  return map_range(pos, left_margin, _line_end, _left_t, _right_t);
}

double ruler::get_pos_of(double t) const {
  return map_range(t, _left_t, _right_t, left_margin, _line_end);
}

double ruler::time_span() const {
  return (_line_end - left_margin) / mark_pixel_spacing * zoom_values[_zoom_i];
}

void ruler::update_last_t() {
  _right_t = time_span() + _left_t;
}

}
