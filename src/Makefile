OBJ:=main.o shm.o memdb.o filelock.o common_local_cache.pb.o shared_memory_struct.pb.o
LIBS := \
	-L../../commonlib4c/src -lcommon -lpthread \
	-L../../commonlib4c/thirdparty/log4cpp/lib -llog4cpp -lpthread \
	-L../../commonlib4c/thirdparty/curl/lib -lcurl \
	-L../../commonlib4c/thirdparty/libevent/lib -levent \
	-L../../commonlib4c/thirdparty/jsoncpp/lib -ljson_linux-gcc-4.1.2_libmt \
	-L../../commonlib4c/thirdparty/mysql/lib -lmysqlclient \
	-L../../commonlib4c/thirdparty/xerces-c/lib -lxerces-c \
	-L../../commonlib4c/thirdparty/fastdb/lib -lfastdb \
	-L../../protobuf/lib -lprotobuf
INC := \
	-I../../commonlib4c/thirdparty/fastdb/include \
	-I../../commonlib4c/src \
	-I../../commonlib4c/thirdparty/log4cpp/include \
	-I../../commonlib4c/thirdparty/curl/include \
	-I../../commonlib4c/thirdparty/libevent/include \
	-I../../commonlib4c/thirdparty/jsoncpp/include \
	-I../../commonlib4c/thirdparty/xerces-c/include \
	-I../../commonlib4c/thirdparty/mysql/include \
	-I../../protobuf/include


CC:=g++
BIN:=binary_log_agent

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
	echo "build done"

.PHONY: 
clean:
	$(RM) -rf *.o
	$(RM) -rf $(LIB)

%.o: %.cpp
	$(CC) -fPIC -c -g -o $@ $< $(INC)

