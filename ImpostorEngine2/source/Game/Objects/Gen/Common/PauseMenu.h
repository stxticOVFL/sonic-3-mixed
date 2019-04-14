#ifndef PAUSEMENU_H
#define PAUSEMENU_H

class PauseMenu;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class PauseMenu: public Object {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* PAUSEMENU_H */
