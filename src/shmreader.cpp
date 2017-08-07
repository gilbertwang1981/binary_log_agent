#include "shmreader.h"

#include <stdlib.h>

using namespace binlog;
using namespace com::vip::local::cache::proto;

const static int DEFAULT_PATH_LENGTH = 256;

ShmReader::ShmReader():m_indexLock(0) , m_dataLock(0){
}

ShmReader::~ShmReader(){
	if (m_indexLock != 0) {
		delete m_indexlock;
	}

	if (m_dataLock != 0) {
		delete m_dataLock;
	}
}

bool ShmReader::initialize() {
	char indexLockPath[DEFAULT_PATH_LENGTH] = {0};
	char dataLockPath[DEFAULT_PATH_LENGTH] = {0};
	
	char * idxPath = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_INDEX_PATH");
	if (idxPath == 0) {
		(void)sprintf(indexLockPath , "%s" , "index.lock");
	} else {
		(void)sprintf(indexLockPath , "%s/%s" , idxPath , "index.lock");
	}

	char * dataPath = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_DATA_PATH");
	if (idxPath == 0) {
		(void)sprintf(dataLockPath , "%s" , "index.shm");
	} else {
		(void)sprintf(dataLockPath , "%s/%s" , dataPath , "index.shm");
	}

	m_indexLock = new FileLock(indexLockPath);
	m_dataLock = new FileLock(dataLockPath);

	return true;
}

bool ShmReader::read(SharedMemoryObject & object) {
	return true;
}




