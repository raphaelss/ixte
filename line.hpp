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

#ifndef LINE_HPP_IXTE_INCLUDED
#define LINE_HPP_IXTE_INCLUDED
#include <set>
#include <algorithm>

namespace ixte {

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
