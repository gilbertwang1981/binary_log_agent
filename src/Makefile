OBJ:=main.o
INC:=-I../thirdparty/log4cpp/include

CC:=g++
BIN:=binary_log_agent

$(BIN): $(OBJ)
	$(CC) -o $@ $^
	echo "build done"

.PHONY: 
clean:
	$(RM) -rf *.o
	$(RM) -rf $(LIB)

%.o: %.cpp
	$(CC) -fPIC -c -g -o $@ $< $(INC)

