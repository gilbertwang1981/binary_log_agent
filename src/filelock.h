#ifndef __FILE_LOCK_H__
#define __FILE_LOCK_H__

namespace binlog {
	class FileLock {
		public:
			FileLock(const char * name);
			~FileLock();
			
			bool lock(void);
			bool unlock(void);

		private:
			int m_fd;
	};
}

#endif

