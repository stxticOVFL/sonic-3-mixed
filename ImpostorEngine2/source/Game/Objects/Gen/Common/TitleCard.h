#ifndef TITLECARD_H
#define TITLECARD_H

class TitleCard;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TitleCard: public Object {
public:    
    
    char zoneName[128];
    int actID;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* TITLECARD_H */
