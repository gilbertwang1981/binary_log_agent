#ifndef __MEMDB_H__
#define __MEMDB_H__

#include <sys/types.h>
#include <unistd.h>

namespace binlog {
	typedef unsigned int uint32;

	typedef struct tag_Index {
		uint32 total;
		uint32 writeCtr;
		uint32 readCtr;
		uint32 index;

		tag_Index(){
			total = 0;
			writeCtr = 0;
			readCtr = 0;
			index = 0;
		}
	}ShmDBIndex;

	typedef struct tag_Payload {
		uint32 length;
		uint32 * payload;

		tag_Payload(){
			length = 0;
			payload = 0;
		}
	}ShmDBPayload;

	typedef struct tag_DataHdr {
		uint32 total;
		uint32 wPage;
		uint32 rPage;
		uint32 wOffset;
		uint32 wCtr;
		uint32 rOffset;
		uint32 rCtr;

		tag_DataHdr(){
			total = 0;
			wPage = 0;
			rPage = 0;
			wOffset = 0;
			wCtr = 0;
			rOffset = 0;
			rCtr = 0;
		}
	}ShmDBDataHdr;

	class MemDBUtil {
		public:
			static void parseShmDBIndex(uint32 * raw , ShmDBIndex & index);
			static void parseShmDBDataHdr(uint32 * raw , ShmDBDataHdr & data);
	};
}

#endif


