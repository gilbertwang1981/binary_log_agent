#include "connector.h"
#include "aynclog.h"
#include "common_local_cache.pb.h"
#include "shm.h"

#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

using namespace binlog;
using namespace common;
using namespace std;
using namespace com::vip::local::cache::proto;

Connector::Connector():m_socket(-1),m_isConnected(false) , m_isClosed(false) , 
	m_lastUpdatedTime(time(0)) {
}

void * Connector::send_heartbeat(void * args) {
	Connector * connector = (Connector *)args;
	while (!connector->isClosed()) {
		sleep(5);
		
		if (connector->isConnected()) {
			CacheCommand cacheCommand;
			cacheCommand.set_messagetype(BINLOG_OPTYPE_HB);

			int length = cacheCommand.ByteSize();
			char * data = new char[length];
			cacheCommand.SerializeToArray(data , length);

			int dataLen = htonl(length);
			char * buffer = new char[length + 4];
			(void)memcpy(buffer , &dataLen , 4);
			(void)memcpy(buffer + 4 , data , length);
		
			(void)connector->sendMsg(buffer , length + 4);

			delete [] data;
			data = 0;

			delete [] buffer;
			buffer = 0;
		}
	}

	return 0;
}

int Connector::initialize(string ipAddress , int port , SocketCallback callback) {
  m_ipAddr = ipAddress;
  m_port = port;
  m_callback = callback;

  pthread_t tid;
  if (-1 == pthread_create(&tid , 0 , run_event_loop , this)) { 
    return -1;
  }

  if (-1 == pthread_create(&tid , 0 , send_heartbeat , this)) { 
    return -1;
  }
  
  return 0;
}

void * Connector::run_event_loop(void * args) {
  Connector * connector = (Connector *)args;

  connector->handle_message();
  
  return 0;
}

int Connector::sendMsg(char * buffer , int length) {
  if (!m_isConnected) {
  	COMMON_ASYNC_LOGGER_ERROR("not connect to server %s" , m_ipAddr.c_str());
	
    return -1;
  }

  int ret = -1;
  int offset = 0;
  while (offset < length) {
	ret = send(m_socket , buffer + offset , length - offset , 0);
	if (ret <= 0) {
	  COMMON_ASYNC_LOGGER_ERROR("send failed, %s" , strerror(errno));

	  m_isConnected = false;
	  ::close(m_socket);
	  m_socket = -1;
	  
	  return -1;
	} else {
	  offset += ret;
	}
  }
  
  return 0;
}

int Connector::recvMsg(char * buffer,int length) {
  if (!m_isConnected) {
  	COMMON_ASYNC_LOGGER_ERROR("not connect to server %s" , m_ipAddr.c_str());
	
    return -1;
  }

  int ret = -1;
  int offset = 0;
  while (offset < length) {
    ret = recv(m_socket , buffer + offset , length - offset , 0);
	if (ret <= 0) {
	  COMMON_ASYNC_LOGGER_ERROR("recv failed, %s\n" , strerror(errno));

	  m_isConnected = false;
	  ::close(m_socket);
	  m_socket = -1;
	  
	  return -1;
	} else {
	  offset += ret;
	}
  }

  this->updateTimestamp();
  
  return 0;
}

void Connector::closeConnector() {
	if (m_socket == -1) {
		m_isClosed = true;
		
		return;
	}

	m_isClosed = true;
	
	::close(m_socket);
	m_socket = -1;
}

int Connector::handle_message() {
  while (!this->isClosed()) {
    if (!m_isConnected) {
	  COMMON_ASYNC_LOGGER_INFO("reconnected to remote server[%s]" , m_ipAddr.c_str());

	  m_socket = socket(AF_INET , SOCK_STREAM , 0);
	  if (m_socket == -1) {
		COMMON_ASYNC_LOGGER_ERROR("create socket failed. %s" , strerror(errno));
		
		return -1;
	  }

	  struct linger so_linger;
      so_linger.l_onoff = 1; 
      so_linger.l_linger = 0; 
      (void)setsockopt(m_socket , SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger); 

	  struct sockaddr_in addr;
	  addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(m_ipAddr.c_str());
      addr.sin_port = htons(m_port);

	  if (-1 == connect(m_socket , (struct sockaddr*)&addr , sizeof(addr))) {
	    COMMON_ASYNC_LOGGER_ERROR("reconnected failed,%s" , strerror(errno));

        ::close(m_socket);
		m_socket = -1;
 
		::sleep(5);
		
	    continue;
	  }
	  else {
	    COMMON_ASYNC_LOGGER_INFO("connected successfully.[%s]" , m_ipAddr.c_str());
		m_isConnected = true;
	  }
    }

	char header[12] = {0};
	if (-1 == this->recvMsg(header , 12)) {
	  if (m_socket != -1) {
	  	::close(m_socket);
      	m_socket = -1;
	  }
	  
	  continue;
	}

	int length = -1;
	(void)memcpy(&length , header , 4);
	length = ntohl(length);

	char * rxb = new char [length];
    if (-1 == this->recvMsg(rxb + 12 , length - 12)) {
	  if (m_socket != -1) {
	    ::close(m_socket);
	    m_socket = -1;
	  }
	  
      continue;
    }

	(void)memcpy(rxb , header , 12);

    (*m_callback)(m_socket , rxb);

	delete [] rxb;
  }
  
  return 0;
}


