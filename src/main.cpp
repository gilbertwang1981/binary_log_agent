#ifndef __BINARY_LOG_AGENT_H__
#define __BINARY_LOG_AGENT_H__

#include <unistd.h>
#include <stdio.h>

#include <string>
#include <ostream>

#include "aynclog.h"
#include "shm.h"
#include "shmreader.h"

using namespace common;
using namespace binlog;
using namespace std;

using namespace com::vip::local::cache::proto;

int main(int argc , char ** argv) {

	COMMON_ASYNC_LOGGER_INIT("binlogagent");

	if (argc != 3) {
		COMMON_ASYNC_LOGGER_ERROR("%s" , 
				"parameters are not right. help:./binary_log_agent db offset");
	
		return -1;
	}

	COMMON_ASYNC_LOGGER_INFO("THE BINLOG AGENT HAS BEEN STARTED.Working from %d:%d" ,
		atoi(argv[1]) , atoi(argv[2]));

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	ShmReader reader;
	if (!reader.initialize(atoi(argv[1]) , atoi(argv[2]))) {
		return -1;
	}

	while (true) {
		SharedMemoryObject object;
		if (!reader.read(object)){
			usleep(500);
		}

		COMMON_ASYNC_LOGGER_INFO("%s:%s:%s:%ld" , object.ip().c_str() , object.key().c_str() , object.value().c_str() , 
				object.timestamp());
	}

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

#endif



