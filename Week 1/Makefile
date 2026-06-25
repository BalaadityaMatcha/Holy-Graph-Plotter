CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fsanitize=address

all: tools_demo

tools_demo: main.cpp
	$(CXX) $(CXXFLAGS) -o tools_demo main.cpp

clean:
	rm -f tools_demo*
