#ifndef FALLINGTILE_H
#define FALLINGTILE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Game/Object.h>
#include <Game/Explosion.h>
#include <Game/LevelScene.h>

class FallingTile : public Explosion {
public:
    int Tile = 0;
    int Hold = 0;
    int16_t grv = 0x38;

    FallingTile();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FALLINGTILE_H */
