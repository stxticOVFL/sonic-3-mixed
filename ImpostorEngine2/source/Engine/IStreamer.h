#ifndef ISTREAMER_H
#define ISTREAMER_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IResource;

#include <Utils/Standard.h>
#include <Engine/IResources.h>

class IStreamer {
public:
    unsigned char* ptr;
    unsigned char* ptr_start;
    IResource* res = NULL;
    long distance = 0;
    bool ExternalAllocation = false;
    void* operator new(size_t const size) noexcept;
    void* operator new(size_t const size, std::nothrow_t const&) noexcept;
    void operator delete(void* const block) noexcept;

    IStreamer(void* pt);
    IStreamer(unsigned char* pt);
    IStreamer(IResource* r);
    ~IStreamer();
    float ReadFloat();
    size_t Seek(int64_t offset);
    size_t Skip(int64_t offset);
    unsigned char  ReadByte();
    unsigned char* ReadByte4();
    unsigned char* ReadBytes(int n);
    unsigned char* ReadBytesTo(unsigned char* data, int n);
    unsigned short ReadUInt16();
    unsigned short ReadUInt16BE();
    unsigned int   ReadUInt32();
    unsigned int   ReadUInt32BE();
    signed short   ReadInt16();
    signed short   ReadInt16BE();
    signed int     ReadInt32();
    signed int     ReadInt32BE();
    char* ReadLine();
    char* ReadString();
    std::string ReadRSDKString();
    char* ReadRSDKUnicodeString();
    void WriteByte(unsigned char data);
    void WriteBytes(unsigned char* data, int n);
    void WriteUInt16(unsigned short data);
    void WriteUInt16BE(unsigned short data);
    void WriteUInt32(unsigned int data);
    void WriteUInt32BE(unsigned int data);
    void WriteInt16(signed short data);
    void WriteInt16BE(signed short data);
    void WriteInt32(signed int data);
    void WriteInt32BE(signed int data);
    void WriteString(char* string);
    void WriteRSDKString(char* string);
    unsigned long Decompress(void* dst, int dstLen, void* src, int srcLen);
    unsigned char* ReadCompressed();
    unsigned long  Distance();
    IStreamer GetCompressedStream();
};

#endif /* ISTREAMER_H */
