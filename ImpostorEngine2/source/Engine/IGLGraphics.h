#ifndef IGLGRAPHICS_H
#define IGLGRAPHICS_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;

#include <Engine/IGraphics.h>

class IGLGraphics : public IGraphics {
public:
    SDL_GLContext Context;
    GLint LocUseTexture;
    GLint LocPosition;
    GLint LocTexCoord;
    GLint LocNormals;
    GLint LocColor;
    GLint LocTexture;
    GLint LocPalette;
    GLint LocPaletteAlt;
    GLint LocTranslate;
    GLint LocRotate;
    GLint LocScale;
    GLint LocWaterLine;
    GLint LocFilterPR;
    GLint LocFilterBW;
    GLint LocFilterFade;
    GLint LocFade;
    GLint LocFadeToWhite;
    GLuint programID;
    GLuint rectBufferID;
    ISprite* TextSprite;
    ISprite* LastSprite = NULL;
    float ColorBlendR = 1.0f;
    float ColorBlendG = 1.0f;
    float ColorBlendB = 1.0f;
    GLint defaultFBO;
    GLuint renderedTexture;
    GLuint renderedTextureQuality;
    GLuint framebufferScreen;
    GLuint framebufferScreenQuality;
    int RetinaMult = 1; ///

    IGLGraphics(IApp* app);
    void Init();
    void SetDisplay(int DesiredWidth, int DesiredHeight, int IsSharp);
    bool CheckGLError(int line);
    bool CheckShaderError(GLuint shader);
    bool CheckProgramError(GLuint prog);
    void Present();
    void Cleanup();
    void MakeTexture(ISprite* sprite);
    void MakeAllTexturesAndFrameBuffers();
    void UpdatePalette(ISprite* sprite);
    int  MakeFrameBufferID(ISprite* sprite, void* fv);
    int  MakeFrameBufferID(ISprite* sprite, void* where, int X, int Y, int W, int H, int OffX, int OffY, int flip);
    int  MakeVertexBuffer(vector<IVertex> vert);
    int  MakeVertexBuffer(IModel* model, bool verts);
    void DeleteBufferID(int buffID);
    void BeginSpriteListBuffer();
    void AddToSpriteListBuffer(ISprite* sprite, int X, int Y, int W, int H, int OffX, int OffY, int Flip);
    int  FinishSpriteListBuffer();
    void SetClip(int x, int y, int w, int h);
    void ClearClip();
    void MakeClone();
    void DrawClone();
    void ClearClone();
    void SetDrawFunc(int a);
    void SetFade(int fade);
    void SetFilter(int filter);
    void DrawTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, Uint32 col);
    void DrawRectangle(int x, int y, int w, int h, Uint32 col);
    void DrawRectangleSkewedH(int x, int y, int w, int h, int sk, Uint32 col);
    void DrawRectangleStroke(int x, int y, int w, int h, Uint32 col);
    void DrawSprite(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip);
    void DrawSpriteSized(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip, int w, int h);
    void DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY);
    void DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY, int SX, int SY);
    void DrawSpriteBuffered(ISprite* sprite, int bufferID, int x, int y, int angle, int flip);
    void DrawSpriteListBuffer(ISprite* sprite, int bufferID, int count, int x, int y);
    void DrawText(int x, int y, const char* string, unsigned int pixel);
    void DrawTextShadow(int x, int y, const char* string, unsigned int pixel);
    void DrawLine(int x0, int y0, int x1, int y1, Uint32 col);
    void DrawModelOn2D(IModel* model, int x, int y, double scale, int rx, int ry, int rz, Uint32 col, bool wireframe);
    void DrawSpriteIn3D(ISprite* sprite, int animation, int frame, int x, int y, int z, double scale, int rx, int ry, int rz);
};

#endif /* IGLGRAPHICS_H */
