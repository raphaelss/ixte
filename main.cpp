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

#include <iostream>
#include "gui.hpp"

int main() {
  std::cout
    << "Ixte Copyright (C) 2015  Raphael Sousa Santos, http://raphaelss.com/\n"
    << "This program comes with ABSOLUTELY NO WARRANTY.\n"
    << "This is free software, and you are welcome to redistribute it\n"
    << "under certain conditions.\n"
    << "You should have received a copy of the GNU General Public License\n"
    << "along with this program.  If not, see http://www.gnu.org/licenses/.\n";
  ixte::gui app;
  app.run();
  return 0;
}
