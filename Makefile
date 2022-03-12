CC = gcc
CFLAGS = -g
LIBS = 
INC = ./include
SRC = ./src
TEST = ./test
LIB = ./lib
ALLNEED = jdlib.o

TARGET = $(LIB)/libjd.so

$(TARGET): jdstr.o jdlist.o jdlib.o $(INC)/jdlib.h
	$(CC) jdstr.o jdlist.o $(CFLAGS) -shared -fPIC -o $(TARGET)

jdlib.o: $(SRC)/jdlib.c $(INC)/jdlib.h
	$(CC) -c $(SRC)/jdlib.c -I$(INC) $(CFLAGS)

jdlist: $(TEST)/test_jlist.c jdlist.o $(ALLNEED)
	$(CC) $^ -o $@ -I$(INC) $(CFLAGS)

jdlist.o: $(SRC)/jdlist.c $(INC)/jdlib.h
	$(CC) -c $(SRC)/jdlist.c -I$(INC) $(CFLAGS)

jdstr: $(TEST)/test_jstrs.c jdstr.o $(ALLNEED)
	$(CC) $^ -o $@ -I$(INC) $(CFLAGS)

jdstr.o: $(SRC)/jdstr.c $(INC)/jdlib.h
	$(CC) -c $(SRC)/jdstr.c -I$(INC) $(CFLAGS)

jdtest: $(TEST)/test.c $(TARGET) $(INC)/jdlib.h $(ALLNEED)
	$(CC) $(TEST)/test.c -L$(LIB) -ljd -I$(INC) -o $@

clean:
	rm *.o *.so jd* \
		lib/* -rf
