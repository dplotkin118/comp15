CXX      = /usr/sup/bin/clang++
CXXFLAGS = --std=c++11 -Wshadow -Wall -Wextra -g3

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

findpath: findpath.o Location.o graph.o
	$(CXX) -o $@ $^

clean:
	rm -f findpath *.o

# Add some rules for rt website
include Makefile.publish

provide:
	provide comp15 rt README Makefile graph.cpp graph.h findpath.cpp test_commands.in
