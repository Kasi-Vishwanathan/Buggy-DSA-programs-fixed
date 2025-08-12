#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

int compress_data(Bytef *source, uLong srcLen, Bytef *dest, uLong *destLen) {
    z_stream stream;
    int ret;

    memset(&stream, 0, sizeof(stream));

    uLong bound = compressBound(srcLen);
    if (*destLen < bound) {
        return Z_BUF_ERROR;
    }

    ret = deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) {
        return ret;
    }

    stream.next_in = source;
    stream.avail_in = srcLen;
    stream.next_out = dest;
    stream.avail_out = *destLen;

    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        deflateEnd(&stream);
        return (ret == Z_OK) ? Z_BUF_ERROR : ret;
    }

    *destLen = stream.total_out;

    deflateEnd(&stream);
    return Z_OK;
}

int main(int argc, char *argv[]) {
    char sourceData[] = "Hello, world!";
    uLong srcLen = sizeof(sourceData);
    Bytef compressed[256];
    uLong compressedLen = sizeof(compressed);

    int result = compress_data((Bytef*)sourceData, srcLen, compressed, &compressedLen);

    if (result == Z_OK) {
        printf("Compression successful. Compressed size: %lu\n", compressedLen);
        printf("Compressed data (hex): ");
        for (uLong i = 0; i < compressedLen; i++) {
            printf("%02X ", compressed[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Compression failed with error code: %d\n", result);
    }

    return 0;
}