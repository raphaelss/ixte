#ifndef PROCESSOR_HPP_XTS_INCLUDED
#define PROCESSOR_HPP_XTS_INCLUDED
#include <string>
#include <vector>
#include <thread>
#include "graphic_system.hpp"
#include "error_msgr.hpp"
#include "external.hpp"
#include <boost/asio.hpp>
#include <mutex>

namespace xts {

class processor {
public:
	processor(graphic_system &sys, error_msgr &msgr);
	~processor();
	
	void request_exit();
	void execute(std::string str);
	
private:
	bool dispatch(std::string &str);
	void exit_cmd(std::string &args);
	void dump_cmd(std::string &args);
	void mkline_cmd(std::string &args);
	void rmline_cmd(std::string &args);
	void mkpoint_cmd(std::string &args);
	void rmpoint_cmd(std::string &args);
	void external_cmd(std::string &cmd, std::string &args);
	
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