/**
* Ixte - a temporal structure editor for musical composition and analysis
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

#include "piper.hpp"
#include <algorithm>
#include <sys/types.h>
#include <unistd.h>

namespace ixte {

piper::piper(): pipefd{-1, -1} {
  if (pipe(pipefd) < 0) {
    throw -1;
  }
}

piper::piper(piper &&p) noexcept
    : pipefd {p.pipefd[0], p.pipefd[1]} {
  p.pipefd[0] = p.pipefd[1] = -1;
}

piper::~piper() noexcept {
  close_read_end();
  close_write_end();
}

piper &piper::operator=(piper &&p) noexcept {
  if (this != &p) {
    this->pipefd[0] = p.pipefd[0];
    this->pipefd[1] = p.pipefd[1];
    p.pipefd[0] = p.pipefd[1] = -1;
  }
  return *this;
}

bool piper::dup_read_end(int pid) const {
  return dup2(pipefd[0], pid) >= 0;
}

bool piper::dup_write_end(int pid) const {
  return dup2(pipefd[1], pid) >= 0;
}

int piper::read_end() const {
  return pipefd[0];
}

int piper::write_end() const {
  return pipefd[1];
}

void piper::close_read_end() {
  closefd(pipefd[0]);
}

void piper::close_write_end() {
  closefd(pipefd[1]);
}

void piper::closefd(int &x) {
  if (x != -1) {
    close(x);
    x = -1;
  }
}

}
