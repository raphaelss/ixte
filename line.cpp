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

#include "line.hpp"

namespace ixte {

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
