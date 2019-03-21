#ifndef IRESOURCES_H
#define IRESOURCES_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Engine/IResource.h>

class IResources {
public:
    static IResource* Load(const char* path);
    static IResource* Load(const char* path, bool inMemory);
    static IResource* Open(const char* path);
    static bool Close(IResource* res);
    static uint64_t Decompress(void* dst, int dstLen, const void* src, int srcLen);
};

#endif /* IRESOURCES_H */
