#ifndef IRESOURCES_H
#define IRESOURCES_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL


#include <Engine/IResource.h>

class IResources {
public:
	static const char* FormatPath(const char* path, int mode);
	static IResource* Load(const char* bpath, int mode = 0);
	static IResource* Load(const char* bpath, bool inMemory, int mode = 0);
	static IResource* Open(const char* bpath, int mode = 0);
	static bool Close(IResource* res);
	static uint64_t Decompress(void* dst, int dstLen, const void* src, int srcLen);
};
#endif

