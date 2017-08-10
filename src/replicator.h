﻿#ifndef __REPLICA_H__
#define __REPLICA_H__

#include <vector>
#include <string>

#include "connector.h" 

namespace binlog {
	class Replicator {
		public:
			static Replicator * instance();

			bool initialize(void);

			bool replicate(char * buffer , int length);

		private:
			static Replicator * m_instance;
	};
}

#endif

