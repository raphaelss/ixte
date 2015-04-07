#ifndef PROCESSOR_HPP_XTS_INCLUDED
#define PROCESSOR_HPP_XTS_INCLUDED
#include <string>
#include <vector>
#include "graphic_system.hpp"
#include "error_msgr.hpp"

namespace xts {

class processor {
public:
	processor(graphic_system &sys, error_msgr &msgr);

	void do_work();
	void execute(std::string str);
	
private:
	void dispatch(std::string &str);
	void exit_cmd(std::string &args);
	void dump_cmd(std::string &args);
	void mkline_cmd(std::string &args);
	void rmline_cmd(std::string &args);
	void mkpoint_cmd(std::string &args);
	void rmpoint_cmd(std::string &args);
	void external_cmd(std::string &cmd, std::string &args);
	void group_cmd(std::string path, std::string &args);
	void executable_cmd(std::string &cmd, std::string &args);
	
	graphic_system &_system;
	error_msgr &_error_msgr;
};

}

#endif