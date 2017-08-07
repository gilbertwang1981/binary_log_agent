#ifndef __SHM_READER_H__
#define __SHM_READER_H__

#include "shared_memory_struct.pb.h"
#include "filelock.h"

namespace binlog {
	class ShmReader {
		public:
			ShmReader();
			~ShmReader();

			bool initialize();

			bool read(com::vip::local::cache::proto::SharedMemoryObject & object); 
		private:
			FileLock * m_indexLock;
			FileLock * m_dataLock;
	};
}

#endif

