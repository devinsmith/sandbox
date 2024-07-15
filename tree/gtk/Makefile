# Makefile for tree tests

.PHONY: all clean

SRCS = test1.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC? = gcc
CXX? = g++

# Dependencies
DEP_INCLUDES = `pkg-config --cflags gtk+-3.0`
DEP_LIBS = `pkg-config --libs gtk+-3.0`

CFLAGS = -Wall -Wextra -g3 -I.

EXE = tree_test

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(DEP_LFLAGS) $(DEP_LIBS)

.c.o:
	$(CC) $(CFLAGS) $(DEP_INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXE) $(DEPS)

# Include automatically generated dependency files
-include $(DEPS)
