#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IResources.h>

class IStreamer {
public:
    unsigned char* ptr;
    unsigned char* ptr_start;
    IResource* res = NULL;
    long distance = 0;
};
#endif

#include <Engine/IStreamer.h>

PUBLIC IStreamer::IStreamer(void* pt) {
    this->ptr = (unsigned char*)pt;
    ptr_start = (unsigned char*)pt;
}
PUBLIC IStreamer::IStreamer(IResource* r) {
    res = r;
}

PUBLIC float IStreamer::ReadFloat() {
    float f;
    unsigned int b = ReadUInt32();
    memcpy(&f, &b, sizeof(f));
    return f;
}

PUBLIC size_t IStreamer::Seek(int64_t offset) {
    if (res) {
        return res->Seek(offset, RW_SEEK_SET);
    }
    ptr = ptr_start + offset;
    distance = offset;
    return distance;
}
PUBLIC size_t IStreamer::Skip(int64_t offset) {
    if (res) {
        return res->Seek(offset, RW_SEEK_CUR);
    }
    ptr += offset;
    distance += offset;
    return distance;
}

PUBLIC unsigned char IStreamer::ReadByte() {
    if (res) {
        unsigned char data = 0;
        res->Read(&data, 1 * sizeof(data));
        return data;
    }
    unsigned char data = *ptr;
    ptr++;
    distance++;
    return data;
}

PUBLIC unsigned char* IStreamer::ReadByte4() {
    if (res) {
        unsigned char* data = (unsigned char*)malloc(4);
        res->Read(data, 1 * 4);
        return data;
    }
    unsigned char* data = ptr;
    ptr += 4;
    distance += 4;
    return data;
}
PUBLIC unsigned char* IStreamer::ReadBytes(int n) {
    if (res) {
        unsigned char* data = (unsigned char*)malloc(n);
        res->Read(data, 1 * n);
        return data;
    }
    unsigned char* data = (unsigned char*)malloc(n);
    memcpy(data, ptr, n);
    ptr += n;
    distance += n;
    return data;
}

PUBLIC unsigned short IStreamer::ReadUInt16() {
    if (res) {
        return (unsigned short)(ReadByte() | ReadByte() << 8);
    }
    unsigned short data = 0;
    data += (unsigned char)(*ptr); ptr++;
    data += (unsigned char)(*ptr) << 8; ptr++;
    distance += 2;
    return (unsigned short)data;
}
PUBLIC unsigned short IStreamer::ReadUInt16E() {
    if (res) {
        return (unsigned short)(ReadByte() << 8 | ReadByte());
    }
    unsigned short data = 0;
    data += (unsigned char)(*ptr) << 8; ptr++;
    data += (unsigned char)(*ptr); ptr++;
    distance += 2;
    return (unsigned short)data;
}
PUBLIC unsigned int IStreamer::ReadUInt32() {
    if (res) {
        return ReadByte() | ReadByte() << 8 | ReadByte() << 16 | ReadByte() << 24;
    }
    unsigned int data = 0;
    data += (*ptr) << 0; ptr++;
    data += (*ptr) << 8; ptr++;
    data += (*ptr) << 16; ptr++;
    data += (*ptr) << 24; ptr++;
    distance += 4;
    return (unsigned int)data;
}
PUBLIC unsigned int IStreamer::ReadUInt32BE() {
    if (res) {
        return ReadByte() << 24 | ReadByte() << 16 | ReadByte() << 8 | ReadByte();
    }
    unsigned int data = 0;
    data += (*ptr) << 24; ptr++;
    data += (*ptr) << 16; ptr++;
    data += (*ptr) << 8; ptr++;
    data += (*ptr) << 0; ptr++;
    distance += 4;
    return (unsigned int)data;
}

PUBLIC short IStreamer::ReadInt16() {
    return (short)ReadUInt16();
}
PUBLIC short IStreamer::ReadInt16BE() {
    return (short)ReadUInt16E();
}
PUBLIC int IStreamer::ReadInt32() {
    return (int)ReadUInt32();
}
PUBLIC int IStreamer::ReadInt32BE() {
    return (int)ReadUInt32BE();
}

PUBLIC char* IStreamer::ReadLine() {
    unsigned long start = Distance();
    while (ReadByte() != '\n');

    uint64_t sz = Distance() - start;

    // char* data = (char*)malloc(sz);
    Skip(-sz);

    return (char*)ReadBytes(sz);
}
PUBLIC char* IStreamer::ReadString() {
    unsigned long start = Distance();
    while (ReadByte() != 0);

    uint64_t sz = Distance() - start;

    // char* data = (char*)malloc(sz);
    Skip(-sz);

    return (char*)ReadBytes(sz);
}
PUBLIC char* IStreamer::ReadRSDKString() {
    if (res) {
        unsigned char count = ReadByte();
        char* data = (char*)malloc(count + 1);
        res->Read(data, 1 * count);
        data[count] = 0;
        return data;
    }
    unsigned char count = *ptr;
    ptr++;
    char* data = (char*)malloc(count + 1);
    memcpy(data, ptr, count);
    data[count] = 0;
    ptr += count;
    distance += count + 1;
    return data;
}

PUBLIC unsigned long IStreamer::Decompress(void* dst, int dstLen, void* src, int srcLen) {
    z_stream strm  = {0};
    strm.total_in  = strm.avail_in  = srcLen;
    strm.total_out = strm.avail_out = dstLen;
    strm.next_in   = (Bytef *) src;
    strm.next_out  = (Bytef *) dst;

    strm.zalloc = Z_NULL;
    strm.zfree  = Z_NULL;
    strm.opaque = Z_NULL;

    int err = -1;
    unsigned long ret = -1;

    err = inflateInit2(&strm, (15 + 32)); //15 window bits, and the +32 tells zlib to to detect if using gzip or zlib
    if (err == Z_OK) {
        err = inflate(&strm, Z_FINISH);
        if (err == Z_STREAM_END) {
            ret = strm.total_out;
        }
        else {
             inflateEnd(&strm);
             return err;
        }
    }
    else {
        inflateEnd(&strm);
        return err;
    }

    inflateEnd(&strm);
    return ret;
}

PUBLIC unsigned char* IStreamer::ReadCompressed() {
    unsigned int compressed_size = ReadUInt32() - 4; // 0x47 = 71 - 4 = 67
    unsigned int uncompressed_size = ReadUInt32BE(); // 0x200 = 512

    unsigned char* out = (unsigned char*)malloc(uncompressed_size);

    if (res) {
        unsigned char* in = (unsigned char*)malloc(compressed_size);
        res->Read(in, 1 * compressed_size);

        Decompress(out, uncompressed_size, in, compressed_size);

        free(in);
    }
    else {
        Decompress(out, uncompressed_size, ptr, compressed_size);

        ptr += compressed_size;
        distance += compressed_size;
    }
    return out;
}

PUBLIC unsigned long IStreamer::Distance() {
    return distance;
}

PUBLIC IStreamer IStreamer::GetCompressedStream() {
    return IStreamer(ReadCompressed());
}
