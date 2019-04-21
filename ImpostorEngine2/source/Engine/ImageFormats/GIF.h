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
    bool indexed = true;

    static Uint32 ReadCode(IStreamer* stream, int codeSize, int* blockLength, int* bitCache, int* bitCacheLength);
    static GIF* Load(const char* filename);
    ~GIF();
};

#endif /* GIF_H */
