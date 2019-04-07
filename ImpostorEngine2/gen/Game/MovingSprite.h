#ifndef MOVINGSPRITE_H
#define MOVINGSPRITE_H

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

class MovingSprite : public Explosion {
public:
    int Hold = 0;
    uint32_t SubX = 0;
    uint32_t SubY = 0;
    int16_t Gravity = 0x38;
    int Left = 0;
    int Top = 0;
    int Width = 1;
    int Height = 1;
    int OffX = 0;
    int OffY = 0;
    int bufferID = -2;
    int LifeSpan = -1;

    MovingSprite();
    void Update();
    void OnAnimationFinish();
    void Render(int CamX, int CamY);
};

#endif /* MOVINGSPRITE_H */
