#ifndef HANDLAUNCHER_H
#define HANDLAUNCHER_H

class HandLauncher;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HandLauncher: public Object {
public:    
    
    bool Near;
    bool Spinning;
    int outY;
    int outY2;
    int coolDown;
    int lastOutY2;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HANDLAUNCHER_H */
