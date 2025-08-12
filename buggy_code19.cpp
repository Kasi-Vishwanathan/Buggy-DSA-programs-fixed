// File: buggy_code19.cpp
#include <cstdio>
#include <cstring>
#include <memory>
#include <cstddef>

int process_data(const char* buf, size_t size) {
    int total = 0;
    for (size_t i = 0; i < size; ++i) {
        if (buf[i] == '\0') {
            break;
        }
        total += static_cast<unsigned char>(buf[i]);
    }
    return total;
}

int main() {
    constexpr size_t buffer_size = 1024;
    std::unique_ptr<char[]> buf(new (std::nothrow) char[buffer_size]());
    if (!buf) {
        std::fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    std::strncpy(buf.get(), "test", buffer_size);
    buf[buffer_size - 1] = '\0'; // Ensure null-termination

    int result = process_data(buf.get(), buffer_size);
    std::printf("Result: %d\n", result);

    return 0;
}