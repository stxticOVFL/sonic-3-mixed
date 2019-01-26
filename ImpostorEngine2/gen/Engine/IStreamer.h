#ifndef ISTREAMER_H
#define ISTREAMER_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

class IResource;

#include <Utils/Standard.h>
#include <Engine/IResources.h>

class IStreamer {
public:
    unsigned char* ptr;
    unsigned char* ptr_start;
    IResource* res = NULL;
    long distance = 0;

    IStreamer(void* pt);
    IStreamer(IResource* r);
    float ReadFloat();
    size_t Seek(int64_t offset);
    size_t Skip(int64_t offset);
    unsigned char ReadByte();
    unsigned char* ReadByte4();
    unsigned char* ReadBytes(int n);
    unsigned short ReadUInt16();
    unsigned short ReadUInt16E();
    unsigned int ReadUInt32();
    unsigned int ReadUInt32BE();
    short ReadInt16();
    short ReadInt16BE();
    int ReadInt32();
    int ReadInt32BE();
    char* ReadLine();
    char* ReadString();
    char* ReadRSDKString();
    unsigned long Decompress(void* dst, int dstLen, void* src, int srcLen);
    unsigned char* ReadCompressed();
    unsigned long Distance();
    IStreamer GetCompressedStream();
};

#endif /* ISTREAMER_H */
