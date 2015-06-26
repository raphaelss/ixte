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

#ifndef SYSTEM_HPP_XTS_INCLUDED
#define SYSTEM_HPP_XTS_INCLUDED
#include <vector>
#include <utility>
#include <string>
#include "line.hpp"

namespace ixte {

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
