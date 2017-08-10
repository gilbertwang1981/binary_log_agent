#include "naming.h"
#include "mtct.h"
#include "mutex.h"
#include "configure.pb.h"
#include "aynclog.h"

#include <pthread.h>

using namespace binlog;
using namespace common;
using namespace std;
using namespace com::vip::local::cache::proto;

NamingService * NamingService::m_instance = 0;

static const int DEFAULT_NAMING_SDK_PORT = 10012;

static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

// not used
int naming_callback(int fd , char * buffer) {
	return 0;
}

NamingService::NamingService() {
}

NamingService::~NamingService() {
}

bool NamingService::callback(char * buffer , int & length) {
	if (length <= 0 || buffer == 0) {
		return false;
	}

	ConfigObject object;

	object.ParseFromArray(buffer , length);

	COMMON_ASYNC_LOGGER_INFO("GOT:[command: %d ip:%s]" , object.optype() , object.ip().c_str());

	if (object.optype() == BINLOG_NAMING_BC_ADDRESS) {
		NamingService::instance()->add(object.ip());
	}

	return true;
}


void * NamingService::run_checker(void * args) {
	int counter = 0;
	while (1) {
		if (counter % 5 == 0) {
			ConfigObject object;
			object.set_ip("10.199.196.120");
			object.set_optype(BINLOG_NAMING_BC_ADDRESS);

			int length = object.ByteSize();
			char * data = new char[length];
			object.SerializeToArray(data , length);

			COMMON_ASYNC_LOGGER_INFO("SND:[command: %d ip:%s]" , object.optype() , object.ip().c_str());
		
			MultiCastClient::instance()->multicast(data , length);

			delete [] data;
			data = 0;

			counter = 0;
		} else {
			counter ++;
		}

		MultiCastServer::instance()->handleMulticastPacket();
		
		sleep(1);
	}
	
	return 0;
}

bool NamingService::broadcast(char * data , int length) {
	COMMON_MUTEX_LOCK(&m_mutex);

	map<string , Connector *>::iterator it = m_peers.begin();
	while (it != m_peers.end()) {
		Connector * connector = (Connector *)it->second;

		if (connector->isConnected()) {
			connector->sendMsg(data , length);
		}
	
		it ++;
	}
	
	return true;
}

bool NamingService::add(string host) {
	COMMON_MUTEX_LOCK(&m_mutex);

	map<string , Connector *>::iterator it = m_peers.find(host);
	if (it != m_peers.end()) {
		return false;		
	}

	Connector * connector = new Connector();

	connector->initialize(host , DEFAULT_NAMING_SDK_PORT , naming_callback);

	(void)m_peers.insert(std::make_pair<std::string , Connector *>(host , connector));

	return true;
}

bool NamingService::remove(string host) {
	COMMON_MUTEX_LOCK(&m_mutex);

	map<string , Connector *>::iterator it = m_peers.find(host);
	if (it == m_peers.end()) {
		return false;		
	}

	Connector * connector = it->second;

	connector->closeConnector();

	delete connector;

	(void)m_peers.erase(it);

	return true;

}

NamingService * NamingService::instance() {
	if (m_instance == 0) {
		m_instance = new NamingService();
	}

	return m_instance;
}

bool NamingService::initialize() {
	if (!MultiCastClient::instance()->initialize()) {
		return false;
	}

	if (!MultiCastServer::instance()->initialize(NamingService::callback)) {
		return false;
	}

	pthread_t tid;
	if (-1 == pthread_create(&tid , 0 , run_checker , 0)) { 
	  return -1;
	}

	return true;
}



