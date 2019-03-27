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
	static void FormatPath(const char* path);
	static void FormatPath(const char* path, int mode);
	static IResource* Load(const char* bpath);
	static IResource* Load(const char* bpath, int mode);
	static IResource* Load(const char* bpath, bool inMemory);
	static IResource* Open(const char* bpath);
	static IResource* Load(const char* bpath, bool inMemory, int mode);
	static IResource* Open(const char* bpath, int mode);
	static bool Close(IResource* res);
	static uint64_t Decompress(void* dst, int dstLen, const void* src, int srcLen);

	//work pls
	static int StrCopy(char* dest, char* src);
	static int StrAdd(char* dest, char* src);
};

#endif /* IRESOURCES_H */
