CC=g++
CFLAGS=-I.
LDFLAGS=ljemalloc
DEPS = p5_utils.h
OBJ  = jmain.o p5_utils.o
%.o: %.cpp $(DEPS)
        $(CC)  -c -o $@ $< $(CFLAGS)
je_malloc : $(OBJ)
        g++  -std=gnu99 -Wall -Wsign-compare -pipe -O2 -L${JEMALLOC_PATH}/lib -ljemalloc -lrt -o $@ $^ $(CFLAGS)
