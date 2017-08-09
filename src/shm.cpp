#include "shm.h"
#include "memdb.h"

#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

using namespace binlog;

static const int DEFAULT_SHM_FILE_SIZE = 8388608;

BinLogShm::BinLogShm():m_fd(-1) , m_ptr(0){
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

bool BinLogShm::initialize(const char * name) {
	if (m_fd == -1) {
		m_fd = open(name , O_RDWR);
		if (m_fd == -1) {
			return false;
		}
	}

	m_ptr = (char *)mmap(0 , DEFAULT_SHM_FILE_SIZE , PROT_READ | PROT_WRITE , MAP_SHARED , m_fd , 0);
	if (m_ptr == MAP_FAILED) {
		close(m_fd);
		m_fd = -1;
	
		return false;
	}

	return true;
}

bool BinLogShm::readInt32(int offset , int & output) {
	if (m_ptr == 0) {
		return false;
	}

	(void)memcpy(&output , m_ptr + offset  , sizeof(int));

	output = htonl(output);

	return true;
}

bool BinLogShm::readBytes(int offset , int length , char * output) {
	if (m_ptr == 0) {
		return false;
	}

	(void)memcpy(output , m_ptr + offset , length);

	return true;
}

bool BinLogShm::writeInt32(int offset , int input) {
	if (m_ptr == 0) {
		return false;
	}

	input = htonl(input);
	
	(void)memcpy(m_ptr + offset , &input  , sizeof(int));

	return true;
}

bool BinLogShm::writeBytes(int offset , int length , char * input) {
	if (m_ptr == 0) {
		return false;
	}

	(void)memcpy(m_ptr + offset , &input , length);

	return true;
}



