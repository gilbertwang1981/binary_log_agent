#include "memdb.h"

#include <string.h>

using namespace binlog;


void MemDBUtil::parseShmDBIndex(uint32 * raw , ShmDBIndex & index) {
	(void)memcpy(&index.total , raw + 0 , 4);
	(void)memcpy(&index.writeCtr , raw + 4 , 4);
	(void)memcpy(&index.readCtr , raw + 8 , 4);
	(void)memcpy(&index.index , raw + 12 , 4);
}

void MemDBUtil::parseShmDBDataHdr(uint32 * raw , ShmDBDataHdr & hdr) {
	(void)memcpy(&hdr.total , raw + 0 , 4);
	(void)memcpy(&hdr.wPage , raw + 4 , 4);
	(void)memcpy(&hdr.rPage , raw + 8 , 4);
	(void)memcpy(&hdr.wOffset , raw + 12 , 4);
	(void)memcpy(&hdr.wCtr , raw + 16 , 4);
	(void)memcpy(&hdr.rOffset , raw + 20 , 4);
	(void)memcpy(&hdr.rCtr , raw + 24 , 4);
}





