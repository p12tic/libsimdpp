CXXFLAGS = -std=c++11 -I../../

test: main.o test_sse2.o test_sse3.o test_sse4_1.o test_avx.o test_avx2.o #test_null.o
	g++ $^ -o test

main.o: main.cc
	g++ main.cc $(CXXFLAGS) -c -o main.o

# Uncomment this if you want to check the non-vectorized variant.
#test_null.o: test.cc
#   g++ test.cc -c $(CXXFLAGS) -o test_null.o

test_sse2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE2 -msse2 \
        -DSIMDPP_EMIT_DISPATCHER=1 \
        -DSIMDPP_DISPATCH_ARCH1=SIMDPP_ARCH_X86_SSE2 \
        -DSIMDPP_DISPATCH_ARCH2=SIMDPP_ARCH_X86_SSE3 \
        -DSIMDPP_DISPATCH_ARCH3=SIMDPP_ARCH_X86_SSE4_1 \
        -DSIMDPP_DISPATCH_ARCH4=SIMDPP_ARCH_X86_AVX \
        -DSIMDPP_DISPATCH_ARCH5=SIMDPP_ARCH_X86_AVX2 \
        -o test_sse2.o

test_sse3.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE3 -msse3 -o test_sse3.o

test_sse4_1.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE4_1 -msse4.1 -o test_sse4_1.o

test_avx.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_AVX -mavx -o test_avx.o

test_avx2.o: test.cc
	g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_AVX2 -mavx2 -o test_avx2.o

