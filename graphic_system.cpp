#include "graphic_system.hpp"
#include "config.hpp"
#include <algorithm>
#include <fstream>

namespace xts {

const double label_margin = 50;
const double inter_line_padding = 60;
const double label_line_padding = 20;
const double point_circle_radius = 3;

graphic_system::graphic_system(const ruler &ruler_arg, sf::Font &font, error_msgr &msgr)
    : _system(), _ruler(ruler_arg), _point_circle(point_circle_radius), _modified(false),
    _modified_noticed(false), _exit(false), _error_msgr(msgr) {
	_label_text.setFont(font);
	_label_text.setColor(quasi_black);
	_label_text.setCharacterSize(13);
	_line_rect.setFillColor(sf::Color(128, 128, 128));
	_line_rect.setOrigin(0, line_width / 2);
	_point_circle.setFillColor(quasi_black);
	_point_circle.setOrigin(point_circle_radius, point_circle_radius);
}

void graphic_system::resized() {
	_line_rect.setSize(_ruler.line_size());
}

void graphic_system::snapshot() {
	//TODO
}

void graphic_system::undo() {
	//TODO
}

void graphic_system::redo() {
	//TODO
}

void graphic_system::mkline(std::vector<std::string> labels) {
	labels.erase(_system.batch_add_mod(labels.begin(), labels.end()), labels.end());
}

void graphic_system::rmline(std::vector <std::string> labels) {
	labels.erase(_system.batch_remove_mod(labels.begin(), labels.end()), labels.end());
}

void graphic_system::mkpoint(std::string label, std::vector<double> points) {
	try {
		line &line = _system.get_line(label);
		points.erase(line.batch_add_mod(points.begin(), points.end()), points.end());
	} catch (std::out_of_range &e) {
		_error_msgr("mkpoint error: line " + label + " does not exist");
	}
}

void graphic_system::rmpoint(std::string label, std::vector<double> points) {
	try {
		line &line = _system.get_line(label);
		points.erase(line.batch_remove_mod(points.begin(), points.end()), points.end());
	} catch (std::out_of_range &e) {
		_error_msgr("mkpoint error: line " + label + " does not exist");
	}
}

void graphic_system::dump() const {
}

void dump_line(std::ofstream &fout, const std::string &label, const line &line) {
	auto it = line.cbegin(), end = line.cend();
	if (it == end) {
		return;
	}
	fout << label;
	for (auto it = line.cbegin(), end = line.cend(); it != end; ++it) {
		fout << ' '<< *it;
	}
	fout << std::endl;
}

void graphic_system::dump(std::string path) const {
	auto it = _system.cbegin(), end = _system.cend();
	if (it == end) {
		return;
	}
	std::ofstream fout(path);
	fout << "mkline";
	for (; it != end; ++it) {
		fout << ' ' << it->first;
	}
	fout << std::endl;
	for (it = _system.cbegin(); it != end; ++it) {
		dump_line(fout, it->first, it->second);
	}
}

void graphic_system::dump(std::string path, std::vector<std::string> lines) const {
}

double graphic_system::time_length() const {
	return _system.time_length();
}

void graphic_system::exit() {
	if (_modified_noticed) {
		_exit = true;
	} else if (_modified) {
		_error_msgr("Modifications were not dumped to file.");
		_modified_noticed = true;
	} else {
		_exit = true;
	}
}

bool graphic_system::should_exit() const {
	return _exit;
}

void graphic_system::draw_label(sf::RenderTarget &target, const std::string &str, double y) {
	_label_text.setString(str);
	auto bounds = _label_text.getLocalBounds();
	_label_text.setPosition(label_margin - bounds.width,
	    y - bounds.height / 2.0 - line_width * 1.5);
	target.draw(_label_text);
}

void graphic_system::draw_single_line(sf::RenderTarget &target, double y) {
	_line_rect.setPosition(_ruler.line_begin_x(), y);
	target.draw(_line_rect);
}

void graphic_system::draw_points(sf::RenderTarget &target, line::const_iterator begin,
    line::const_iterator end, double y) {
	for (; begin != end; ++begin) {
		_point_circle.setPosition(_ruler.get_pos_of(*begin), y);
		target.draw(_point_circle);
	}
}

void graphic_system::draw(sf::RenderTarget &target) {
	double y = _ruler.line_first_y();
	for (auto i = _system.cbegin(), end = _system.cend(); i != end; ++i) {
		draw_label(target, i->first, y);
		draw_single_line(target, y);
		auto pair = i->second.range(_ruler.left_t(), _ruler.right_t());
		draw_points(target, pair.first, pair.second, y);
		y += inter_line_padding;
	}
}

}
