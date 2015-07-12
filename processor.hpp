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

#ifndef PROCESSOR_HPP_IXTE_INCLUDED
#define PROCESSOR_HPP_IXTE_INCLUDED
#include <string>
#include <vector>
#include <thread>
#include "graphic_system.hpp"
#include "error_msgr.hpp"
#include "external.hpp"
#include <boost/asio.hpp>
#include <mutex>

namespace ixte {

class processor {
public:
  processor(graphic_system &sys, error_msgr &msgr);
  ~processor();

  void request_exit();
  void execute(std::string str);

private:
  bool dispatch(std::string str);
  void exit_cmd(std::string &args);
  void save_cmd(std::string &args);
  void bind_cmd(std::string &args);
  void mkline_cmd(std::string &args);
  void rmline_cmd(std::string &args);
  void mkpoint_cmd(std::string &args);
  void rmpoint_cmd(std::string &args);
  bool external_cmd(std::string &cmd, std::string &args);

  bool has_running_external();
  void write_to_external(const std::string &str);
  void push_external(external &&ext);
  void pop_external();
  void async_external_read();

  graphic_system &_system;
  error_msgr &_error_msgr;
  boost::asio::io_service _io_serv;
  std::thread _worker_thread;
  std::vector<external> _running_externals;
  std::mutex _externals_lock;
};

}

#endif
