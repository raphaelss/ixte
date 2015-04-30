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

#ifndef EXTERNAL_HPP_XTS_INCLUDED
#define EXTERNAL_HPP_XTS_INCLUDED
#include "error_msgr.hpp"
#include "piper.hpp"
#include <boost/asio.hpp>

namespace ixte {

class external {
public:
  external(error_msgr &msgr, boost::asio::io_service &io_serv);

  bool child_redirect_stdstreams() const;
  void parent_close_unused_pipes();
  void write(const std::string &str);

private:
  piper _out_pipe, _in_pipe, _err_pipe;
public:
  boost::asio::posix::stream_descriptor _out, _in, _err;
};

}

#endif
