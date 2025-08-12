// File: buggy_code2.cpp
#include <zlib.h>
#include <vector>
#include <iostream>
#include <string>

std::vector<unsigned char> compressToZlib(const unsigned char* data, uLong dataLen) {
    uLong compressedSize = compressBound(dataLen);
    std::vector<Bytef> compressedData(compressedSize);

    int ret = compress2(compressedData.data(), &compressedSize, data, dataLen, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return {};
    }

    compressedData.resize(compressedSize);
    return std::vector<unsigned char>(compressedData.begin(), compressedData.end());
}

int main() {
    std::string str = "Hello, this is a test string for zlib compression.";
    std::vector<unsigned char> data(str.begin(), str.end());
    uLong dataLen = static_cast<uLong>(data.size());

    auto result = compressToZlib(data.data(), dataLen);

    if (result.empty()) {
        std::cerr << "Compression failed!" << std::endl;
        return 1;
    }

    std::cout << "Compressed size: " << result.size() << std::endl;

    // Check for zlib header (0x78)
    if (result[0] == 0x78) {
        std::cout << "Header check passed." << std::endl;
    } else {
        std::cerr << "Header check failed." << std::endl;
        return 1;
    }

    return 0;
}