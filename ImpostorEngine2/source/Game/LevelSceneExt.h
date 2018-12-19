#ifndef LEVELSCENEEXT_H
#define LEVELSCENEEXT_H

#include <Engine/ISprite.h>

struct TileCfg {
    unsigned char Collision[16];
    bool HasCollision[16];
    bool IsCeiling;
    unsigned char Config[5];
};
struct ScrollingInfo {
    int RelativeX;
    int ConstantX;
    char HeatWaveEnabled;
    char Byte2;
};
struct ScrollingIndex {
    int  Index;
    int  Size;
    int* TileBuffers = NULL;
};
struct Layer {
    char Name[50];
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

    int OffsetX = 0x0000;
    int OffsetY = 0x0000;

    int8_t* Deform = NULL;

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
    Layer     layers[10];
    TileCfg*  tiles1;
    TileCfg*  tiles2;
    ISprite*  tileTex;

    int*      animatedTileFrames;
    int       animatedTilesCount = 0;
    int**     animatedTileDurations = NULL;
    short*    isAnims;

    short            objectDefinitionCount;
    ObjectDefinition objectDefinitions[0xFF];

    int       cameraLayer;
};

#endif /* LEVELSCENEEXT_H */
