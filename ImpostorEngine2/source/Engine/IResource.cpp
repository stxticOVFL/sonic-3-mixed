#if INTERFACE

#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Utils/Minizip.hh>

class IResource {
public:
    SDL_RWops*  RW = NULL;
    const char* path = NULL;
    uint8_t*    Buffer = NULL;

    unzFile uf = NULL;
    unz_file_info64 info;

    bool ZipLoading = false;
};

#endif

#include <Engine/IApp.h>
#include <Engine/IResource.h>

PUBLIC size_t IResource::Read(void* dest, size_t size) {
    if (ZipLoading) {
        int err = unzReadCurrentFile(uf, dest, size);
        if (err < 0) {
            IApp::Print(2, "Error while reading '%s'! (Error Code: %d)", path, err);
        }
        return err;
    }
    else {
        return SDL_RWread(RW, dest, 1, size);
    }
    return 0;
}
PUBLIC size_t IResource::Write(void* src, size_t size) {
    return 0;
}
PUBLIC size_t IResource::Seek(size_t where, int whence) {
    if (ZipLoading) {
        if (whence == RW_SEEK_SET) {
			size_t jim = 0; // unzSetOffset(uf, 0);
            ///*
            if (where > 0) {
                void* temp = malloc(where);
                Read(temp, where);
                free(temp);
            }
            return jim + where;
            //*/
        }
        else if (whence == RW_SEEK_CUR) {
            if (where > 0) {
                void* temp = malloc(where);
                Read(temp, where);
                free(temp);
            }
            return Position() + where;
        }
        return 0;
    }
    else {
        return SDL_RWseek(RW, where, whence);
        // SDL_RWread\(res->RW, ([A-z0-9\-\+\/<>&\(\)]+), ([A-z0-9\-\+\/<>&\(\)]+), ([A-z0-9\-\+\/<>&\(\)]+)\);
    }
    return 0;
}
PUBLIC size_t IResource::Position() {
    if (ZipLoading) {
        return unztell(uf);
    }
    else {
        return SDL_RWtell(RW);
    }
}
PUBLIC size_t IResource::Size() {
    if (ZipLoading) {
        return info.uncompressed_size;
    }
    else {
        return RW->size(RW);
    }
    return 0;
}
