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

		  const bool isConnected() const {
		  	return m_isConnected;
		  }
		
		  const int getHandle(void) const {
		  	return m_socket;
		  }
		
		private:
		  static void * run_event_loop(void * args);
		
		  int m_socket;
		  bool m_isConnected;
		
		  std::string m_ipAddr;
		  int m_port;
		  SocketCallback m_callback;		
	};
}

#endif

