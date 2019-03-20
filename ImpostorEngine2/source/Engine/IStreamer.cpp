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

/// Read functions
PUBLIC unsigned char  IStreamer::ReadByte() {
    if (res) {
        unsigned char data = 0;
        res->Read(&data, 1);
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
PUBLIC unsigned char* IStreamer::ReadBytesTo(unsigned char* data, int n) {
    if (res) {
        res->Read(data, n);
        return data;
    }
    memcpy(data, ptr, n);
    ptr += n;
    distance += n;
    return data;
}

PUBLIC unsigned short IStreamer::ReadUInt16() {
	unsigned short data = 0;
	if (res) {
		res->Read(&data, sizeof(data));
		return data;
	}
	memcpy(&data, ptr, sizeof(data));
	ptr += sizeof(data);
	distance += sizeof(data);
	return data;
}
PUBLIC unsigned short IStreamer::ReadUInt16BE() {
    return (unsigned short)(ReadByte() << 8 | ReadByte());
}
PUBLIC unsigned int   IStreamer::ReadUInt32() {
    unsigned int data = 0;
	if (res) {
		res->Read(&data, sizeof(data));
		return data;
	}
	memcpy(&data, ptr, sizeof(data));
	ptr += sizeof(data);
	distance += sizeof(data);
	return data;
}
PUBLIC unsigned int   IStreamer::ReadUInt32BE() {
    return ReadByte() << 24 | ReadByte() << 16 | ReadByte() << 8 | ReadByte();
}

PUBLIC signed short   IStreamer::ReadInt16() {
    return (signed short)ReadUInt16();
}
PUBLIC signed short   IStreamer::ReadInt16BE() {
    return (signed short)ReadUInt16BE();
}
PUBLIC signed int     IStreamer::ReadInt32() {
    return (signed int)ReadUInt32();
}
PUBLIC signed int     IStreamer::ReadInt32BE() {
    return (signed int)ReadUInt32BE();
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

PUBLIC char* IStreamer::ReadRSDKUnicodeString() {
	if (res) {
		unsigned char count = ReadUInt16();
		char* data = (char*)malloc(count + 1);
		for (int i = 0; i < count; i++)
		{
			data[i] = ReadByte();
			ReadByte();
		}
		//res->Read(data, 1 * count);
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

/// Write functions
PUBLIC void IStreamer::WriteByte(unsigned char data) {
    if (res) {
        res->Write(&data, sizeof(data));
        return;
    }
    *ptr = data;
    ptr++;
    distance++;
}
PUBLIC void IStreamer::WriteBytes(unsigned char* data, int n) {
    if (res) {
        res->Write(data, n);
        return;
    }
    memcpy(ptr, data, n);
    ptr += n;
    distance += n;
}

PUBLIC void IStreamer::WriteUInt16(unsigned short data) {
    WriteBytes((uint8_t*)&data, sizeof(data));
}
PUBLIC void IStreamer::WriteUInt16BE(unsigned short data) {
    WriteByte(data >> 8 & 0xFF);
    WriteByte(data & 0xFF);
}
PUBLIC void IStreamer::WriteUInt32(unsigned int data) {
    WriteBytes((uint8_t*)&data, sizeof(data));
}
PUBLIC void IStreamer::WriteUInt32BE(unsigned int data) {
    WriteByte(data >> 24 & 0xFF);
    WriteByte(data >> 16 & 0xFF);
    WriteByte(data >> 8 & 0xFF);
    WriteByte(data & 0xFF);
}

PUBLIC void IStreamer::WriteInt16(signed short data) {
    return WriteUInt16((unsigned short)data);
}
PUBLIC void IStreamer::WriteInt16BE(signed short data) {
    return WriteUInt16BE((unsigned short)data);
}
PUBLIC void IStreamer::WriteInt32(signed int data) {
    return WriteUInt32((unsigned int)data);
}
PUBLIC void IStreamer::WriteInt32BE(signed int data) {
    return WriteUInt32BE((unsigned int)data);
}

PUBLIC void IStreamer::WriteString(char* string) {
    while (*string) {
        WriteByte((unsigned char)(*string));
        string++;
    }
    WriteByte(0);
}
PUBLIC void IStreamer::WriteRSDKString(char* string) {
    WriteByte(strlen(string) + 1);
    while (*string) {
        WriteByte((unsigned char)(*string));
        string++;
    }
    WriteByte(0);
}

PUBLIC unsigned long  IStreamer::Decompress(void* dst, int dstLen, void* src, int srcLen) {
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
PUBLIC unsigned long  IStreamer::Distance() {
	if (res) {
		return res->Position();
	}
    return distance;
}

PUBLIC IStreamer IStreamer::GetCompressedStream() {
    return IStreamer(ReadCompressed());
}
