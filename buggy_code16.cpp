// File: buggy_code16.cpp
#include <iostream>
#include <vector>
#include <stdexcept>
#include <zlib.h>
#include <string>

using namespace std;

vector<uint8_t> compress_string(const vector<uint8_t>& input) {
    z_stream strm = {};
    int ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                          MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) {
        throw runtime_error("deflateInit2 failed with error " + to_string(ret));
    }

    const uLong max_compressed_size = deflateBound(&strm, input.size());
    vector<uint8_t> output(max_compressed_size);

    strm.next_in = const_cast<Bytef*>(input.data());
    strm.avail_in = input.size();
    strm.next_out = output.data();
    strm.avail_out = static_cast<uInt>(output.size());

    ret = deflate(&strm, Z_FINISH);
    if (ret != Z_STREAM_END) {
        deflateEnd(&strm);
        throw runtime_error("Compression failed with error " + to_string(ret));
    }

    deflateEnd(&strm);
    output.resize(strm.total_out);
    return output;
}

vector<uint8_t> decompress_string(const vector<uint8_t>& input) {
    z_stream strm = {};
    int ret = inflateInit2(&strm, MAX_WBITS);
    if (ret != Z_OK) {
        throw runtime_error("inflateInit2 failed with error " + to_string(ret));
    }

    vector<uint8_t> output;
    constexpr size_t BUFFER_SIZE = 1024;
    uint8_t buffer[BUFFER_SIZE];

    strm.next_in = const_cast<Bytef*>(input.data());
    strm.avail_in = static_cast<uInt>(input.size());

    do {
        strm.next_out = buffer;
        strm.avail_out = BUFFER_SIZE;

        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            inflateEnd(&strm);
            throw runtime_error("Decompression failed with error " + to_string(ret));
        }

        const size_t bytes_written = BUFFER_SIZE - strm.avail_out;
        output.insert(output.end(), buffer, buffer + bytes_written);
    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    return output;
}

int main() {
    string original = "Hello, this is a test string to demonstrate zlib compression and decompression.";
    vector<uint8_t> input(original.begin(), original.end());

    try {
        auto compressed = compress_string(input);
        auto decompressed = decompress_string(compressed);

        cout << "Original size: " << input.size() << endl;
        cout << "Compressed size: " << compressed.size() << endl;
        cout << "Decompressed size: " << decompressed.size() << endl;

        if (input == decompressed) {
            cout << "Success: Decompressed data matches original." << endl;
        } else {
            cout << "Error: Decompressed data does not match original." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}