#ifndef __BINARY_LOG_AGENT_H__
#define __BINARY_LOG_AGENT_H__

#include <unistd.h>
#include <stdio.h>

#include "aynclog.h"

using namespace common;
using namespace std;

int main(int argc , char ** argv) {
	COMMON_ASYNC_LOGGER_INIT("binlog");

	COMMON_ASYNC_LOGGER_DEBUG("%s" , "THE BINLOG AGENT HAS BEEN STARTED.");

	return 0;
}

#endif



