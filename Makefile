CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread
SRC = src/main.cpp src/ThreadPool.cpp src/Logger.cpp
INCLUDES = -Iinclude
TARGET = server

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f logs/server.log