#include "shmreader.h"
#include "shared_memory_struct.pb.h"
#include "aynclog.h"

#include <stdlib.h>

using namespace binlog;
using namespace com::vip::local::cache::proto;
using namespace common;

const static int DEFAULT_PATH_LENGTH = 256;

ShmReader::ShmReader():m_indexLock(0) ,
	m_idxShm(0) , m_dataShm(0) , m_dataLock(0) {
}

ShmReader::~ShmReader(){
	if (m_indexLock != 0) {
		delete m_indexLock;
		m_indexLock = 0;
	}

	if (m_dataLock != 0) {
		delete m_dataLock;
		m_dataLock = 0;
	}

	if (m_idxShm != 0) {
		delete m_idxShm;
		m_idxShm = 0;
	}

	if (m_dataShm != 0) {
		delete m_dataShm;
		m_dataShm = 0;
	}
}

bool ShmReader::initialize() {
	char indexLockPath[DEFAULT_PATH_LENGTH] = {0};
	char indexDataPath[DEFAULT_PATH_LENGTH] = {0};
	
	char * idxPath = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_INDEX_PATH");
	if (idxPath == 0) {
		(void)sprintf(indexLockPath , "%s" , "index.lock");
		(void)sprintf(indexDataPath , "%s" , "index.shm");
	} else {
		(void)sprintf(indexLockPath , "%s/%s" , idxPath , "index.lock");
		(void)sprintf(indexDataPath , "%s/%s" , idxPath , "index.shm");
	}

	m_indexLock = new FileLock(indexLockPath);
	m_idxShm = new BinLogShm();

	if (!m_idxShm->initialize(indexDataPath)){
		delete m_indexLock;
		m_indexLock = 0;

		delete m_idxShm;
		m_idxShm = 0;
	
		return false;
	}

	int index = 0;
	
	m_indexLock->lock();
	m_idxShm->readInt32(8 , index);
	m_indexLock->unlock();

	char dataLockPath[DEFAULT_PATH_LENGTH] = {0};
	char dataPath[DEFAULT_PATH_LENGTH] = {0};
	
	char * path = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_DATA_PATH");
	if (path == 0) {
		(void)sprintf(dataLockPath , "data.%d.lock" , index);
		(void)sprintf(dataPath , "data.%d.shm" , index);
	} else {
		(void)sprintf(dataLockPath , "%s/data.%d.lock" , path , index);
		(void)sprintf(dataPath , "%s/data.%d.shm" , path , index);
	}

	m_dataLock = new FileLock(dataLockPath);
	m_dataShm = new BinLogShm();

	if (!m_dataShm->initialize(dataPath)){
		delete m_indexLock;
		m_indexLock = 0;

		delete m_idxShm;
		m_idxShm = 0;

		delete m_dataLock;
		m_dataLock = 0;

		delete m_dataShm;
		m_dataShm = 0;
	
		return false;
	}

	return true;
}

bool ShmReader::switchFile(int index) {
	if (m_dataShm != 0) {
		delete m_dataShm;
		m_dataShm = 0;
	
		char dataPath[DEFAULT_PATH_LENGTH] = {0};
		char * path = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_DATA_PATH");
		if (path == 0) {
			(void)sprintf(dataPath , "data.%d.shm" , index);
		} else {
			(void)sprintf(dataPath , "%s/data.%d.shm" , path , index);
		}

		m_dataShm = new BinLogShm();
		if (!m_dataShm->initialize(dataPath)) {		
			return false;
		}
	} else {
		return false;
	}

	return true;
}

bool ShmReader::read(SharedMemoryObject & object) {
	if (m_indexLock == 0 || !m_indexLock->lock()) {
		return false;
	}

	int total = 0;
	if (!m_idxShm->readInt32(0 , total)){
		(void)m_indexLock->unlock();
	
		return false;
	}

	int wCtr = 0;
	if (!m_idxShm->readInt32(4 , wCtr)){
		(void)m_indexLock->unlock();
	
		return false;
	}

	int rCtr = 0;
	if (!m_idxShm->readInt32(8 , rCtr)){
		(void)m_indexLock->unlock();
	
		return false;
	}

	if (!m_indexLock->unlock()){
		return false;
	}

	if (m_dataLock == 0 || !m_dataLock->lock()) {
		return false;
	}

	int dTotal = 0;
	if (!m_dataShm->readInt32(0 , dTotal)) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	int drCtr = 0;
	if (!m_dataShm->readInt32(24 , drCtr)) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	int dwCtr = 0;
	if (!m_dataShm->readInt32(16 , dwCtr)) {
		(void)m_dataLock->unlock();
	
		return false;
	} 

	int drOffset = 0;
	if (!m_dataShm->readInt32(20 , drOffset)) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	if (wCtr == rCtr && dwCtr == drCtr) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	COMMON_ASYNC_LOGGER_DEBUG("total:%d,wCtr:%d,rCtr:%d,dTotal:%d,dwCtr:%d,drCtr:%d\n" , 
		total , wCtr , rCtr , dTotal , dwCtr , drCtr);

	int dataLen = 0;
	if (!m_dataShm->readInt32(28 + drOffset , dataLen)) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	char * data = new char[dataLen];
	(void)memset(data , 0x00 , dataLen);

	if (!m_dataShm->readBytes(28 + drOffset + 4 , dataLen , data)) {
		delete [] data;
		data = 0;

		(void)m_dataLock->unlock();

		return false;
	}
	
	SharedMemoryObject smo;
	smo.ParseFromArray(data , dataLen);
	object = smo;

	drOffset += dataLen + 4;

	delete [] data;
	data = 0;

	bool needSwitch = false;
	if ((dTotal -1) == drCtr) {
		rCtr ++;
	
		drCtr = 0;

		needSwitch = true;
	} else {
		drCtr ++;
	}

	if (rCtr == total) {
		needSwitch = true;
		rCtr = 0;
	}

	(void)m_dataShm->writeInt32(24 , drCtr);
	(void)m_dataShm->writeInt32(20 , drOffset);
	(void)m_idxShm->writeInt32(8 , rCtr);

	if (needSwitch) {
		if (!this->switchFile(rCtr)) {
			(void)m_dataLock->unlock();
		
			return false;
		}
	}

	if (!m_dataLock->unlock()) {
		return false;
	}
	
	return true;
}




