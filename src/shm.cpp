#include "shm.h"
#include "memdb.h"

#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace binlog;

static const int DEFAULT_SHM_FILE_SIZE = 4157440;

BinLogShm::BinLogShm(const char * name):m_fd(-1) , m_ptr(0){
	if (m_fd == -1) {
		m_fd = open(name , O_RDONLY);
		if (m_fd == -1) {
			return;
		}
	}

	m_ptr = (char *)mmap(0 , DEFAULT_SHM_FILE_SIZE , PROT_READ , MAP_PRIVATE , m_fd , 0);
	if (m_ptr == 0) {
		close(m_fd);
		m_fd = -1;
	
		return;
	}
}

BinLogShm::~BinLogShm(){
	if (m_ptr != 0) {
		(void)munmap(m_ptr , DEFAULT_SHM_FILE_SIZE);
		m_ptr = 0;
	}

	if (m_fd > 0) {
		close(m_fd);
		m_fd = -1;
	}
}




