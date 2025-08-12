CXX = g++

CXXFLAGS = -O3 -std=c++17
LDFLAGS  = 
LIBS     = 
TARGET = main

SRCS = game.cpp 
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
		-rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
