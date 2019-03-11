#ifndef ANIMAL_H
#define ANIMAL_H

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

class Animal : public Explosion {
public:
    int CurrentFrame = 0;
    bool Escaping = false;
    bool HitGround = false;
    uint32_t SubX = 0;
    uint32_t SubY = 0;
    uint32_t Gravity = 0;
    int32_t  JumpSpeed = 0;

    Animal();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* ANIMAL_H */
