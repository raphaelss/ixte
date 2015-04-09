#ifndef PIPER_HPP_XTS_INCLUDED
#define PIPER_HPP_XTS_INCLUDED

namespace xts {

class piper {
public:
	piper();
	piper(const piper &other)  = delete;
	piper(piper &&p) noexcept;
	~piper() noexcept;
	
	piper &operator=(const piper &p) = delete;
	piper &operator=(piper &&p) noexcept;
	
	bool dup_read_end(int pid) const;
	bool dup_write_end(int pid) const;
	
	int read_end() const;
	int write_end() const;
	
	void close_read_end();
	void close_write_end();
	
private:
	void closefd(int &x);
	int pipefd[2];
};

}

#endif