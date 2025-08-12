// File: buggy_code10.cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdint>

using Bytef = unsigned char;

constexpr int BUFSIZE = 1024;

void error(const char* msg) {
    std::fprintf(stderr, "error: %s\n", msg);
    std::exit(1);
}

void compress_block(Bytef* buf, int length) {
    if (length < 0 || length > 65535) {
        error("invalid length");
    }
    // Write length in big-endian format
    std::putc(static_cast<uint16_t>(length) >> 8, stdout);
    std::putc(static_cast<uint16_t>(length) & 0xFF, stdout);
    if (std::fwrite(buf, 1, length, stdout) != static_cast<size_t>(length)) {
        error("write error");
    }
}

void process(Bytef* buf, std::FILE* in) {
    size_t ret;
    while ((ret = std::fread(buf, 1, BUFSIZE, in)) > 0) {
        compress_block(buf, static_cast<int>(ret));
    }
    if (std::ferror(in)) {
        error("read error");
    }
}

int main(int argc, char* argv[]) {
    std::vector<Bytef> buf(BUFSIZE);

    std::FILE* in = nullptr;
    if (argc > 1) {
        in = std::fopen(argv[1], "rb");
        if (!in) {
            error("could not open input file");
        }
    } else {
        in = stdin;
    }

    process(buf.data(), in);

    if (in != stdin) {
        std::fclose(in);
    }

    return 0;
}