#ifndef EXTERNAL_HPP_XTS_INCLUDED
#define EXTERNAL_HPP_XTS_INCLUDED
#include "error_msgr.hpp"
#include "piper.hpp"
#include <boost/asio.hpp>

namespace xts {

class external {
public:
	external(error_msgr &msgr, boost::asio::io_service &io_serv);
	
	bool child_redirect_stdstreams() const;
	void parent_close_unused();
	void write(const std::string &str);
	
private:
	piper _out_pipe, _in_pipe, _err_pipe;
public:
	boost::asio::posix::stream_descriptor _out, _in, _err;
};

}

#endif