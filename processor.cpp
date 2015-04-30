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

#include "processor.hpp"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

namespace ixte {

namespace asio = boost::asio;

// helper
static std::string split_first_token(std::string &str) {
  boost::trim_left(str);
  auto pos = str.find_first_of(" \t", 0);
  if (pos == std::string::npos) {
    std::string token = str;
    str.clear();
    return token;
  }
  std::string token = str.substr(0, pos);
  str.erase(0, pos + 1);
  return token;
}

void thread_fun(asio::io_service &io_serv) {
  asio::io_service::work work(io_serv);
  io_serv.run();
}

processor::processor(graphic_system &sys, error_msgr &msgr)
    : _system(sys), _error_msgr(msgr), _io_serv(),
    _worker_thread(thread_fun, std::ref(_io_serv)),
    _running_externals(), _externals_lock() {}

processor::~processor() {
  _io_serv.stop();
  if (_worker_thread.joinable()) {
    _worker_thread.join();
  }
}

void processor::request_exit() {
  _system.exit();
}

void processor::execute(std::string str) {
  {
    std::lock_guard<std::mutex> guard(_externals_lock);
    if (has_running_external()) {
      write_to_external(str);
      return;
    }
  }
  _io_serv.dispatch(boost::bind(&processor::dispatch,  this, str));
}

bool processor::dispatch(std::string str) {
  std::string cmd = split_first_token(str);
  if (cmd == "exit") {
    exit_cmd(str);
  } else if (cmd == "save") {
    save_cmd(str);
  } else if (cmd == "bind") {
    bind_cmd(str);
  } else if (cmd == "mkline") {
    mkline_cmd(str);
  } else if (cmd == "rmline") {
    rmline_cmd(str);
  } else if (cmd == "mkpoint") {
    mkpoint_cmd(str);
  } else if (cmd == "rmpoint") {
    rmpoint_cmd(str);
  } else {
    return external_cmd(cmd, str);
  }
  return false;
}

void processor::exit_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string tmp;
  if (ss >> tmp) {
    _error_msgr("exit error: too many parameters (expected 0).");
    return;
  }
  _system.exit();
}

void processor::save_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string tmp;
  if (ss >> tmp) {
    _error_msgr("save error: too many parameters (expected 0).");
    return;
  }
  _system.save();
}

void processor::bind_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string tmp;
  if (ss >> tmp) {
    _system.bind(std::move(tmp));
    return;
  }
  _error_msgr("bind error: missing file path argument.");
}

void processor::mkline_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string tmp;
  std::vector<std::string> arg_vector;
  while ((ss >> tmp)) {
    arg_vector.push_back(tmp);
  }
  if (arg_vector.empty()) {
    _error_msgr("mkline error: missing parameters.");
    return;
  }
  _system.mkline(std::move(arg_vector));
}

void processor::rmline_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string tmp;
  std::vector<std::string> arg_vector;
  while ((ss >> tmp)) {
    arg_vector.push_back(tmp);
  }
  if (arg_vector.empty()) {
    _error_msgr("rmline error: missing parameters.");
    return;
  }
  _system.rmline(std::move(arg_vector));
}

void processor::mkpoint_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string label;
  if (!(ss >> label)) {
    _error_msgr("mkpoint error: missing parameters.");
    return;
  }
  std::vector<double> arg_vector;
  double tmp;
  while (ss >> tmp) {
    if (tmp < 0) {
      _error_msgr("mkpoint error: negative number.");
      return;
    }
    arg_vector.push_back(tmp);
  }
  _system.mkpoint(label, std::move(arg_vector));
}

void processor::rmpoint_cmd(std::string &args) {
  std::stringstream ss(args);
  std::string label;
  if (!(ss >> label)) {
    _error_msgr("rmpoint error: missing parameters.");
    return;
  }
  std::vector<double> arg_vector;
  double tmp;
  while (ss >> tmp) {
    if (tmp < 0) {
      _error_msgr("rmpoint error: negative number.");
      return;
    }
    arg_vector.push_back(tmp);
  }
  _system.rmpoint(label, std::move(arg_vector));
}

bool processor::external_cmd(std::string &cmd, std::string &args) {
  external ext(_error_msgr, _io_serv);
  int test_pipe[2];
  pipe(test_pipe);
  pid_t procid = fork();
  if (procid < 0) {
    _error_msgr("external command error: failed to fork.");
    return false;
  }
  if (!procid) {
    ext.child_redirect_stdstreams();
    close(test_pipe[0]);
    fcntl(test_pipe[1], F_SETFD, FD_CLOEXEC);
    std::vector<std::string> split_args;
    boost::split(split_args, args, boost::algorithm::is_any_of(" \t"), boost::token_compress_on);
    char **argv= new char * [split_args.size() + 2];
    argv[0] = const_cast<char*>(cmd.c_str());
    for(unsigned i = 1; i < split_args.size() + 1; ++i) {
      argv[i] = const_cast<char*>(split_args[i-1].c_str());
    }
    argv[split_args.size() + 1] = nullptr;
    execvp(argv[0], argv);
    write(test_pipe[1], "", 1);
    _exit(1);
  } else {
    ext.parent_close_unused_pipes();
    close(test_pipe[1]);
    char ch;
    int n = read(test_pipe[0], &ch, 1);
    close(test_pipe[0]);
    if (!n) {
      push_external(std::move(ext));
      return true;
    } else {
      _error_msgr("exec failed: " + cmd + " " + args + ".");
      return false;
    }
  }
}

bool processor::has_running_external() {
  return !_running_externals.empty();
}

void processor::write_to_external(const std::string &str) {
  _running_externals.back().write(str);
}

void processor::push_external(external &&ext) {
  std::lock_guard<std::mutex> guard(_externals_lock);
  _running_externals.emplace_back(std::move(ext));
  async_external_read();
}

void processor::pop_external() {
  std::lock_guard<std::mutex> guard(_externals_lock);
  _running_externals.pop_back();
}

void processor::async_external_read() {
  static asio::streambuf b;
  if (has_running_external()) {
    asio::async_read_until(_running_externals.back()._out, b, '\n',
        [this](const boost::system::error_code &e, std::size_t n) {
          if (n > 0) {
        std::istream s(&b);
        std::string line;
        std::getline(s, line);
        if (this->dispatch(line)) {
          return;
        }
          }
          if (e || !n) {
        this->pop_external();
      }
      std::lock_guard<std::mutex> guard(_externals_lock);
      this->async_external_read();
    });
  }
}

}
