#ifndef ISOUND_H
#define ISOUND_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IResource;

#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>
#include <Engine/IResources.h>

class ISound {
private:
    static size_t StaticRead(void* ptr, size_t size, size_t nmemb, void *datasource);
    static int StaticSeek(void* datasource, ogg_int64_t offset, int whence);
    static int StaticCloseFree(void* datasource);
    static int StaticCloseNoFree(void* datasource);
    static long StaticTell(void* datasource);

public:
    SDL_AudioSpec     Format;
    uint32_t          Length = 0;
    uint8_t*          Buffer = NULL;
    uint32_t          Remaining = 0;
    char*             Name = NULL;
    bool              LoadFailed = false;
    bool              StreamFromFile = false;
    SDL_AudioStream*  Stream = NULL;
    IResource*        Resource = NULL;
    uint8_t*          ExtraBuffer = NULL;
    struct Vorbis {
    OggVorbis_File vf;
    vorbis_info* info = NULL;
    Uint32 audio_len;
    }; 
    Vorbis* vorbis_file = NULL;

    bool LoadOGG_RW(IResource* src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
    Vorbis* LoadVorbis(IResource* src, SDL_AudioSpec *spec);
    int ReadVorbis(Vorbis* vorb, void* dst, int size);
    int SeekVorbis(Vorbis* vorb, int64_t pos);
    long long TellVorbis(Vorbis* vorb);
    ISound(const char* filename);
    ISound(const char* filename, bool streamFromFile);
    void Load(const char* filename, bool streamFromFile);
    int  RequestMoreData(int samples, int amount);
    void Seek(int amount);
    long long GetPosition();
    void Cleanup();
};

#endif /* ISOUND_H */
