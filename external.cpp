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

#include "external.hpp"

namespace ixte {

namespace asio = boost::asio;

external::external(error_msgr &msgr, boost::asio::io_service &io_serv)
    : _out_pipe(), _in_pipe(), _err_pipe(),
    _out(io_serv, _out_pipe.read_end()),
    _in(io_serv, _in_pipe.write_end()),
    _err(io_serv, _err_pipe.read_end()) {}

bool external::child_redirect_stdstreams() const {
	return (_out_pipe.dup_write_end(STDOUT_FILENO) &&
	    _in_pipe.dup_read_end(STDIN_FILENO) &&
	    _err_pipe.dup_write_end(STDERR_FILENO));
}

void external::parent_close_unused_pipes() {
	_out_pipe.close_write_end();
	_in_pipe.close_read_end();
	_err_pipe.close_write_end();
}

void external::write(const std::string &str) {
	asio::write(_in, asio::buffer(str));
}

}
