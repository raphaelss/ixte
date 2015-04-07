#include "error_msgr.hpp"
#include <iostream>

namespace xts {

void error_msgr::operator()(const std::string &str) {
	std::cerr << str << std::endl;
}

}