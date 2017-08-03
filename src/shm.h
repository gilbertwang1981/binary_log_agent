#ifndef __SHM_H__
#define __SHM_H__

namespace binlog {
	class BinLogShm {
		public:
			static BinLogShm * instance();

		private:
			static BinLogShm * m_instance;
	};
}

#endif


