#ifndef EGGCAPSULEBUTTON_H
#define EGGCAPSULEBUTTON_H

class EggCapsuleButton;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class EggCapsuleButton: public Object {
public:    
    
    int Down;
    int Pressed;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* EGGCAPSULEBUTTON_H */
