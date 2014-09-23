CXXFLAGS = -std=c++11 -I../../

test: main.o test_sse2.o test_sse3.o test_sse4_1.o test_avx.o test_avx2.o test_null.o
	g++ $^ -lpthread -o test

main.o: main.cc
	g++ main.cc $(CXXFLAGS) -c -o main.o

# inclusion of NONE_NULL is mandatory
test_null.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -o test_null.o
#	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_USER_ARCH_INFO=Arch::NONE_NULL -o test_null.o

test_sse2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE2 -msse2 -o test_sse2.o

test_sse3.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE3 -msse3 -o test_sse3.o

test_sse4_1.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE4_1 -msse4.1 -o test_sse4_1.o

test_avx.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_AVX -mavx -o test_avx.o

test_avx2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_AVX2 -mavx2 -o test_avx2.o

