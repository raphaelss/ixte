/**
* Ixte - a musical temporal structure editor for musical composition and analysis
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

#ifndef COMMAND_HPP_XTS_INCLUDED
#define COMMAND_HPP_XTS_INCLUDED
#include <memory>
#include "graphic_system.hpp"

namespace ixte {

class command {
public:
	enum type {
		MKLINE, RMLINE, MKPOINT, RMPOINT, GROUP
	};
	virtual ~command() = 0;
	virtual void execute(graphic_system &sys) const = 0;
	virtual void execute_reverse(graphic_system &sys) const;
	virtual type cmd_type() const = 0;
	
	static std::unique_ptr<command> combine
	    (std::unique_ptr<command> &&lhs, std::unique_ptr<command> &&rhs);
};

}

#endif
