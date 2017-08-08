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

		if (object.optype() == BINLOG_OPTYPE_NOTIFY) {
			COMMON_ASYNC_LOGGER_INFO("Cache Flush:%s,%ld" , object.value().c_str() , 
				object.timestamp());
		} else if (object.optype() == BINLOG_OPTYPE_SET) {
			COMMON_ASYNC_LOGGER_INFO("Cache Set:%s,%s,%ld" , object.key().c_str() , 
				object.value().c_str() , object.timestamp());
		} else if (object.optype() == BINLOG_OPTYPE_DEL) {
			COMMON_ASYNC_LOGGER_INFO("Cache Del:%s,%ld" , object.key().c_str() , 
				object.timestamp());
		} else {
			COMMON_ASYNC_LOGGER_ERROR("invalid command, %d" , object.optype());
		}
	}

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

#endif



