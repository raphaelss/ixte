#include "system.hpp"
#include <algorithm>
#include <stdexcept>

namespace xts {

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
