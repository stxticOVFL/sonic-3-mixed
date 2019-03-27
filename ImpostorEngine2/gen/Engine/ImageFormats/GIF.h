#ifndef GIF_H
#define GIF_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Engine/IStreamer.h>

class GIF {
public:
    Uint32* Colors = NULL;
    Uint8*  Data = NULL;
    Uint32  Width = 0;
    Uint32  Height = 0;
    Uint32  TransparentColorIndex = 0;
    vector<Uint8*> Frames;

    static Uint32 ReadCode(IStreamer* stream, int codeSize, int* blockLength, int* bitCache, int* bitCacheLength);
    static void   WriteCode(IStreamer* stream, int* offset, int* partial, Uint8* buffer, uint16_t key, int key_size);
           void   WriteFrame(IStreamer* stream, Uint8* data);
    static void*  NewNode(Uint16 key, int degree);
    static void*  NewTree(int degree, int* nkeys);
    static void   FreeTree(void* root, int degree);
    static GIF*   Load(const char* filename);
    static bool   Save(GIF* gif, const char* filename);
    bool Save(const char* filename);
    ~GIF();
};

#endif /* GIF_H */
