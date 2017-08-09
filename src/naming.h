#ifndef __NAMING_H__
#define __NAMING_H__

#include <map>
#include "connector.h"

namespace binlog {
	class NamingService {
		public:
			NamingService();
			virtual ~NamingService();

			static NamingService * instance();

			bool initialize(void);

			static bool callback(char * buffer , int & length);

			bool remove(std::string host);
			bool add(std::string host);

		private:
			static NamingService * m_instance;

			std::map<std::string , Connector *> m_peers;
	};
}

#endif


