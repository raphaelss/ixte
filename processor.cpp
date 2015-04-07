#include "processor.hpp"
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace xts {

namespace fs = boost::filesystem;

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

processor::processor(graphic_system &sys, error_msgr &msgr)
    : _system(sys), _error_msgr(msgr) {}


void processor::do_work() {
	
}

void processor::execute(std::string str) {
	dispatch(str);
}

void processor::dispatch(std::string &str) {
	std::string cmd = split_first_token(str);
	if (cmd == "exit") {
		exit_cmd(str);
	} else if (cmd == "dump") {
		dump_cmd(str);
	} else if (cmd == "mkline") {
		mkline_cmd(str);
	} else if (cmd == "rmline") {
		rmline_cmd(str);
	} else if (cmd == "mkpoint") {
		mkpoint_cmd(str);
	} else if (cmd == "rmpoint") {
		rmpoint_cmd(str);
	} else {
		external_cmd(cmd, str);
	}
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

void processor::dump_cmd(std::string &args) {
	std::stringstream ss(args);
	std::string tmp;
	if (ss >> tmp) {
		_system.dump(std::move(tmp));
		return;
	}
	_error_msgr("dump error: missing file path.");
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
		arg_vector.push_back(tmp);
	}
	_system.rmpoint(label, std::move(arg_vector));
}

void processor::external_cmd(std::string &cmd, std::string &args) {
	if (fs::exists(cmd)) {
		fs::path p(cmd);
		while (fs::is_symlink(p)) {
			p = fs::read_symlink(p);
		}
		if (fs::is_directory(p)) {
			_error_msgr("external command error: " + cmd + "is a directory");
			return;
		}
		if (fs::is_regular_file(p)) {
			fs::file_status status = fs::status(p);
			if (!(status.permissions() & (fs::others_exe | fs::owner_exe | fs::group_exe))) {
				group_cmd(p.native(), args);
				return;
			}
		}
	}
	executable_cmd(cmd, args);

}

void processor::group_cmd(std::string path, std::string &args) {
	std::ifstream fin(path);
	std::string line;
	while (std::getline(fin, line)) {
		dispatch(line);
	}
}

void processor::executable_cmd(std::string &cmd, std::string &args) {
/*
	pid_t procid = vfork();
	if (procid < 0) {
		_error_msgr("external command error: " + cmd + " - failed to fork");
		return;
	}
	else if (!procid) {
		std::vector<std::string> tmp_vec;
		boost::split(tmp_vec, args, boost::is_space, boost::token_compress_on);
		std::vector<const char*> ptr_vec;
		std::transform(tmp_vec.begin(), tmp_vec.end(), std::back_inserter(ptr_vec), [](std::string &str) {
			str.c_str();
		});
		ptr_vec.insert(ptr_vec.begin(), cmd.c_str());
		ptr_vec.push_back(nullptr);
		execvp(cmd.c_str(), ptr_vec.data());
		
	} else {
		std::cout << "Parent process" << std::endl;
	}
*/
}

}