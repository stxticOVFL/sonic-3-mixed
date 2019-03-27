#ifndef PNG_H
#define PNG_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Engine/IStreamer.h>

class PNG {
public:
    Uint32* Colors = NULL;
    Uint32* Data = NULL;
    Uint32  Width = 0;
    Uint32  Height = 0;
    Uint32  TransparentColorIndex = 0;
    bool  indexed = false;

    static PNG* Load(const char* filename);
    ~PNG();
};

#endif /* PNG_H */
