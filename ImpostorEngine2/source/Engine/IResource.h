#ifndef IRESOURCE_H
#define IRESOURCE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Utils/Minizip.hh>

class IResource {
public:
    SDL_RWops*  RW = NULL;
    const char* path = NULL;
    uint8_t*    Buffer = NULL;
    // unzFile uf = NULL;
    // unz_file_info64 info;
    bool ZipLoading = false;

    size_t Read(void* dest, size_t size);
    size_t Write(void* src, size_t size);
    size_t Seek(size_t where, int whence);
    size_t Position();
    size_t Size();
};

#endif /* IRESOURCE_H */
