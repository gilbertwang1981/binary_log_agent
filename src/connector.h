#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include <string>

namespace binlog {
	typedef int (* SocketCallback)(int , char *);

	class Connector {
		public:
		  Connector();
		
		  int initialize(std::string ipAddress , int port , SocketCallback callback);
		
		  int sendMsg(char * buffer , int length);
		  int recvMsg(char * buffer , int length);
		  
		  int handle_message(void);

		  const void updateTimestamp(void) {
		  	m_lastUpdatedTime = time(0);
		  }

		  const int getLastUpdatedTimestamp(void) const {
		  	return m_lastUpdatedTime;
		  }

		  const bool isConnected() const {
		  	return m_isConnected;
		  }

		  void closeConnector();
		
		  const int getHandle(void) const {
		  	return m_socket;
		  }
		
		private:
		  static void * run_event_loop(void * args);

		  static void * send_heartbeat(void * args);
		
		  int m_socket;
		  bool m_isConnected;
		
		  std::string m_ipAddr;
		  int m_port;
		  SocketCallback m_callback;

		  static bool m_isClosed;

		  int m_lastUpdatedTime;
	};
}

#endif

