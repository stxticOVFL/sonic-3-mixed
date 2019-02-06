#ifndef BREAKABLEWALL_H
#define BREAKABLEWALL_H

class BreakableWall;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BreakableWall: public Object {
public:    
    
    int Behavior;
    bool LevelTriggered;
    
    void Create();
    void DrawAIZ(int CamX, int CamY);
    void DrawHCZ(int CamX, int CamY);
    void DrawMGZ(int CamX, int CamY);
    void BreakHCZ(int HitSide);
    void BreakMGZ(int HitSide);
    void Update();
    void Render(int CamX, int CamY);
    int OnBreakHorizontal(int PlayerID, int HitFrom);
};

#endif /* BREAKABLEWALL_H */
