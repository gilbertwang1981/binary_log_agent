#include "shmreader.h"
#include "shared_memory_struct.pb.h"

#include <stdlib.h>

using namespace binlog;
using namespace com::vip::local::cache::proto;

const static int DEFAULT_PATH_LENGTH = 256;

ShmReader::ShmReader():m_indexLock(0) ,
	m_dbIdx(0) , m_offset(0) , m_idxShm(0) , 
	m_dataShm(0) , m_dataLock(0) {
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

bool ShmReader::initialize(int index , int offset) {
	this->m_dbIdx = index;
	this->m_offset = offset;

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

	m_indexLock = new FileLock(indexLockPath);
	m_idxShm = new BinLogShm(indexDataPath);

	m_dataLock = new FileLock(dataLockPath);
	m_dataShm = new BinLogShm(dataPath);

	return true;
}

bool ShmReader::read(SharedMemoryObject & object) {
	bool isSwitch = false;
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

	int cCtr = 0;
	if (!m_idxShm->readInt32(12 , cCtr)){
		(void)m_indexLock->unlock();
	
		return false;
	}

	if (rCtr == total) {
		cCtr = 0;

		(void)m_idxShm->writeInt32(8 , rCtr);
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

	if (dwCtr == drCtr) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	if (dTotal == drCtr) {
		isSwitch = true;
		rCtr++;
	}

	int drOffset = 0;
	if (!m_dataShm->readInt32(20 , drOffset)) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	int dataLen = 0;
	if (!m_dataShm->readInt32(28 + drOffset , dataLen)) {
		(void)m_dataLock->unlock();
	
		return false;
	}

	char * data = new char[dataLen];
	(void)memset(data , 0x00 , dataLen);

	if (!m_dataShm->readBytes(28 + drOffset , dataLen , data)) {
		delete [] data;
		data = 0;

		(void)m_dataLock->unlock();

		return false;
	}

	drOffset += dataLen + 4;
	drCtr += 1;

	(void)m_dataShm->writeInt32(24 , drCtr);
	(void)m_dataShm->writeInt32(20 , drOffset);
	

	SharedMemoryObject smo;
	smo.ParseFromArray(data , dataLen);
	object = smo;

	delete [] data;
	data = 0;

	if (!m_dataLock->unlock()) {
		return false;
	}

	if (isSwitch) {
		(void)m_indexLock->lock();

		(void)m_idxShm->writeInt32(8 , rCtr);

		// re-init the shm file
		if (m_dataShm == 0) {
			delete m_dataShm;
			m_dataShm = 0;

			char dataPath[DEFAULT_PATH_LENGTH] = {0};
			char * path = getenv("DISTRIBUTED_STRING_LOCAL_CACHE_DATA_PATH");
			if (path == 0) {
				(void)sprintf(dataPath , "data.%d.shm" , rCtr);
			} else {
				(void)sprintf(dataPath , "%s/data.%d.shm" , path , rCtr);
			}

			m_dataShm = new BinLogShm(dataPath);
		}

		(void)m_indexLock->unlock();
	}
	
	return true;
}




