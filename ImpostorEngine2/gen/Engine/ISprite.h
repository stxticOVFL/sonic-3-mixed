#ifndef ISPRITE_H
#define ISPRITE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IApp;
class IGraphics;
class ISprite;

#include <Utils/Standard.h>
#include <Engine/IGraphics.h>
#include "Utils/gifdec.h"

class ISprite {
private:
    bool strBeginsWith(const char* str, const char* suffix);
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
    int Extra;
    int OffX;
    int OffY;
    int SheetNumber;
    int Duration;
    uint BufferID;
    }; 
    struct Animation {
    std::string Name;
    int FrameCount;
    int AnimationSpeed;
    int FrameToLoop;
    int Flags;
    AnimFrame* Frames;
    }; 
    std::vector<Animation> Animations;
    int AnimCount = 0;
    uint32_t TextureID;
    uint32_t PaletteID;
    uint32_t PaletteAltID;
    IGraphics* G = NULL;
    std::string Filename;
    ISprite* LinkedSprite = NULL;
    bool Print = false;
    void* operator new(size_t const size);
    void* operator new(size_t const size, const char* identifier);
    void* operator new(size_t const size, std::nothrow_t const&) noexcept;
    void operator delete(void* const block) noexcept;
    void operator delete(void* const block, const char* identifier) noexcept;

    ISprite(const char* filename, IApp* app);
    ISprite(const char* filename, IApp* app, bool IsPrinting);
    ISprite(const char* filename, IApp* app, int mode);
    ISprite(const char* filename, IApp* app, int mode, bool IsPrinting);
    ~ISprite();
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
    void LoadSprite(std::string filename);
    int FindAnimation(const char* animname);
    int FindAnimation(const char* animname, const bool dir);
    void LinkAnimation(std::vector<Animation> ani);
    void Cleanup();

protected:
    inline bool FindGIF(const char* filename);
};

#endif /* ISPRITE_H */
