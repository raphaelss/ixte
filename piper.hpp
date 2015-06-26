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

#ifndef PIPER_HPP_XTS_INCLUDED
#define PIPER_HPP_XTS_INCLUDED

namespace ixte {

class piper {
public:
  piper();
  piper(const piper &other)  = delete;
  piper(piper &&p) noexcept;
  ~piper() noexcept;

  piper &operator=(const piper &p) = delete;
  piper &operator=(piper &&p) noexcept;

  bool dup_read_end(int pid) const;
  bool dup_write_end(int pid) const;

  int read_end() const;
  int write_end() const;

  void close_read_end();
  void close_write_end();

private:
  void closefd(int &x);
  int pipefd[2];
};

}

#endif
