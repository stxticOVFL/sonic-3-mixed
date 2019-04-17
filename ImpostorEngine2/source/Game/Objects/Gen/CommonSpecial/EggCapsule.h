#ifndef EGGCAPSULE_H
#define EGGCAPSULE_H

class EggCapsule;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class EggCapsule: public Object {
public:    
    
    bool Flying;
    bool Broken;
    Object* Button;
    int TimerX;
    int TimerY;
    bool Left;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    void OnDestroy();
};

#endif /* EGGCAPSULE_H */
