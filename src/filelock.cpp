#include "filelock.h"

#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace binlog;

FileLock::FileLock(const char * name):m_fd(-1){
	m_fd = open(name , O_RDWR | _CREAT);
	if (m_fd == -1) {
		return;
	}
}

FileLock::~FileLock(){
	if (m_fd > 0) {
		close(m_fd);
		m_fd = -1;
	}
}

bool FileLock::lock() {
	if (m_fd == -1) {
		return false;
	}

	if (-1 == flock(m_fd , LOCK_EX)){
		close(m_fd);
		m_fd = -1;
	
		return false;
	}
	
	return true;
}

bool FileLock::unlock() {
	if (m_fd == -1) {
		return false;
	}

	if (-1 == flock(m_fd , LOCK_UN)){
		close(m_fd);
		m_fd = -1;
	
		return false;
	}

	return true;
}




