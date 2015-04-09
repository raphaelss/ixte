#include "piper.hpp"
#include <algorithm>
#include <sys/types.h>
#include <unistd.h>

namespace xts {

piper::piper(): pipefd{-1, -1} {
	if (pipe(pipefd) < 0) {
		throw -1;
	}	
}

piper::piper(piper &&p) noexcept
    : pipefd {p.pipefd[0], p.pipefd[1]} {
	p.pipefd[0] = p.pipefd[1] = -1;
}

piper::~piper() noexcept {
	close_read_end();
	close_write_end();
}

piper &piper::operator=(piper &&p) noexcept {
	if (this != &p) {
		this->pipefd[0] = p.pipefd[0];
		this->pipefd[1] = p.pipefd[1];
		p.pipefd[0] = p.pipefd[1] = -1;
	}
	return *this;
}

bool piper::dup_read_end(int pid) const {
	return dup2(pipefd[0], pid) >= 0;
}

bool piper::dup_write_end(int pid) const {
	return dup2(pipefd[1], pid) >= 0;
}

int piper::read_end() const {
	return pipefd[0];
}

int piper::write_end() const {
	return pipefd[1];
}

void piper::close_read_end() {
	closefd(pipefd[0]);
}

void piper::close_write_end() {
	closefd(pipefd[1]);
}

void piper::closefd(int &x) {
	if (x != -1) {
		close(x);
		x = -1;
	}
}

}