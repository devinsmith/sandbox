# Makefile for xft example

.PHONY: all clean

SRCS = xft.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC? = gcc
RM = rm -f

# These may need to be changed for your environment.
CFLAGS = -Wall -O3
INCLUDES = -I/usr/include/freetype2
LIBS = -lXft -lfontconfig -lX11 -lm

EXE = hello_xft

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pthread $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(EXE)

# Include automatically generated dependency files
-include $(DEPS)

