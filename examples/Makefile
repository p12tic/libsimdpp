CXXFLAGS = -std=c++11 -I../ -lstdc++

all: vector-add

vector-add:
	g++ $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE4_1 -msse4 vector-add.cpp