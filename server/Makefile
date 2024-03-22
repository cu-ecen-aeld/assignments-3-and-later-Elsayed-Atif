
# DONE: clean target and cross-compile target

P=aesdsocket
SOURCES= aesdsocket.c
OBJECTS= $(SOURCES:.c=.o)

all: $(P)

debug: CCFLAGS += -DDEBUG -g
debug: all

$(P).o: $(P).c
	$(CC) $(CCFLAGS) -Wall -std=c11 -D_POSIX_C_SOURCE=200809L -c $(SOURCES)

$(P): $(OBJECTS)
	$(CC) $(LDFLAGS) -lpthread -pthread $(OBJECTS) -o $(P)

clean:
	rm -f $(OBJECTS) $(P)