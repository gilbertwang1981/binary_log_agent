#include "shm.h"
#include "memdb.h"

using namespace binlog;

BinLogShm * BinLogShm::m_instance = 0;

BinLogShm * BinLogShm::instance() {
	if (m_instance == 0) {
		m_instance = new BinLogShm();
	}

	return m_instance;
}


