#ifndef COMMAND_HPP_XTS_INCLUDED
#define COMMAND_HPP_XTS_INCLUDED
#include <memory>
#include "graphic_system.hpp"

namespace xts {

class command {
public:
	enum type {
		MKLINE, RMLINE, MKPOINT, RMPOINT, GROUP
	};
	virtual ~command() = 0;
	virtual void execute(graphic_system &sys) const = 0;
	virtual void execute_reverse(graphic_system &sys) const;
	virtual type cmd_type() const = 0;
	
	static std::unique_ptr<command> combine
	    (std::unique_ptr<command> &&lhs, std::unique_ptr<command> &&rhs);
};

}

#endif