#if INTERFACE

#include <Utils/Standard.h>
#include <stdlib.h>

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

 
// These are the VC operators, Rewritten to use this system.
/*
void* __CRTDECL operator new(size_t const size) {
    for (;;) {
        if (void* const block = Memory::Malloc(size)) {
            return block;
        }
        if (_callnewh(size) == 0) {
            static const std::bad_alloc nomem;
            _RAISE(nomem);
        }

        // The new handler was successful; try to allocate again...
    }
}

void* __CRTDECL operator new(size_t const size, std::nothrow_t const&) noexcept {
    try {
        return operator new(size);
    } catch (...) {
        return nullptr;
    }
}

void* __CRTDECL operator new[](size_t const size) {
	return operator new(size);
}

void* __CRTDECL operator new[](size_t const size, std::nothrow_t const& x) noexcept {
    return operator new(size, x);
}

void __CRTDECL operator delete(void* const block) noexcept {
    Memory::Free(block);
}

void __CRTDECL operator delete(void* block, std::nothrow_t const&) noexcept {
    operator delete(block);
}

void __CRTDECL operator delete(void* block, size_t) noexcept {
    operator delete(block);
}

void __CRTDECL operator delete[](void* block) noexcept {
    operator delete(block);
}

void __CRTDECL operator delete[](void* block, std::nothrow_t const&) noexcept {
    operator delete[](block);
}

void __CRTDECL operator delete[](void* block, size_t) noexcept {
    operator delete[](block);
}
*/

PUBLIC STATIC void* Memory::Malloc(size_t size) {
    void* mem = malloc(size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(size);
        TrackedMemoryNames.push_back(NULL);
    }
    return mem;
}

PUBLIC STATIC void* Memory::Calloc(size_t count, size_t size) {
    void* mem = calloc(count, size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(count * size);
        TrackedMemoryNames.push_back(NULL);
    }
    return mem;
}

PUBLIC STATIC void* Memory::TrackedMalloc(const char* identifier, size_t size) {
    void* mem = malloc(size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(size);
        TrackedMemoryNames.push_back(identifier);
    }
    return mem;
}

PUBLIC STATIC void* Memory::TrackedCalloc(const char* identifier, size_t count, size_t size) {
    void* mem = calloc(count, size);
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(count * size);
        TrackedMemoryNames.push_back(identifier);
    }
    return mem;
}

PUBLIC STATIC void Memory::Free(void* mem) {
    free(mem);

    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        if (TrackedMemory[i] == mem) {
            TrackedMemoryNames.erase(TrackedMemoryNames.begin() + i);
            TrackedMemory.erase(TrackedMemory.begin() + i);
            TrackedSizes.erase(TrackedSizes.begin() + i);
            break;
        }
    }
}

PUBLIC STATIC void Memory::TrackMemory(const char* identifier, void *mem, size_t count, size_t size) {
    if (mem) {
        TrackedMemory.push_back(mem);
        TrackedSizes.push_back(count * size);
        TrackedMemoryNames.push_back(identifier);
    }
}

PUBLIC STATIC void Memory::ClearTrackedMemory() {
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

PUBLIC STATIC void Memory::PrintLeak() {
    size_t total = 0;
    IApp::Print(0, "Printing unfreed memory...");
    for (Uint32 i = 0; i < TrackedMemory.size(); i++) {
        IApp::Print(0, " : %p [%zu bytes] (%s)", TrackedMemory[i], TrackedSizes[i], TrackedMemoryNames[i] ? TrackedMemoryNames[i] : "no name");
        total += TrackedSizes[i];
    }
    IApp::Print(0, "Total: %zu bytes (%.3f MB)", total, total / 1024 / 1024.0);
}