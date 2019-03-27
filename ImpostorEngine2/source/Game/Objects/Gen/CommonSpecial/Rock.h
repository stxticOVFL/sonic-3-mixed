#ifndef ROCK_H
#define ROCK_H

class Rock;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Rock: public Object {
public:    
    
    int i;
    int LastX;
    int RockSize;
    int RockType;
    Sint8 Rock0Pos[32];
    Sint16 Rock0Vels[16];
    Sint8 Rock1Pos[32];
    Sint16 Rock1Vels[16];
    Sint8 Rock2Pos[32];
    Sint16 Rock2Vels[16];
    int Act1RockBitsBinIndex;
    int Act2RockBitsBinIndex;
    int CurrentRockBitsAnimation;
    int RockBitsBinIndex;
    ISprite* RockBitsSprite;
    bool Knux;
    
    CONSTRUCTER Rock();
    void Create();
    void Update();
    void DrawAIZ(int CamX, int CamY);
    void BreakAIZ(int HitSide);
    void Render(int CamX, int CamY);
    int OnBreakVertical(int PlayerID, int HitFrom);
    int OnBreakHorizontal(int PlayerID, int HitFrom);
};

#endif /* ROCK_H */
