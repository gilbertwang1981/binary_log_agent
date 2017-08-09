#include "naming.h"
#include "mtct.h"

using namespace binlog;
using namespace common;
using namespace std;

NamingService * NamingService::m_instance = 0;

static const int DEFAULT_NAMING_SDK_PORT = 10012;

int naming_callback(int fd , char * buffer) {
	return 0;
}

NamingService::NamingService() {
}


NamingService::~NamingService() {
}

bool NamingService::add(string host) {
	map<string , Connector *>::iterator it = m_peers.find(host);
	if (it != m_peers.end()) {
		return false;		
	}

	Connector * connector = new Connector();

	connector->initialize(it->first , DEFAULT_NAMING_SDK_PORT , naming_callback);

	(void)m_peers.insert(std::make_pair<std::string , Connector *>(host , connector));

	return true;
}

bool NamingService::remove(string host) {
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

bool NamingService::callback(char * buffer, int & length) {
	return true;
}

bool NamingService::initialize() {
	if (!MultiCastClient::instance()->initialize()) {
		return false;
	}

	if (!MultiCastServer::instance()->initialize(NamingService::callback)) {
		return false;
	}

	return true;
}



