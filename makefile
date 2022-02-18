CC = gcc
CFLAGS = -g
LIBS = 
INC = ./include
SRC = ./src
TEST = ./test
LIB = ./lib

TARGET = $(LIB)/libjd.so

$(TARGET): jdstr.o $(INC)/jdlib.h
	$(CC) jdstr.o $(CFLAGS) -shared -fPIC -o $(TARGET)

jdstr: $(TEST)/test_jstrs.c jdstr.o
	$(CC) $^ -o jdstr -I$(INC) $(CFLAGS)

jdstr.o: $(SRC)/jdstr.c $(INC)/jdlib.h
	$(CC) -c $(SRC)/jdstr.c -I$(INC) $(CFLAGS)

jdtest: $(TEST)/test.c $(TARGET) $(INC)/jdlib.h
	$(CC) $(TEST)/test.c -L$(LIB) -ljd -I$(INC) -o jdtest

clean:
	rm *.o *.so jd* \
		lib/* -rf
