#include "replicator.h"
#include "connector.h"

using namespace binlog;
using namespace std;

Replicator * Replicator::m_instance = 0;

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

bool Replicator::initialize() {
	Connector * connector = new Connector();

	connector->initialize("127.0.0.1" , 10012 , socket_callback);

	m_peers.push_back(connector);

	return true;
}


