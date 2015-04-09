#include "external.hpp"

namespace xts {

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

void external::parent_close_unused() {
	_out_pipe.close_write_end();
	_in_pipe.close_read_end();
	_err_pipe.close_write_end();
}

void external::write(const std::string &str) {
	asio::write(_in, asio::buffer(str));
}

}