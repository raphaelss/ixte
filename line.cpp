#include "line.hpp"

namespace xts {

bool line::add(double x) {
	bool had = contains(x);
	_set.insert(x);
	return !had;
}

bool line::remove(double x) {
	bool had = contains(x);
	_set.erase(x);
	return had;
}

bool line::empty() const {
	return _set.empty();
}

bool line::contains(double x) const {
	return _set.count(x);
}

double line::largest() const {
	if (empty()) {
		return -1;
	}
	return *(_set.crbegin());
}

line::const_iterator line::cbegin() const {
	return _set.cbegin();
}

line::const_iterator line::cend() const {
	return _set.cend();
}

line::const_iterator line::lower_bound(double x) const {
	return _set.lower_bound(x);
}

line::const_iterator line::upper_bound(double x) const {
	return _set.upper_bound(x);
}


std::pair<line::const_iterator, line::const_iterator>
line::range(double min, double max) const {
	return std::make_pair<line::const_iterator, line::const_iterator>(
			lower_bound(min), upper_bound(max)
	);
}

}
