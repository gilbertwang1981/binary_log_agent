#ifndef __SHM_READER_H__
#define __SHM_READER_H__

#include "shared_memory_struct.pb.h"
#include "shm.h"
#include "filelock.h"

namespace binlog {
	class ShmReader {
		public:
			ShmReader();
			~ShmReader();

			bool initialize(void);

			bool read(com::vip::local::cache::proto::SharedMemoryObject & object); 
		private:
			FileLock * m_indexLock;
			FileLock * m_dataLock;

			BinLogShm * m_idxShm;
			BinLogShm * m_dataShm;

			bool switchFile(int index , int lastIndex);
	};
}

#endif

