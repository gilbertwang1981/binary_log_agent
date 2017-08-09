#include "naming.h"
#include "mtct.h"

using namespace binlog;
using namespace common;

NamingService * NamingService::m_instance = 0;

NamingService::NamingService(){
}


NamingService::~NamingService() {
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



