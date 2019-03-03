#ifndef ISPRITE_H
#define ISPRITE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

class IApp;
class IGraphics;
class ISprite;

#include <Utils/Standard.h>
#include <Engine/IGraphics.h>
#include "Utils/gifdec.h"

class ISprite {
private:
    bool strEndsWith(const char* str, const char* suffix);

public:
    uint8_t* Data = NULL;
    uint16_t Width;
    uint16_t Height;
    uint32_t* Palette = NULL;
    uint32_t* PaletteAlt = NULL;
    int PaletteSize = 0;
    int Paletted = 0;
    int TransparentColorIndex = 0;
    IApp* App = NULL;
    struct AnimFrame {
    int X;
    int Y;
    int W;
    int H;
    int OffX;
    int OffY;
    int SheetNumber;
    int Duration;
    uint BufferID;
    }; 
    struct Animation {
    char* Name;
    int FrameCount;
    int AnimationSpeed;
    int FrameToLoop;
    int Flags;
    AnimFrame* Frames;
    }; 
    vector<Animation> Animations;
    int AnimCount = 0;
    uint32_t TextureID;
    uint32_t PaletteID;
    uint32_t PaletteAltID;
    IGraphics* G = NULL;
    const char* Filename;
    ISprite* LinkedSprite = NULL;
    bool Print = false; //

    ISprite(const char* filename, IApp* app);
    void SetTransparentColorIndex(int i);
    void SetPalette(int i, uint32_t col);
    void SetPaletteAlt(int i, uint32_t col);
    void SetPalette(int i, int cnt, uint32_t* col);
    void SetPaletteAlt(int i, int cnt, uint32_t* col);
    uint32_t GetPalette(int i);
    uint32_t GetPaletteAlt(int i);
    uint32_t ReverseColor(uint32_t col);
    void SplitPalette();
    void RotatePaletteLeft(uint32_t* color, int size);
    void RotatePaletteRight(uint32_t* color, int size);
    void UpdatePalette();
    void LinkPalette(ISprite* other);
    void LoadBin(const char* filename);
    void LoadAnimation(const char* filename);
    void LoadSprite(const char* filename);
    int FindAnimation(const char* animname);
    int FindAnimation(const char* animname, const bool dir);
    void LinkAnimation(vector<Animation> ani);
    void Cleanup();

protected:
    inline bool FindGIF(const char* filename);
};

#endif /* ISPRITE_H */
