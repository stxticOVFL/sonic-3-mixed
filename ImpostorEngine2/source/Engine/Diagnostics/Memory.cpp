#if INTERFACE

#include <Utils/Standard.h>

class Memory {
private:
    static vector<void*> TrackedMemory;
    static vector<size_t> TrackedSizes;
    static vector<const char*> TrackedMemoryNames;
};
#endif

#include <Engine/IApp.h>
#include <Engine/Diagnostics/Memory.h>

vector<void*> Memory::TrackedMemory;
vector<size_t> Memory::TrackedSizes;
vector<const char*> Memory::TrackedMemoryNames;

PUBLIC STATIC void*  Memory::Malloc(size_t size) {
    void* mem = malloc(size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(size);
        TrackedMemoryNames.push_back(NULL);
    }
    return mem;
}
PUBLIC STATIC void*  Memory::Calloc(size_t count, size_t size) {
    void* mem = calloc(count, size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(count * size);
        TrackedMemoryNames.push_back(NULL);
    }
    return mem;
}
PUBLIC STATIC void*  Memory::TrackedMalloc(const char* identifier, size_t size) {
    void* mem = malloc(size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(size);
        TrackedMemoryNames.push_back(identifier);
    }
    return mem;
}
PUBLIC STATIC void*  Memory::TrackedCalloc(const char* identifier, size_t count, size_t size) {
    void* mem = calloc(count, size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(count * size);
        TrackedMemoryNames.push_back(identifier);
    }
    return mem;
}
PUBLIC STATIC void   Memory::Track(void* pointer, const char* identifier) {
    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        if (TrackedMemory[i] == pointer) {
            TrackedMemoryNames[i] = identifier;
            return;
        }
    }
}
PUBLIC STATIC void   Memory::Track(void* pointer, size_t size, const char* identifier) {
    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        if (TrackedMemory[i] == pointer) {
            TrackedSizes[i] = size;
            TrackedMemoryNames[i] = identifier;
            return;
        }
    }

    TrackedMemory.push_back(pointer);
    TrackedSizes.push_back(size);
    TrackedMemoryNames.push_back(identifier);
}
PUBLIC STATIC void   Memory::TrackLast(const char* identifier) {
    if (TrackedMemoryNames.size() == 0) return;
    TrackedMemoryNames[TrackedMemoryNames.size() - 1] = identifier;
}
PUBLIC STATIC void   Memory::Free(void* pointer) {
    free(pointer);

    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        if (TrackedMemory[i] == pointer) {
            TrackedMemoryNames.erase(TrackedMemoryNames.begin() + i);
            TrackedMemory.erase(TrackedMemory.begin() + i);
            TrackedSizes.erase(TrackedSizes.begin() + i);
            break;
        }
    }
}

PUBLIC STATIC void   Memory::ClearTrackedMemory() {
    TrackedMemoryNames.clear();
    TrackedMemory.clear();
    TrackedSizes.clear();
}
PUBLIC STATIC size_t Memory::CheckLeak() {
    size_t total = 0;
    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        total += TrackedSizes[i];
    }
    return total;
}
PUBLIC STATIC void   Memory::PrintLeak() {
    size_t total = 0;
    IApp::Print(-1, "Printing unfreed memory...");
    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        IApp::Print(-1, " : %p [%zu bytes] (%s)", TrackedMemory[i], TrackedSizes[i], TrackedMemoryNames[i] ? TrackedMemoryNames[i] : "no name");
        total += TrackedSizes[i];
    }
    IApp::Print(-1, "Total: %zu bytes (%.3f MB)", total, total / 1024 / 1024.0);
}