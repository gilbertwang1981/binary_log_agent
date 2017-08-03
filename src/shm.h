#ifndef __SHM_H__
#define __SHM_H__

#include <sys/mman.h>

namespace binlog {
	class BinLogShm {
		public:
			BinLogShm(const char * name);
			~BinLogShm();

			bool readInt32(int offset , int & output);
			bool readBytes(int offset , int length , char * output);

		private:
			int m_fd;
			char * m_ptr;
	};
}

#endif


