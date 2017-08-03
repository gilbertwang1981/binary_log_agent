#ifndef __BINARY_LOG_AGENT_H__
#define __BINARY_LOG_AGENT_H__

#include <unistd.h>
#include <stdio.h>

#include <string>
#include <ostream>

#include "aynclog.h"
#include "shm.h"
#include "common_local_cache.pb.h"

using namespace common;
using namespace binlog;
using namespace std;

using namespace com::vip::local::cache::proto;

int main(int argc , char ** argv) {
	COMMON_ASYNC_LOGGER_INIT("binlogagent");

	COMMON_ASYNC_LOGGER_DEBUG("%s" , "THE BINLOG AGENT HAS BEEN STARTED.");

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	CacheCommand cc;
	cc.set_key("12345678");
	cc.set_value("this is a test!");
	cc.set_parameter("this is the parameter!");
	cc.set_messagetype(5);

	string output;
	cc.SerializeToString(&output);

	COMMON_ASYNC_LOGGER_DEBUG("%s" , output.c_str());

	CacheCommand ccc;
	ccc.ParseFromString(output);
	COMMON_ASYNC_LOGGER_DEBUG("%s|%s|%s|%d" , ccc.key().c_str() , ccc.value().c_str() , 
		ccc.parameter().c_str() , ccc.messagetype());

	google::protobuf::ShutdownProtobufLibrary();

	sleep(5);

	return 0;
}

#endif



