#ifndef __NAMING_H__
#define __NAMING_H__

#include <map>
#include "connector.h"

namespace binlog {
	enum {
		BINLOG_NAMING_BC_ADDRESS = 1
	};

	class NamingService {
		public:
			NamingService();
			virtual ~NamingService();

			static NamingService * instance();

			bool initialize(void);

			static bool callback(char * buffer , int & length);

			bool remove(std::string host);
			bool add(std::string host);
			bool broadcast(char * data , int length);
			bool clean(void);

		private:
			static NamingService * m_instance;

			std::map<std::string , Connector *> m_peers;

			static std::map<std::string , int> m_lastUpdatedTime;

			static void * run_checker(void * args);

			bool discover();
			std::string getNodeId(int socket = -1);

			bool error(std::string errorNodeId , char * buffer , int length);

			static std::string buildVerifyCode(void);
	};
}

#endif


