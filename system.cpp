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

#include "system.hpp"
#include <algorithm>
#include <stdexcept>

namespace ixte {

struct match {
	match(const std::string &label): _label(label) {}
	bool operator()(const system::entry &e) {
		return e.first == _label;
	}
	const std::string &_label;
};

bool system::make_line(std::string label) {
	if (contains(label)) {
		return false;
	}
	_lines.push_back(std::make_pair<std::string, line>(std::move(label), line()));
	return true;
}

bool system::remove_line(const std::string &label) {
	const_iterator iter = find(label);
	if (iter == _lines.cend()) {
		return false;
	}
	_lines.erase(iter);
	return true;
}

bool system::contains(const std::string &label) const {
	return find(label) != _lines.cend();
}

line &system::get_line(const std::string &label) {
	auto iter = std::find_if(_lines.begin(), _lines.end(), match(label));
	if (iter == _lines.end()) {
		throw std::out_of_range(label);
	}
	return iter->second;
}

double system::time_length() const {
	double result = -1;
	for(auto iter = cbegin(), end = cend(); iter != end; ++iter) {
		result = std::max<double>(iter->second.largest(), result);
	}
	return result;
}

system::const_iterator system::find(const std::string &label) const {
	return std::find_if(_lines.cbegin(), _lines.cend(), match(label));
}

system::const_iterator system::cbegin() const {
	return _lines.cbegin();
}

system::const_iterator system::cend() const {
	return _lines.cend();
}

}
