#ifndef DOOR_H
#define DOOR_H

class Door;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Door: public Object {
public:    
    
    int DoorType;
    bool Horizontal;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* DOOR_H */
