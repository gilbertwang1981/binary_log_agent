#include "shmreader.h"

#include <stdlib.h>

using namespace binlog;
using namespace com::vip::local::cache::proto;

const static int DEFAULT_PATH_LENGTH = 256;

ShmReader::ShmReader():m_indexlock(0){
}

ShmReader::~ShmReader(){
	if (m_indexlock != 0) {
		delete m_indexlock;
	}
}

bool ShmReader::initialize() {
	char lockPath[DEFAULT_PATH_LENGTH] = {0};

	char * path = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_INDEX_PATH");
	if (path == 0) {
		(void)sprintf(lockPath , "%s" , "index.lock");
	} else {
		(void)sprintf(lockPath , "%s/%s" , path , "index.lock");
	}

	m_indexlock = new FileLock(lockPath);

	return true;
}

bool ShmReader::read(SharedMemoryObject & object) {
	return true;
}




