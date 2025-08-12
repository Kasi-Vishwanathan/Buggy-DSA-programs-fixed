// File: buggy_code13.cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "zlib.h"

void test_inflate(Byte *buf, uInt len, int header) {
    int err;
    z_stream d_stream{};
    int initialized = 0;

    d_stream.zalloc = Z_NULL;
    d_stream.zfree = Z_NULL;
    d_stream.opaque = Z_NULL;

    if (header) {
        err = inflateInit(&d_stream);
    } else {
        err = inflateInit2(&d_stream, -MAX_WBITS);
    }
    if (err != Z_OK) {
        fprintf(stderr, "inflateInit error: %d\n", err);
        return;
    }
    initialized = 1;

    d_stream.next_in = buf;
    d_stream.avail_in = len;

    while (d_stream.total_in < len) {
        d_stream.next_out = d_stream.next_in;
        d_stream.avail_out = d_stream.avail_in;

        err = inflate(&d_stream, Z_NO_FLUSH);
        if (err != Z_OK && err != Z_STREAM_END) {
            fprintf(stderr, "inflate error: %d\n", err);
            goto cleanup;
        }
    }

cleanup:
    if (initialized) {
        int end_err = inflateEnd(&d_stream);
        if (end_err != Z_OK) {
            fprintf(stderr, "inflateEnd error: %d\n", end_err);
        }
    }
}

int main() {
    const uInt CHUNK = 16384;
    auto deleter = [](Byte* ptr) { std::free(ptr); };
    std::unique_ptr<Byte, decltype(deleter)> buf_ptr(
        static_cast<Byte*>(std::malloc(CHUNK)), deleter
    );
    Byte* buf = buf_ptr.get();

    if (!buf) {
        std::fprintf(stderr, "Failed to allocate buffer\n");
        return 1;
    }

    std::memset(buf, 0, CHUNK);

    test_inflate(buf, CHUNK, 0);
    test_inflate(buf, CHUNK, 1);

    return 0;
}