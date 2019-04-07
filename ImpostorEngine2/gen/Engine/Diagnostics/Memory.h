#ifndef MEMORY_H
#define MEMORY_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <stdlib.h>

class Memory {
private:
    static vector<void*> TrackedMemory;
    static vector<size_t> TrackedSizes;
    static vector<const char*> TrackedMemoryNames;


public:
    static void* Malloc(size_t size);
    static void* Calloc(size_t count, size_t size);
    static void* TrackedMalloc(const char* identifier, size_t size);
    static void* TrackedCalloc(const char* identifier, size_t count, size_t size);
    static void Free(void* mem);
    static void TrackMemory(const char* identifier, void *mem, size_t count, size_t size);
    static void ClearTrackedMemory();
    static size_t CheckLeak();
    static void PrintLeak();
};

#endif /* MEMORY_H */
