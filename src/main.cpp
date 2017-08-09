#ifndef __BINARY_LOG_AGENT_H__
#define __BINARY_LOG_AGENT_H__

#include <string>

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <arpa/inet.h>

#include "aynclog.h"
#include "shm.h"
#include "shmreader.h"
#include "replicator.h"
#include "common_local_cache.pb.h"

using namespace common;
using namespace binlog;
using namespace std;

using namespace com::vip::local::cache::proto;

void init_daemon() {
  int pid = fork();
  if(pid < 0) {
    (void)exit(1);
  }
  else if(pid > 0) {
    (void)exit(0);
  }
  
  (void)setsid(); 

  pid = fork();

  if(pid > 0) {
    (void)exit(0);
  }
  else if(pid < 0) {
    (void)exit(1);
  }
  
  for(int i = 0;i < NOFILE ; i++) {
    (void)close(i);
  }

  (void)umask(0);

  return;
}

int main(int argc , char ** argv) {

	if (argc != 2) {
	  printf("Usage: ./binary_log_agent isDeamon\n");
	
	  return -1;
	}
	
	if (atoi(argv[1]) != 0) {
	  init_daemon();
	}
	
	(void)signal(SIGPIPE , SIG_IGN);

	COMMON_ASYNC_LOGGER_INIT("binlogagent");

	if (!Replicator::instance()->initialize()){
		return -1;
	}

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

		CacheCommand cacheCommand;
		if (object.optype() == BINLOG_OPTYPE_NOTIFY) {
			COMMON_ASYNC_LOGGER_INFO("Cache Flush:%s,%ld" , object.value().c_str() , 
				object.timestamp());
			cacheCommand.set_parameter(object.value());
			cacheCommand.set_messagetype(BINLOG_OPTYPE_NOTIFY);
		} else if (object.optype() == BINLOG_OPTYPE_SET) {
			COMMON_ASYNC_LOGGER_INFO("Cache Set:%s,%s,%ld" , object.key().c_str() , 
				object.value().c_str() , object.timestamp());
			cacheCommand.set_key(object.key());
			cacheCommand.set_value(object.value());
			cacheCommand.set_messagetype(BINLOG_OPTYPE_SET);
		} else if (object.optype() == BINLOG_OPTYPE_DEL) {
			COMMON_ASYNC_LOGGER_INFO("Cache Del:%s,%ld" , object.key().c_str() , 
				object.timestamp());
			cacheCommand.set_key(object.key());
			cacheCommand.set_messagetype(BINLOG_OPTYPE_DEL);
		} else {
			COMMON_ASYNC_LOGGER_ERROR("invalid command, %d" , object.optype());

			continue;
		}

		int length = cacheCommand.ByteSize();
		char * data = new char[length];
		cacheCommand.SerializeToArray(data , length);

		int dataLen = htonl(length);
		char * buffer = new char[length + 4];
		(void)memcpy(buffer , &dataLen , 4);
		(void)memcpy(buffer + 4 , data , length);
		if (!Replicator::instance()->replicate(buffer , length + 4)) {
			COMMON_ASYNC_LOGGER_ERROR("replicate failed.%d" , object.optype());
		}

		delete [] data;
		data = 0;

		delete [] buffer;
		buffer = 0;
	}

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

#endif



