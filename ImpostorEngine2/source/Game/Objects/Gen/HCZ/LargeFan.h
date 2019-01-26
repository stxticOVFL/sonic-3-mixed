#ifndef LARGEFAN_H
#define LARGEFAN_H

class LargeFan;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class LargeFan: public Object {
public:    
    
    int OutY;
    bool PlayingSound;
    
    void Create();
    void Update();
    int OnLeaveScreen();
    void Render(int CamX, int CamY);
};

#endif /* LARGEFAN_H */
