#pragma once

#include <cstdint>

class CCompressor {
protected:
	static constexpr size_t MinChunkSize = 3;
	static constexpr uint8_t ChunkSame = 0, ChunkMixed = 1;

	static bool GetNextChunkSame(uint8_t* src, uint64_t srcSize, uint64_t pos, uint64_t* left, uint64_t* right);
	static void PutChunkMixed(uint8_t* src, uint64_t* i, uint64_t iEnd, uint8_t* dest, uint64_t* destPos);

public:
	static uint64_t Compress(uint8_t* src, uint64_t srcSize, uint8_t* dest);
	static uint64_t Decompress(uint8_t* src, uint64_t srcSize, uint8_t* dest);
};
