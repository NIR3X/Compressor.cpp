#include "Compressor.h"
#include "VarsizedInt.cpp/VarsizedInt.h"

bool CCompressor::GetNextChunkSame(uint8_t* src, uint64_t srcSize, uint64_t pos, uint64_t* left, uint64_t* right) {
	int16_t chunkValue = -1;
	uint64_t chunkSize = 0;
	for (uint64_t i = pos; i < srcSize; ++i) {
		uint8_t curr = src[i];
		if (chunkValue == curr) {
			++chunkSize;
		}
		if (chunkValue != curr || i == srcSize - 1) {
			if (chunkSize >= MinChunkSize) {
				if (chunkValue == curr) {
					*right = i + 1;
				} else {
					*right = i;
				}
				return true;
			}
			chunkValue = curr;
			chunkSize = 1;
			*left = i;
		}
	}
	return false;
}

void CCompressor::PutChunkMixed(uint8_t* src, uint64_t* i, uint64_t iEnd, uint8_t* dest, uint64_t* destPos) {
	uint64_t i_ = *i, destPos_ = *destPos, chunkMixedSize = iEnd - i_;
	if (chunkMixedSize > 0) {
		destPos_ += CVarsizedInt::Encode(&dest[destPos_], (chunkMixedSize << 1) | ChunkMixed);
		for (uint64_t j = 0; j < chunkMixedSize; ++j, ++i_, ++destPos_) {
			dest[destPos_] = src[i_];
		}
		*i = i_;
		*destPos = destPos_;
	}
}

uint64_t CCompressor::Compress(uint8_t* src, uint64_t srcSize, uint8_t* dest) {
	uint64_t destPos = 0;
	for (uint64_t i = 0; i < srcSize; ++i) {
		uint64_t left = 0, right = 0;
		if (GetNextChunkSame(src, srcSize, i, &left, &right)) {
			PutChunkMixed(src, &i, left, dest, &destPos);
			uint64_t chunkSameSize = right - left;
			destPos += CVarsizedInt::Encode(&dest[destPos], (chunkSameSize << 1) | ChunkSame);
			dest[destPos] = src[left];
			destPos += sizeof(src[left]);
			i += chunkSameSize - 1;
		} else {
			PutChunkMixed(src, &i, srcSize, dest, &destPos);
			return destPos;
		}
	}
	return destPos;
}

uint64_t CCompressor::Decompress(uint8_t* src, uint64_t srcSize, uint8_t* dest) {
	uint64_t destPos = 0;
	for (uint64_t i = 0; i < srcSize;) {
		uint8_t *srcPos = &src[i];
		int chunkSizeSize = CVarsizedInt::ParseSize(srcPos);
		i += chunkSizeSize;
		uint64_t chunkSize = CVarsizedInt::Decode(srcPos);
		uint8_t chunkType = chunkSize & 1; chunkSize >>= 1;
		switch (chunkType) {
			case ChunkSame: {
					uint8_t chunkSameValue = src[i];
					for (uint64_t j = 0; j < chunkSize; ++j, ++destPos) {
						dest[destPos] = chunkSameValue;
					}
					++i;
				}
				break;
			case ChunkMixed:
				for (uint64_t j = 0; j < chunkSize; ++j, ++destPos, ++i) {
					dest[destPos] = src[i];
				}
				break;
		}
	}
	return destPos;
}
