/* File: buggy_code12.c */
#include "zlib.h"

int deflateInit_(z_streamp strm, int level, const char *version, int stream_size) {
    if (strm == Z_NULL) return Z_STREAM_ERROR;
    if (version == Z_NULL || version[0] != ZLIB_VERSION[0] ||
        stream_size != sizeof(z_stream)) {
        return Z_VERSION_ERROR;
    }
    return deflateInit2_(strm, level, Z_DEFLATED, MAX_WBITS, DEF_MEM_LEVEL,
                         Z_DEFAULT_STRATEGY, version, stream_size);
}

int deflateInit(z_streamp strm, int level) {
    return deflateInit2_(strm, level, Z_DEFLATED, MAX_WBITS, DEF_MEM_LEVEL,
                        Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(z_stream));
}