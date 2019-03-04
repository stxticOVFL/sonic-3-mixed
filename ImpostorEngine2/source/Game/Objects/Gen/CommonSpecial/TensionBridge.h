#ifndef TENSIONBRIDGE_H
#define TENSIONBRIDGE_H

class TensionBridge;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TensionBridge: public Object {
public:    
    
    int Count;
    int MaxDepress;
    int CurSegment;
    Object* Children[16];
    int BrakeIndexes[16];
    bool Broken;
    int Angled;
    bool Triggered;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* TENSIONBRIDGE_H */
