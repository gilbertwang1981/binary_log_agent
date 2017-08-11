#ifndef __SHM_H__
#define __SHM_H__

#include <sys/mman.h>

namespace binlog {

	enum {
		BINLOG_OPTYPE_NOTIFY = 0,
		BINLOG_OPTYPE_SET = 1,
		BINLOG_OPTYPE_DEL = 2 , 
		BINLOG_OPTYPE_ERR = 3 ,
		BINLOG_OPTYPE_HB = 127
	};

	class BinLogShm {
		public:
			BinLogShm();
			virtual ~BinLogShm();

			bool readInt32(int offset , int & output);
			bool readBytes(int offset , int length , char * output);

			bool writeInt32(int offset , int input);
			bool writeBytes(int offset , int length , char * input);

			bool initialize(const char * name);

		private:
			int m_fd;
			char * m_ptr;
	};
}

#endif


