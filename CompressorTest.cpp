#include "Compressor.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
	// Data to compress
	std::string data = "Hellooooooooooo, World!";

	// Compress the data
	std::vector<uint8_t> compressed(data.size() * 2);  // Assume worst-case expansion for simplicity
	uint64_t compressedSize = CCompressor::Compress((uint8_t*)data.data(), data.size(), compressed.data());

	// Decompress the data
	std::vector<uint8_t> decompressed(data.size());
	uint64_t decompressedSize = CCompressor::Decompress(compressed.data(), compressedSize, decompressed.data());

	// Print original, compressed, and decompressed sizes
	std::cout << "Original Size: " << data.size() << " bytes" << std::endl;
	std::cout << "Compressed Size: " << compressedSize << " bytes" << std::endl;
	std::cout << "Decompressed Size: " << decompressedSize << " bytes" << std::endl;

	// Print original and decompressed data
	std::cout << "Original Data: " << data << std::endl;
	std::cout << "Decompressed Data: " << std::string(decompressed.begin(), decompressed.end()) << std::endl;

	// Check assertions
	assert(compressedSize < decompressedSize && "compressedSize should be less than decompressedSize");
	assert(decompressedSize == data.size() && "decompressedSize should be equal to data.size()");
	assert(std::string(decompressed.begin(), decompressed.end()) == data && "std::string(decompressed.begin(), decompressed.end()) should be equal to data");
	
	// Indicate that the test passed successfully
	std::cout << "PASS" << std::endl;
	return 0;
}
