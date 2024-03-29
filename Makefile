AR = ar
CXX = g++
CXXFLAGS = -std=c++2a -Wall -O2 -march=x86-64 -fno-rtti
LDFLAGS = -s -static

SRC = Compressor.cpp
OBJ = $(SRC:.cpp=.o)
DEST = Compressor.a
TEST_SRC = CompressorTest.cpp
TEST_DEST = CompressorTest.exe

build: varsized_int $(OBJ)
	$(AR) r -o $(DEST) $(OBJ)

build-test: build
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(DEST) VarsizedInt.cpp/VarsizedInt.a -o $(TEST_DEST) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

varsized_int:
	$(MAKE) -C VarsizedInt.cpp

clean:
	$(MAKE) -C VarsizedInt.cpp clean
	rm -f $(OBJ) $(DEST) $(TEST_DEST)
