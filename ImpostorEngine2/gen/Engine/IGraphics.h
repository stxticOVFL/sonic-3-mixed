#ifndef IGRAPHICS_H
#define IGRAPHICS_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class IModel;
class IApp;

#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>
#include <Engine/ISprite.h>
#include <Engine/IModel.h>

class IGraphics {
private:
    void Flip();
    void ScanLine(long x1, long y1, long x2, long y2);

public:
    IApp * App = NULL;
    SDL_Surface* Screen = NULL;
    uint32_t* FrameBuffer = NULL;
    int WindowWidth = 16;
    int WindowHeight = 9;
    SDL_Window* Window = NULL;
    SDL_Renderer* Renderer = NULL;
    SDL_Surface* WindowScreen = NULL;
    SDL_Texture* ScreenTexture = NULL;
    uint32_t* FrameBufferClone = NULL;
    bool HaveClone = false;
    uint8_t Fade = 0;
    bool    FadeToWhite = false;
    int    PixelScale = 2;
    int    RENDER_WIDTH = 400;
    long    ContourX[800][2];
    int    DivTable[0x100];
    int    WaterPaletteStartLine = 0xFFFF;
    int    Clip[4];
    int8_t* Deform = NULL;
    bool    DoDeform = false;
    int    DrawAlpha = 0xFF;
    int    DrawModeOverlay = false;
    double  MyCos[256];
    double  MySin[256]; ////

    IGraphics();
    IGraphics(IApp* app);
    virtual ~IGraphics();
    virtual void MakeAllTexturesAndFrameBuffers();
    virtual void MakeTexture(ISprite* sprite);
    virtual void UpdatePalette(ISprite* sprite);
    virtual int MakeFrameBufferID(ISprite* sprite, void* f);
    virtual int MakeFrameBufferID(ISprite* sprite, void* where, int X, int Y, int W, int H, int OffX, int OffY, int flip);
    virtual int MakeVertexBuffer(vector<IVertex> vert);
    virtual int MakeVertexBuffer(IModel* m, bool verts);
    virtual void DeleteBufferID(int buffID);
    virtual void BeginSpriteListBuffer();
    virtual void AddToSpriteListBuffer(ISprite* sprite, int X, int Y, int W, int H, int OffX, int OffY, int Flip);
    virtual int FinishSpriteListBuffer();
    virtual void Init();
    virtual void SetDisplay(int DesiredWidth, int DesiredHeight, int IsSharp);
    virtual void Present();
    virtual void Cleanup();
    void SetPixelNormal(int x, int y, uint32_t pixel);
    void SetPixelAlpha(int x, int y, uint32_t pixel);
    void SetPixelAdditive(int x, int y, uint32_t pixel);
    uint32_t FilterNone(uint32_t pixel);
    uint32_t FilterGrayscale(uint32_t pixel);
    uint32_t FilterInversionRadius(uint32_t pixel);
    uint32_t FilterFadeToBlack(uint32_t pixel);
    uint32_t FilterFadeToWhite(uint32_t pixel);
    virtual void SetPixelTrue(SDL_Surface* surface, int x, int y, uint32_t pixel);
    virtual void SetPixel(SDL_Surface* surface, int x, int y, uint32_t pixel);
    virtual uint32_t GetPixelSPR(ISprite* sprite, int x, int y);
    virtual uint32_t GetPixelSPR(ISprite* sprite, int x, int y, uint32_t* pal);
    virtual void SetDrawAlpha(int a);
    virtual void SetDrawFunc(int a);
    virtual void SetFade(int fade);
    virtual void SetFilter(int filter);
    virtual int GetFilter();
    virtual void SetClip(int x, int y, int w, int h);
    virtual void ClearClip();
    virtual void MakeClone();
    virtual void DrawClone();
    virtual void ClearClone();
    virtual void DrawTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, uint32_t col);
    virtual void DrawRectangle(int x, int y, int w, int h, uint32_t col);
    virtual void DrawRectangleSkewedH(int x, int y, int w, int h, int sk, uint32_t col);
    virtual void DrawRectangleStroke(int x, int y, int w, int h, uint32_t col);
    virtual void DrawSprite(SDL_Surface* surface, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY);
    virtual void DrawSpriteNormal(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, bool FlipX, bool FlipY, int RealCenterX, int RealCenterY);
    virtual int CheckAnimation(ISprite* sprite, int animation, int frame);
    virtual void DrawSprite(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip);
    virtual void DrawSpriteSized(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip, int width, int height);
    virtual void DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY);
    virtual void DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY, int SX, int SY);
    virtual void DrawSpriteBuffered(ISprite* sprite, int bufferID, int x, int y, int angle, int flip);
    virtual void DrawSpriteListBuffer(ISprite* sprite, int bufferID, int count, int x, int y);
    virtual void DrawText(int x, int y, const char* string, unsigned int pixel);
    virtual void DrawTextShadow(int x, int y, const char* string, unsigned int pixel);
    virtual void DrawLine(int x0, int y0, int x1, int y1, uint32_t col);
    virtual void DrawTextSprite(ISprite* sprite, int animation, char first, int x, int y, const char* string);
    virtual int MeasureTextSprite(ISprite* sprite, int animation, char first, const char* string);
    virtual void DrawModelOn2D(IModel* model, int x, int y, double scale, int rx, int ry, int rz, uint32_t color, bool wireframe);
    virtual void DrawSpriteIn3D(ISprite* sprite, int animation, int frame, int x, int y, int z, double scale, int rx, int ry, int rz);
    uint32_t ColorBlend(uint32_t color1, uint32_t color2, double percent);
    uint32_t ColorBlendHex(uint32_t color1, uint32_t color2, int percent);
    uint32_t ColorAddHex(uint32_t color1, uint32_t color2, int percent);
    uint32_t GetRetroColor(uint16_t RetroColor);
    void ABGRToRGB(uint32_t ABGR, uint8_t output[4]);
    double easeInBack(double t);
    double easeOutBack(double t);
    double easeInQuad(double t);
    double easeOutQuad(double t);

protected:
    int Filter = 0;

};

#endif /* IGRAPHICS_H */
