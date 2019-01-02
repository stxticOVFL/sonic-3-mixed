#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IGraphics.h>

class ISprite {
public:
    uint8_t* Data = NULL;
    uint16_t Width;
    uint16_t Height;
    uint32_t* Palette = NULL;
    uint32_t* PaletteAlt = NULL;
    int PaletteSize = 0;
    int Paletted = 0;
    int TransparentColorIndex = 0;

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
};
#endif

#include <Engine/IApp.h>
#include <Engine/ISprite.h>
#include <Engine/IGraphics.h>
#include <Engine/IStreamer.h>
#include <Engine/IResources.h>
#include "Utils/gifdec.h"

PUBLIC ISprite::ISprite(const char* filename, IApp* app) {
    IResource* res = IResources::Load(filename, true);
	if (!res) {
		IApp::Print(2, "Couldn't open file '%s'!", filename);
		fflush(stdin);
		return;
	}

    Filename = filename;

    IStreamer stream(res);
    stream.Skip(6);

    Width = stream.ReadUInt16();
    Height = stream.ReadUInt16();

    int fdsz = stream.ReadByte();
    if ((fdsz & 0x80) == 0) {
        IApp::Print(2, "Could not make sprite using '%s' without a palette!", filename);
        return;
    }

    Palette = (uint32_t*)calloc(256, sizeof(uint32_t));
    PaletteAlt = (uint32_t*)calloc(256, sizeof(uint32_t));

    PaletteSize = 1 << ((fdsz & 0x07) + 1);
    TransparentColorIndex = stream.ReadByte();
    // printf("for %s PaletteSize = %d width = %d height = %d\n", filename, PaletteSize, Width, Height);

    stream.Skip(1);

    for (int i = 0; i < PaletteSize; i++) {
        uint8_t* color = stream.ReadBytes(3);
        Palette[i] = color[0] << 16 | color[1] << 8 | color[2];
        free(color);

        if (Palette[i] == 0xFF00FF)
    		TransparentColorIndex = i;
    }
    IResources::Close(res);

	if (TransparentColorIndex == 0xFF)
		TransparentColorIndex = 0;
    if (Palette[0] == 0xFF00FF)
		TransparentColorIndex = 0;
	if (Palette[0] == 0x00F000)
		TransparentColorIndex = 0;

    Data = (uint8_t*)malloc(Width * Height);

    res = IResources::Load(filename, true);

    gd_GIF* gif = gd_open_gif(res);
    gd_get_frame(gif);

	gd_render_frame(gif, Data);
    gd_close_gif(gif);

    IResources::Close(res);

    Paletted = 1;

    G = app->G;
    G->MakeTexture(this);
}

PUBLIC void ISprite::SplitPalette() {
    PaletteSize /= 2;
    memmove(PaletteAlt, Palette + PaletteSize, 4 * PaletteSize);
    Paletted = 2;
}

PUBLIC void ISprite::RotatePaletteLeft(uint32_t* color, int size) {
    uint32_t temp = *color;
    for (int i = 0; i < size - 1; i++) {
        *(color + i) = *(color + i + 1);
    }
    *(color + size - 1) = temp;
}
PUBLIC void ISprite::RotatePaletteRight(uint32_t* color, int size) {
    uint32_t temp = *(color + size - 1);
    for (int i = size - 1; i >= 1; i--) {
        *(color + i) = *(color + i - 1);
    }
    *color = temp;
}

PUBLIC void ISprite::SetPalette(int index, uint32_t color) {
    // if GL, write just that color change to palette texture
}

PUBLIC void ISprite::UpdatePalette() {
    // if GL, write whole palette to palette texture
    G->UpdatePalette(this);
}

PUBLIC void ISprite::LinkPalette(ISprite* other) {
    if (other == this) return;

    free(Palette);
    free(PaletteAlt);
    Palette = other->Palette;
    PaletteAlt = other->PaletteAlt;
    PaletteID = other->PaletteID;
    PaletteAltID = other->PaletteAltID;
}

PUBLIC void ISprite::LoadAnimation(const char* filename) {
    IResource* SpriteFile = IResources::Load(filename);
    if (!SpriteFile) {
        IApp::Print(2, "Couldn't open file '%s'!", filename);
		fflush(stdin);
        exit(0);
    }

    IStreamer reader(SpriteFile);

    IApp::Print(-1, "\"%s\"", filename);

    reader.ReadUInt32BE(); // magic

    reader.ReadUInt32(); //int TotalFrameCount = reader.ReadUInt32();

    bool solid = false;

    int sheets = reader.ReadByte();
    for (int i = 0; i < sheets; i++)
        free(reader.ReadRSDKString());

    int collisionboxes = reader.ReadByte();
    for (int i = 0; i < collisionboxes; i++) {
        char* attr = reader.ReadRSDKString();
        if (!strcmp(attr, "Solid"))
            solid = true;
        free(attr);
    }

    int count = reader.ReadUInt16();

    for (int a = AnimCount; a < AnimCount + count; a++) {
        Animation an;

        an.Name = reader.ReadRSDKString();
        an.FrameCount = reader.ReadUInt16();
        an.AnimationSpeed = reader.ReadUInt16();
        an.FrameToLoop = reader.ReadByte();
        an.Flags = reader.ReadByte(); // 0: Default behavior, 1: Full engine rotation, 2: Partial engine rotation, 3: Static rotation using extra frames, 4: Unknown (used alot in Mania)
        an.Frames = (AnimFrame*)malloc(sizeof(AnimFrame) * an.FrameCount);
		IApp::Print(-1, "    \"%s\" (%d) (Flags: %02X, FtL: %d, Spd: %d, Frames: %d)", an.Name, a, an.Flags, an.FrameToLoop, an.AnimationSpeed, an.FrameCount);
        for (int i = 0; i < an.FrameCount; i++) {
            an.Frames[i].SheetNumber = reader.ReadByte();
            an.Frames[i].Duration = reader.ReadInt16();
            reader.ReadUInt16(); //int ID = reader.ReadUInt16();
            an.Frames[i].X = reader.ReadUInt16();
            an.Frames[i].Y = reader.ReadUInt16();
            an.Frames[i].W = reader.ReadUInt16();
            an.Frames[i].H = reader.ReadUInt16();
            an.Frames[i].OffX = reader.ReadInt16(); // Center X
            an.Frames[i].OffY = reader.ReadInt16(); // Center Y
            for (int h = 0; h < collisionboxes; h++) {
                //skipBytes(SpriteFile, 16);
                reader.ReadUInt16(); // Left
                reader.ReadUInt16(); // Top
                reader.ReadUInt16(); // Right
                reader.ReadUInt16(); // Bottom
            }
            G->MakeFrameBufferID(this, an.Frames + i);
        }
        Animations.push_back(an);
    }
    AnimCount += count;
    IResources::Close(SpriteFile);
    // printf("\n");
}

PUBLIC void ISprite::LinkAnimation(vector<Animation> ani) {
    Animations = ani;
}

PUBLIC void ISprite::Cleanup() {
    for (int a = 0; a < AnimCount; a++) {
        if (Animations[a].Name) {
            free(Animations[a].Name);
            Animations[a].Name = NULL;
        }
        if (Animations[a].Frames) {
            for (int f = 0; f < Animations[a].FrameCount; f++)
                G->DeleteBufferID(Animations[a].Frames[f].BufferID);
            free(Animations[a].Frames);
            Animations[a].Frames = NULL;
        }
    }
    if (Data) {
        free(Data);
        Data = NULL;
    }

    free(Palette);
    free(PaletteAlt);
}
