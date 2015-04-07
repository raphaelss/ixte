#ifndef ERROR_MSGR_HTTP_XTS_INCLUDED
#define ERROR_MSGR_HTTP_XTS_INCLUDED
#include <string>

namespace xts {

class error_msgr {
public:
	void operator()(const std::string &str);
	
};

}

#endif