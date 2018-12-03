.POSIX:
.SUFFIXES:

PROJECT=graph

CXXFLAGS=--std=c++11 -W -O
LDLIBS_MAIN=-lm

INCLUDES=-Iinclude -Isparse_matrix/include -Isparse_matrix/avl_tree/include

all: interactive
interactive: obj/main.o
	$(CXX) $(LDFLAGS) $(LDLIBS_MAIN) -o build/$(PROJECT) $^

obj/main.o: main.cpp include/$(PROJECT).hpp
	mkdir -p build
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDLIBS) -c $< -o $@

clean:
	$(RM) -r build
	$(RM) -r obj
	$(RM) -r bin

.PHONY: all interactive clean