#ifndef LINE_HPP_XTS_INCLUDED
#define LINE_HPP_XTS_INCLUDED
#include <set>
#include <algorithm>

namespace xts {

class line {
public:
	typedef std::set<double>::const_iterator const_iterator;

	bool add(double x);
	bool remove(double x);
	bool empty() const;
	bool contains(double x) const;
	double largest() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	const_iterator lower_bound(double x = 0) const;
	const_iterator upper_bound(double x) const;
	std::pair<const_iterator,const_iterator> range(double min, double max) const;

	template <class Iter>
	Iter batch_add_mod(Iter begin, Iter end) {
		return std::remove_if(begin, end, [this](double x) {
			return !this->add(x);
		});
	}
	
	template <class Iter >
	Iter batch_remove_mod(Iter begin, Iter end) {
		return std::remove_if(begin, end, [this](double x) {
			return !this->remove(x);
		});
	}
	
	template <class Iter>
	void batch_add(Iter begin, Iter end) {
		std::for_each(begin, end, [this](double x) {
			this->add(x);
		});
	}
	
	template <class Iter >
	void batch_remove(Iter begin, Iter end) {
		std::for_each(begin, end, [this](double x) {
			this->remove(x);
		});
	}

private:
	std::set<double> _set;
};

}

#endif
