/**
* Ixte - a musical temporal structure editor for musical composition and analysis
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

#include "graphic_system.hpp"
#include "config.hpp"
#include <algorithm>
#include <fstream>

namespace ixte {

const double label_margin = 50;
const double inter_line_padding = 60;
const double point_circle_radius = 3;

//helper
void dump_line(std::ofstream &fout, const std::string &label, const line &line) {
	auto it = line.cbegin(), end = line.cend();
	if (it == end) {
		return;
	}
	fout << "mkpoint " << label;
	for (auto it = line.cbegin(), end = line.cend(); it != end; ++it) {
		fout << ' '<< *it;
	}
	fout << std::endl;
}

graphic_system::graphic_system(const ruler &ruler_arg, sf::Font &font, error_msgr &msgr)
    : _lock(), _system(), _ruler(ruler_arg), _point_circle(point_circle_radius), _modified(false),
    _modified_noticed(false), _exit(false), _error_msgr(msgr), _current_file() {
	_label_text.setFont(font);
	_label_text.setColor(quasi_black);
	_label_text.setCharacterSize(13);
	_line_rect.setFillColor(sf::Color(128, 128, 128));
	_line_rect.setOrigin(0, line_width / 2);
	_point_circle.setFillColor(quasi_black);
	_point_circle.setOrigin(point_circle_radius, point_circle_radius);
}

void graphic_system::resized() {
	std::lock_guard<std::mutex> guard(_lock);
	_line_rect.setSize(_ruler.line_size());
}

void graphic_system::undo() {
	std::lock_guard<std::mutex> guard(_lock);
	//TODO
}

void graphic_system::redo() {
	std::lock_guard<std::mutex> guard(_lock);
	//TODO
}

void graphic_system::mkline(std::vector<std::string> labels) {
	std::lock_guard<std::mutex> guard(_lock);
	labels.erase(_system.batch_add_mod(labels.begin(), labels.end()), labels.end());
	if (!labels.empty()) {
		modified();
	}
}

void graphic_system::rmline(std::vector <std::string> labels) {
	std::lock_guard<std::mutex> guard(_lock);
	labels.erase(_system.batch_remove_mod(labels.begin(), labels.end()), labels.end());
	if (!labels.empty()) {
		modified();
	}
}

void graphic_system::mkpoint(std::string label, std::vector<double> points) {
	std::lock_guard<std::mutex> guard(_lock);
	try {
		line &line = _system.get_line(label);
		points.erase(line.batch_add_mod(points.begin(), points.end()), points.end());
		if (!points.empty()) {
			modified();
		}
	} catch (std::out_of_range &e) {
		_error_msgr("mkpoint error: line " + label + " does not exist");
	}
}

void graphic_system::rmpoint(std::string label, std::vector<double> points) {
	std::lock_guard<std::mutex> guard(_lock);
	try {
		line &line = _system.get_line(label);
		points.erase(line.batch_remove_mod(points.begin(), points.end()), points.end());
		if(!points.empty()) {
			modified();
		}
	} catch (std::out_of_range &e) {
		_error_msgr("mkpoint error: line " + label + " does not exist");
	}
}

void graphic_system::save() {
	std::lock_guard<std::mutex> guard(_lock);
	if (_current_file.empty()) {
		_error_msgr("save error: no currently associated file.");
		return;
	}
	auto it = _system.cbegin(), end = _system.cend();
	if (it == end) {
		return;
	}
	std::ofstream fout(_current_file);
	fout << "mkline";
	for (; it != end; ++it) {
		fout << ' ' << it->first;
	}
	fout << std::endl;
	for (it = _system.cbegin(); it != end; ++it) {
		dump_line(fout, it->first, it->second);
	}
	_modified = _modified_noticed = false;
}

void graphic_system::bind(std::string path) {
	std::lock_guard<std::mutex> guard(_lock);
	_current_file = std::move(path);
}

double graphic_system::time_length() {
	std::lock_guard<std::mutex> guard(_lock);
	return _system.time_length();
}

void graphic_system::exit() {
	std::lock_guard<std::mutex> guard(_lock);
	if (_modified_noticed) {
		_exit = true;
	} else if (_modified) {
		_error_msgr("Modifications were not saved.");
		_modified_noticed = true;
	} else {
		_exit = true;
	}
}

bool graphic_system::should_exit() {
	std::lock_guard<std::mutex> guard(_lock);
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
	std::lock_guard<std::mutex> guard(_lock);
	double y = _ruler.line_first_y();
	for (auto i = _system.cbegin(), end = _system.cend(); i != end; ++i) {
		draw_label(target, i->first, y);
		draw_single_line(target, y);
		auto pair = i->second.range(_ruler.left_t(), _ruler.right_t());
		draw_points(target, pair.first, pair.second, y);
		y += inter_line_padding;
	}
}

void graphic_system::modified() {
	_modified = true;
	_modified_noticed = false;
}

}
