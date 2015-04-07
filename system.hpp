#ifndef SYSTEM_HPP_XTS_INCLUDED
#define	SYSTEM_HPP_XTS_INCLUDED
#include <vector>
#include <utility>
#include <string>
#include "line.hpp"

namespace xts {

class system {
public:
	typedef std::pair<std::string, line> entry;
	typedef std::vector<entry>::const_iterator const_iterator;

	bool make_line(std::string label);
	bool remove_line(const std::string &label);

	bool contains(const std::string &label) const;
	line &get_line(const std::string &label);

	double time_length() const;

	const_iterator find(const std::string &label) const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	
	template <class Iter>
	Iter batch_add_mod(Iter begin, Iter end) {
		return std::remove_if(begin, end, [this](const std::string &label) {
			return !this->make_line(label);
		});
	}
	
	template <class Iter>
	Iter batch_remove_mod(Iter begin, Iter end) {
		return std::remove_if(begin, end, [this](const std::string &label) {
			return !this->remove_line(label);
		});
	}
	
	template <class Iter>
	void batch_add(Iter begin, Iter end) {
		std::for_each(begin, end, [this](const std::string &label) {
			this->make_line(label);
		});
	}
	
	template <class Iter>
	void batch_remove(Iter begin, Iter end) {
		std::for_each(begin, end, [this](const std::string &label) {
			this->remove_line(label);
		});
	}

private:
	std::vector<entry> _lines;
};

}

#endif
