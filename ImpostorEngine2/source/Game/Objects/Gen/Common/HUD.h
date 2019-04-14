#ifndef HUD_H
#define HUD_H

class HUD;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HUD: public Object {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HUD_H */
