CC = gcc
CFLAGS = -g
LIBS = 
INC = ./include
SRC = ./src
TEST = ./test
LIB = ./lib

TARGET = $(LIB)/libjd.so

$(TARGET): jdstr.o jdlist.o $(INC)/jdlib.h
	$(CC) jdstr.o jdlist.o $(CFLAGS) -shared -fPIC -o $(TARGET)

jdlist: $(TEST)/test_jlist.c jdlist.o
	$(CC) $^ -o $@ -I$(INC) $(CFLAGS)

jdlist.o: $(SRC)/jdlist.c $(INC)/jdlib.h
	$(CC) -c $(SRC)/jdlist.c -I$(INC) $(CFLAGS)

jdstr: $(TEST)/test_jstrs.c jdstr.o
	$(CC) $^ -o $@ -I$(INC) $(CFLAGS)

jdstr.o: $(SRC)/jdstr.c $(INC)/jdlib.h
	$(CC) -c $(SRC)/jdstr.c -I$(INC) $(CFLAGS)

jdtest: $(TEST)/test.c $(TARGET) $(INC)/jdlib.h
	$(CC) $(TEST)/test.c -L$(LIB) -ljd -I$(INC) -o $@

clean:
	rm *.o *.so jd* \
		lib/* -rf
