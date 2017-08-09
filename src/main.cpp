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

#include "aynclog.h"
#include "shm.h"
#include "shmreader.h"
#include "replicator.h"

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

	if (!Replicator::instance()->initialize()){
		return -1;
	}

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



