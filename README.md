# Compressor - Simple Repeated Characters Compression Algorithm

This C++ package provides a basic implementation of a symmetric compression algorithm designed for sequences containing repeated characters. The algorithm aims to reduce the size of data by efficiently encoding repeated character chunks.

## Installation

To use this package, you can clone the repository and compile it using a C++ compiler:

```bash
git clone https://github.com/NIR3X/Compressor.cpp --recurse-submodules
cd Compressor.cpp
make
```

## Usage

Here is an example of how to use the Compressor package in your C++ application:

```cpp
#include "Compressor.h"
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

	return 0;
}
```
In this example, the Compressor package compresses the input data, and then decompresses it, demonstrating the basic usage of the compression and decompression functionalities. Adjust the package integration as needed for your specific use case.

## License
[![GNU AGPLv3 Image](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.html)  

This program is Free Software: You can use, study share and improve it at your
will. Specifically you can redistribute and/or modify it under the terms of the
[GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html) as
published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
