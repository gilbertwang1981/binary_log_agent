#include "replicator.h"
#include "connector.h"
#include "naming.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace binlog;
using namespace std;

Replicator * Replicator::m_instance = 0;

Replicator * Replicator::instance() {
	if (m_instance == 0) {
		m_instance = new Replicator();
	}

	return m_instance;
}

bool Replicator::replicate(char * buffer , int length) {	
	return NamingService::instance()->broadcast(buffer , length);
}

bool Replicator::initialize() {
	return true;
}


