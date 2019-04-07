#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IGraphics.h>
#include "Utils/gifdec.h"

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
};
#endif

#include <Engine/IApp.h>
#include <Engine/ISprite.h>
#include <Engine/IGraphics.h>
#include <Engine/IStreamer.h>
#include <Engine/IResources.h>
#include <algorithm>
#include <fstream>
#include <Engine/ImageFormats/GIF.h>
#include <Engine/ImageFormats/BMP.h>
#include <Engine/ImageFormats/PNG.h>
#include <Engine/Diagnostics/Memory.h>

static std::unordered_map<const char*, gd_GIF*> GifMap;

PUBLIC ISprite::ISprite(const char* filename, IApp* app) {
    App = app;
    G = app->G;
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
    }
    Filename = checkedFilename;
    if (strEndsWith(Filename.c_str(), ".bin")) {
        LoadBin(Filename.c_str());
    } else {
        LoadSprite(Filename);
    }
}

PUBLIC ISprite::ISprite(const char* filename, IApp* app, bool IsPrinting) {
    App = app;
    G = app->G;
    Print = IsPrinting;
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
    }
    Filename = checkedFilename;
    if (strEndsWith(Filename.c_str(), ".bin")) {
        LoadBin(Filename.c_str());
    } else {
        LoadSprite(Filename);
    }
}

PUBLIC ISprite::ISprite(const char* filename, IApp* app, int mode) {
    App = app;
    G = app->G;
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
    }
	std::string outfile;
	switch (mode) {
		case 0: {
			outfile.append("Classic/");
			outfile.append(checkedFilename);
			std::ifstream cfile(outfile);
			if ((bool)cfile) {
				break;
			}
		}
		case 1:
		case 2: {
			outfile.clear();
			outfile.append("Classic/");
			outfile.append(checkedFilename);
			std::ifstream cfile(outfile);
			if ((bool)cfile) {
				break;
			}
		}
		default:
			outfile.clear();
			outfile.append(checkedFilename);
	}
    Filename = checkedFilename;
    if (strEndsWith(Filename.c_str(), ".bin")) {
        LoadBin(Filename.c_str());
    } else {
        LoadSprite(Filename);
    }
}

PUBLIC ISprite::ISprite(const char* filename, IApp* app, int mode, bool IsPrinting) {
    App = app;
    G = app->G;
    Print = IsPrinting;
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
    }
	std::string outfile;
	switch (mode) {
		case 0: {
			outfile.append("Classic/");
			outfile.append(checkedFilename);
			std::ifstream cfile(outfile);
			if ((bool)cfile) {
				break;
			}
		}
		case 1:
		case 2: {
			outfile.clear();
			outfile.append("Classic/");
			outfile.append(checkedFilename);
			std::ifstream cfile(outfile);
			if ((bool)cfile) {
				break;
			}
		}
		default:
			outfile.clear();
			outfile.append(checkedFilename);
	}
    Filename = checkedFilename;
    if (strEndsWith(Filename.c_str(), ".bin")) {
        LoadBin(Filename.c_str());
    } else {
        LoadSprite(Filename);
    }
}

PUBLIC ISprite::~ISprite() {

}

PUBLIC void ISprite::SetTransparentColorIndex(int i) {
    TransparentColorIndex = i;

    Palette[TransparentColorIndex] &= 0xFFFFFF;
    PaletteAlt[TransparentColorIndex] &= 0xFFFFFF;

    for (int i = 0; i < 256; i++) {
        if (i == TransparentColorIndex) continue;

        Palette[i] = 0xFF000000 | Palette[i];
        PaletteAlt[i] = 0xFF000000 | PaletteAlt[i];
    }
}

PUBLIC void ISprite::SetPalette(int i, uint32_t col) {
    if (LinkedSprite != NULL) { LinkedSprite->SetPalette(i, col); return; }

    #if ANDROID
    Palette[i] = ReverseColor(col);
    #else
    Palette[i] = 0xFF000000 | col;
    #endif
}

PUBLIC void ISprite::SetPaletteAlt(int i, uint32_t col) {
    if (LinkedSprite != NULL) { LinkedSprite->SetPaletteAlt(i, col); return; }

    #if ANDROID
    PaletteAlt[i] = ReverseColor(col);
    #else
    PaletteAlt[i] = 0xFF000000 | col;
    #endif
}

PUBLIC void ISprite::SetPalette(int i, int cnt, uint32_t* col) {
	if (LinkedSprite != NULL) { LinkedSprite->SetPalette(i, cnt, col); return; }

    for (int j = i; j < i + cnt; j++)
        SetPalette(j, col[j - i]);
}

PUBLIC void ISprite::SetPaletteAlt(int i, int cnt, uint32_t* col) {
    for (int j = i; j < i + cnt; j++)
        SetPaletteAlt(j, col[j - i]);
}

PUBLIC uint32_t ISprite::GetPalette(int i) {
    if (LinkedSprite != NULL) { return LinkedSprite->GetPalette(i); }

    #if ANDROID
    return ReverseColor(Palette[i] & 0xFFFFFF);
    #else
    return Palette[i] & 0xFFFFFF;
    #endif
}

PUBLIC uint32_t ISprite::GetPaletteAlt(int i) {
    if (LinkedSprite != NULL) { return LinkedSprite->GetPaletteAlt(i); }

    #if ANDROID
    return ReverseColor(PaletteAlt[i] & 0xFFFFFF);
    #else
    return PaletteAlt[i] & 0xFFFFFF;
    #endif
}

PUBLIC uint32_t ISprite::ReverseColor(uint32_t col) {
    return 0xFF000000 | ((col & 0xFF) << 16) | (col & 0xFF00) | ((col & 0xFF0000) >> 16);
}

PUBLIC void ISprite::SplitPalette() {
    PaletteSize /= 2;
    if (!LinkedSprite)
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

PUBLIC void ISprite::UpdatePalette() {
    // if GL, write whole palette to palette texture
    G->UpdatePalette(LinkedSprite ? LinkedSprite : this);
}

PUBLIC void ISprite::LinkPalette(ISprite* other) {
    if (other == this) return;

    if (!LinkedSprite) {
        if (Palette) {
            Memory::Free(Palette);
        }
        if (PaletteAlt) {
            Memory::Free(PaletteAlt);
        }
    }
    Palette = other->Palette;
    PaletteAlt = other->PaletteAlt;
    PaletteID = other->PaletteID;
    PaletteAltID = other->PaletteAltID;
    PaletteSize = other->PaletteSize;
    Paletted = other->Paletted;
    LinkedSprite = other;
}

PUBLIC void ISprite::LoadBin(const char* filename) {
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
        Filename = checkedFilename;
    }
    IResource* BinFile = IResources::Load(checkedFilename.c_str());
    if (BinFile == NULL) {
        IApp::Print(2, "Couldn't open file '%s'!", checkedFilename.c_str());
        fflush(stdin);
        exit(0);
    }

    IStreamer reader(BinFile);

    IApp::Print(-1 + Print, "\"%s\"", Filename);

    reader.ReadUInt32BE(); // Magic

    reader.ReadUInt32(); //int TotalFrameCount = reader.ReadUInt32();

    bool solid = false;

    int sheets = reader.ReadByte();
    for (int i = 0; i < sheets; i++) {
        std::string sheet = reader.ReadRSDKString();
        LoadSprite(sheet);
    }

    int collisionboxes = reader.ReadByte();
    for (int i = 0; i < collisionboxes; i++) {
        std::string attr = reader.ReadRSDKString();
		if (!strcmp(attr.c_str(), "Solid")) {
			solid = true;
		}
    }

    int count = reader.ReadUInt16();

    for (int a = AnimCount; a < AnimCount + count; a++) {
        Animation an;
        an.Name = reader.ReadRSDKString();
        an.FrameCount = reader.ReadUInt16();
        an.AnimationSpeed = reader.ReadUInt16();
        an.FrameToLoop = reader.ReadByte();
        an.Flags = reader.ReadByte(); // 0: Default behavior, 1: Full engine rotation, 2: Partial engine rotation, 3: Static rotation using extra frames, 4: Unknown (used alot in Mania)
        an.Frames = new AnimFrame[an.FrameCount];
		IApp::Print(-1 + Print, "    \"%s\" (%d) (Flags: %02X, FtL: %d, Spd: %d, Frames: %d)", an.Name.c_str(), a, an.Flags, an.FrameToLoop, an.AnimationSpeed, an.FrameCount);
        for (int i = 0; i < an.FrameCount; i++) {
            AnimFrame frame;
            frame.SheetNumber = reader.ReadByte();
            frame.Duration = reader.ReadInt16();
            reader.ReadUInt16(); //int ID = reader.ReadUInt16();
            frame.X = reader.ReadUInt16();
            frame.Y = reader.ReadUInt16();
            frame.W = reader.ReadUInt16();
            frame.H = reader.ReadUInt16();
            frame.OffX = reader.ReadInt16(); // Center X
            frame.OffY = reader.ReadInt16(); // Center Y
            an.Frames[i] = frame;
            for (int h = 0; h < collisionboxes; h++) {
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
    IResources::Close(BinFile);
}

PUBLIC void ISprite::LoadAnimation(const char* filename) {
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
    }
    IResource* SpriteFile = IResources::Load(checkedFilename.c_str());
    if (SpriteFile == NULL) {
        IApp::Print(2, "Couldn't open file '%s'!", checkedFilename.c_str());
        fflush(stdin);
        exit(0);
    }

    IStreamer reader(SpriteFile);

    IApp::Print(-1 + Print, "\"%s\"", checkedFilename.c_str());

    reader.ReadUInt32BE(); // magic

    reader.ReadUInt32(); //int TotalFrameCount = reader.ReadUInt32();

    bool solid = false;

    int sheets = reader.ReadByte();
    for (int i = 0; i < sheets; i++) {
        std::string sheet = reader.ReadRSDKString();
    }

    int collisionboxes = reader.ReadByte();
    for (int i = 0; i < collisionboxes; i++) {
        std::string attr = reader.ReadRSDKString();
		if (!strcmp(attr.c_str(), "Solid")) {
			solid = true;
		}
    }

    int count = reader.ReadUInt16();

    for (int a = AnimCount; a < AnimCount + count; a++) {
        Animation an;
        an.Name = reader.ReadRSDKString();
        an.FrameCount = reader.ReadUInt16();
        an.AnimationSpeed = reader.ReadUInt16();
        an.FrameToLoop = reader.ReadByte();
        an.Flags = reader.ReadByte(); // 0: Default behavior, 1: Full engine rotation, 2: Partial engine rotation, 3: Static rotation using extra frames, 4: Unknown (used alot in Mania)
        an.Frames = new AnimFrame[an.FrameCount];
		IApp::Print(-1 + Print, "    \"%s\" (%d) (Flags: %02X, FtL: %d, Spd: %d, Frames: %d)", an.Name.c_str(), a, an.Flags, an.FrameToLoop, an.AnimationSpeed, an.FrameCount);
        for (int i = 0; i < an.FrameCount; i++) {
            AnimFrame frame;
            frame.SheetNumber = reader.ReadByte();
            frame.Duration = reader.ReadInt16();
            reader.ReadUInt16(); //int ID = reader.ReadUInt16();
            frame.X = reader.ReadUInt16();
            frame.Y = reader.ReadUInt16();
            frame.W = reader.ReadUInt16();
            frame.H = reader.ReadUInt16();
            frame.OffX = reader.ReadInt16(); // Center X
            frame.OffY = reader.ReadInt16(); // Center Y
            an.Frames[i] = frame;
            for (int h = 0; h < collisionboxes; h++) {
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
}

PUBLIC void ISprite::LoadSprite(const char* filename) {
    std::string checkedFilename(filename);
    if (!strBeginsWith(filename, "Sprites") && !strBeginsWith(filename, "Classic/Stages") && !strBeginsWith(filename, "Mixed/Stages")) {
        checkedFilename = "Sprites/" + checkedFilename;
        Filename = checkedFilename;
    }

    TextureID = 0;
    PaletteID = 0;
    PaletteAltID = 0;

    Filename = checkedFilename;

    size_t ticks = SDL_GetTicks();

	int strleng = strlen(Filename.c_str());

	GIF* gif;

	switch (Filename.c_str()[strleng - 3])
	{
		PNG* png;
		BMP* bmp;
	case 'b':
	case 'B':
		bmp = BMP::Load(Filename.c_str());
		gif = BMP::ToGif(bmp);
		//delete[] bmp;
		break;
	case 'p':
	case 'P':
		png = PNG::Load(Filename.c_str());
		gif = PNG::ToGif(png);
		//delete[] png;
		break;
	default:
		gif = GIF::Load(Filename.c_str());
		break;
	}

    if (!LinkedSprite) {
        if (Palette) {
            Memory::Free(Palette);
            Palette = NULL;
        }
        if (PaletteAlt) {
            Memory::Free(PaletteAlt);
            PaletteAlt = NULL;
        }
    }
    
    if (gif) {
        IApp::Print(-1, "GIF load took %zu ms", SDL_GetTicks() - ticks);
        Data = gif->Data;
        Width = gif->Width;
        Height = gif->Height;
        Palette = gif->Colors;
        TransparentColorIndex = gif->TransparentColorIndex;
        PaletteAlt = (uint32_t*)Memory::TrackedCalloc("ISprite::PaletteAlt", 256, sizeof(uint32_t));
    }
    else {
        IApp::Print(2, "GIF could not be loaded! Making 'Empty' Sprite");
		gif = GIF::Load("Classic/Sprites/Dev/NullGfx.gif");
		Data = gif->Data;
		Width = gif->Width;
		Height = gif->Height;
		Palette = gif->Colors;
		TransparentColorIndex = gif->TransparentColorIndex;
		PaletteAlt = (uint32_t*)Memory::TrackedCalloc("ISprite::PaletteAlt", 256, sizeof(uint32_t));
        //exit(-1);
    }

    Paletted = 1;

    G->MakeTexture(this);
    UpdatePalette();
}

PUBLIC void ISprite::LoadSprite(std::string filename) {
    ISprite::LoadSprite(filename.c_str());
}

PROTECTED inline bool ISprite::FindGIF(const char* filename) {
    auto it = GifMap.find(filename);
    if (it == GifMap.end()) {
        return false;
    } else {
        return true;
    }
}

PUBLIC int ISprite::FindAnimation(const char* animname) {
#ifndef NDEBUG
	//assert(this != nullptr);
#endif
	for (int a = 0; a < AnimCount; a++) {
		if (Animations[a].Name[0] == animname[0] && !strcmp(Animations[a].Name.c_str(), animname)) {
			return a;
		}
	}

    App->Print(2, "Couldn't find animation %s in Sprite %s!", animname, Filename.c_str());
    return 0;
}

PUBLIC int ISprite::FindAnimation(const char* animname, const bool dir) {
#ifndef NDEBUG
	//assert(this != nullptr);
#endif

    if (dir) { 
        return FindAnimation(animname);
    }
    std::vector<Animation> Reversed = Animations;
    std::reverse(Reversed.begin(), Reversed.end());

    for (int a = 0; a < AnimCount; a++) {
        if (Reversed[a].Name[0] == animname[0] && !strcmp(Reversed[a].Name.c_str(), animname)) {
            return a;
        }
    }
    
    App->Print(2, "Couldn't find animation %s in Sprite %s!", animname, Filename.c_str());
    return 0;
}

PUBLIC void ISprite::LinkAnimation(std::vector<Animation> ani) {
    Animations = ani;
}

PUBLIC void ISprite::Cleanup() {
    for (int a = 0; a < AnimCount; a++) {
        if (Animations.at(a).Frames) {
            for (int f = 0; f < Animations.at(a).FrameCount; f++) {
                G->DeleteBufferID(Animations.at(a).Frames[f].BufferID);
            }
            delete Animations.at(a).Frames;
            Animations.at(a).Frames = NULL;
        }
    }
	Animations.clear();

    if (Data) {
        Memory::Free(Data);
        Data = NULL;
    }

    if (FindGIF(Filename.c_str())) {
        auto it = GifMap.find(Filename.c_str());
        gd_close_gif(it->second);
        GifMap.erase(it);
    }

    if (!LinkedSprite) {
        if (Palette) {
            Memory::Free(Palette);
        }
        if (PaletteAlt) {
            Memory::Free(PaletteAlt);
        }
    }

    Palette = NULL;
    PaletteAlt = NULL;
}

PRIVATE bool ISprite::strBeginsWith(const char* str, const char* suffix) {
    if (str == NULL || suffix == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) {
        return false;
    }

    return 0 == strncmp( str, suffix, suffix_len );
}

PRIVATE bool ISprite::strEndsWith(const char* str, const char* suffix) {
    if (str == NULL || suffix == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) {
        return false;
    }

    return 0 == strncmp( str + str_len - suffix_len, suffix, suffix_len );
}

void* ISprite::operator new(size_t const size) {
    for (;;) {
        if (void* const block = Memory::TrackedMalloc("ISprite", size)) {
            return block;
        }
        if (_callnewh(size) == 0) {
            static const std::bad_alloc nomem;
            _RAISE(nomem);
        }

        // The new handler was successful; try to allocate again...
    }
}

void* ISprite::operator new(size_t size, const char* identifier) {
    for (;;) {
        if (void* const block = Memory::TrackedMalloc(identifier, size)) {
            return block;
        }
        if (_callnewh(size) == 0) {
            static const std::bad_alloc nomem;
            _RAISE(nomem);
        }

        // The new handler was successful; try to allocate again...
    }
}

void* ISprite::operator new(size_t const size, std::nothrow_t const&) noexcept {
    try {
        return operator new(size);
    } catch (...) {
        return nullptr;
    }
}

void ISprite::operator delete(void* const block) noexcept {
    Memory::Free(block);
}

void ISprite::operator delete(void* const block, const char* identifier) noexcept {
    operator delete(block);
}