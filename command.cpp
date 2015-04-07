#include "command.hpp"
#include <vector>
#include <string>

namespace xts {

class group_cmd : command {
public:
	group_cmd();
	
	virtual void execute(graphic_system &sys) const {
		for (const auto &cmd_ptr : _cmds) {
			cmd_ptr->execute(sys);
		}
	}
	
	virtual void execute_reverse(graphic_system &sys) const {
		for (auto it = _cmds.crbegin(), end = _cmds.crend(); it != end; ++it) {
			(*it)->execute(sys);
		}
	}
	
	virtual type cmd_type() const {
		return GROUP;
	}
	
private:
	std::vector<std::unique_ptr<command>> _cmds;
};

class mkline_cmd : command {
public:
	mkline_cmd(std::vector<std::string> &&labels): _labels(labels) {}
	
	virtual void execute(graphic_system &sys) const {
//		sys.mkline(_labels.cbegin(), _labels.cend());
	}

	virtual type cmd_type() const {
		return MKLINE;
	}
private:
	std::vector<std::string> _labels;
};


class rmline_cmd : command {
public:
	rmline_cmd(std::vector<std::string> &&labels): _labels(labels) {}
	
	virtual void execute(graphic_system &sys) const {
//		sys.rmline(_labels.cbegin(), _labels.cend());
	}
	
	virtual type cmd_type() const {
		return RMLINE;
	}
private:
	std::vector<std::string> _labels;
};

class mkpoint_cmd : command {
public:
	mkpoint_cmd(std::string &&label, std::vector<double> &&points)
	    : _label(label), _points(points) {}
	    
	 virtual void execute(graphic_system &sys) const {
//
	 }

	virtual type cmd_type() const {
		return MKPOINT;
	}
	
private:
	std::string _label;
	std::vector<double> _points;
};

class rmpoint_cmd : command {
public:
	rmpoint_cmd(std::string &&label, std::vector<double> &&points)
	    : _label(label), _points(points) {}
	    
	 virtual void execute(graphic_system &sys) const {
//
	 }

	virtual type cmd_type() const {
		return RMPOINT;
	}
	
private:
	std::string _label;
	std::vector<double> _points;
};

void command::execute_reverse(graphic_system &sys) const {
	return execute(sys);
}

std::unique_ptr<command> command::combine
    (std::unique_ptr<command> &&lhs, std::unique_ptr<command> &&rhs) {
    	//TODO
	return std::unique_ptr<command>(nullptr);
}


}