#ifndef BREAKABLEBAR_H
#define BREAKABLEBAR_H

class BreakableBar;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BreakableBar: public Object {
public:    
    
    bool Broken;
    bool Horizontal;
    int Delay;
    bool PlayerTouched;
    
    void Create();
    void Update();
    void Break();
    void Render(int CamX, int CamY);
};

#endif /* BREAKABLEBAR_H */
