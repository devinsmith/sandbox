# Makefile for dyn_split

.PHONY: all clean

SRCS = test1.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

CC? = gcc
CXX? = g++

# Dependencies
DEP_INCLUDES = `fox-config --cflags`
DEP_LIBS = `fox-config --libs` -lcrypto -lssl

CFLAGS = -Wall -Wextra -g3 -I.

EXE = dyn_split

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXE) $(OBJS) $(DEP_LFLAGS) $(DEP_LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(DEP_INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXE) $(DEPS)

# Include automatically generated dependency files
-include $(DEPS)
