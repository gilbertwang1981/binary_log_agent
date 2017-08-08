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

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	ShmReader reader;
	if (!reader.initialize()) {
		COMMON_ASYNC_LOGGER_ERROR("%s" , "initializing the SHM Reader failed.");
		
		sleep(5);

		return -1;
	}

	while (true) {
		SharedMemoryObject object;
		if (!reader.read(object)){
			usleep(500000);

			continue;
		}

		COMMON_ASYNC_LOGGER_INFO("%s:%s:%s:%ld" , object.ip().c_str() , object.key().c_str() , object.value().c_str() , 
				object.timestamp());
	}

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

#endif



