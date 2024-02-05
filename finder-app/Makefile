# Makefile for writer application

# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra

# Default target: build the writer application
.DEFAULT_GOAL := writer

# Cross-compiler settings (if CROSS_COMPILE is specified)
ifdef CROSS_COMPILE
    CC := $(CROSS_COMPILE)$(CC)
endif

# Source files
SRCS := writer.c

# Object files
OBJS := $(SRCS:.c=.o)

# Targets
writer: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f writer $(OBJS)
