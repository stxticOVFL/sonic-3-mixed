#ifndef LEVELSCENEEXT_H
#define LEVELSCENEEXT_H

#include <Engine/ISprite.h>

struct TileCfg {
    unsigned char Collision[16];
    bool HasCollision[16];
    bool IsCeiling;
	/// <summary>
	/// Angle, Physics, Momentum, Unknown, Special. In that order.
	/// </summary>
    unsigned char Config[5];
};

struct ScrollingInfo {
    int RelativeX;
    int ConstantX;
    char Behaviour;
    char DrawLayer;
};

struct ScrollingIndex {
    int  Index;
    int  Size;
    int* TileBuffers = NULL;
};

struct Layer {
    std::string Name;
    bool Visible = true;

    bool IsScrollingVertical = false;
    int InfoCount;
    int ScrollIndexCount;
    ScrollingInfo* Info = NULL;
    ScrollingIndex* ScrollIndexes = NULL;

    int Width = 0;
    int Height = 0;
    int RelativeY = 0x0100;
    int ConstantY = 0x0000;
    short* Tiles = NULL;
    short* TilesBackup = NULL;
    short* TileOffsetY = NULL;

    int OffsetX = 0x0000;
    int OffsetY = 0x0000;
    bool UseDeltaCameraX = false;
    bool UseDeltaCameraY = false;

    int8_t* Deform = NULL;

	bool NoBuffer = false;

    int Flags = 0x0000;
};

struct ObjectDefinition {

};

struct PlaneSwitch {
    int X;
    int Y;
    int Flags;
    int Size;
    int Angle;
    bool OnPath;
};

struct SceneData {
    short     layerCount;
    Layer     Layers[10];
    TileCfg*  tiles1;
    TileCfg*  tiles2;
    ISprite*  tileTex;

    int*      animatedTileFrames;
    int       animatedTilesCount = 0;
    int**     animatedTileDurations = NULL;
    short*    IsAnims;

    short            ObjectDefinitionCount;
    ObjectDefinition objectDefinitions[0xFF];

    int       CameraLayer;
};

#endif /* LEVELSCENEEXT_H */
