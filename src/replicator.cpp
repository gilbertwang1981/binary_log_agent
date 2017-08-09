#include "replicator.h"
#include "connector.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace binlog;
using namespace std;

Replicator * Replicator::m_instance = 0;

static const int DEFAULT_SDK_PORT = 10012;

int socket_callback(int fd , char * buffer) {
	return 0;
}

Replicator * Replicator::instance() {
	if (m_instance == 0) {
		m_instance = new Replicator();
	}

	return m_instance;
}

bool Replicator::replicate(char * buffer , int length) {
	vector<Connector *>::iterator it = m_peers.begin();
	while (it != m_peers.end()) {
		Connector * connector = (Connector *)(*it);

		if (connector->isConnected()) {
			connector->sendMsg(buffer , length);
		}
	
		it ++;
	}
	
	return true;
}

vector<string> Replicator::getAddressFromEnv() {
	vector<string> ipList;

	char * ips = getenv("DEFAULT_CLUSTER_HOSTS");
	if (ips == 0) {
		ipList.push_back("127.0.0.1");
	} else {
		char * token = strtok(ips , ":");
		if (token != 0) {
			ipList.push_back(token);
		}

		while ((token = strtok(0, ":")) != 0) {
			ipList.push_back(token);
		}
	}

	return ipList;
}

bool Replicator::initialize() {
	vector<string> ips = getAddressFromEnv();
	vector<string>::iterator it = ips.begin();
	while (it != ips.end()) {
		Connector * connector = new Connector();

		connector->initialize(*it , DEFAULT_SDK_PORT , socket_callback);

		m_peers.push_back(connector);

		it ++;
	}

	return true;
}


