#ifndef HOVERFAN_H
#define HOVERFAN_H

class HoverFan;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HoverFan: public Object {
public:    
    
    int BlowHeight;
    bool HaveBlock;
    int OutX;
    int Underwater;
    bool AlwaysOn;
    bool OnOff;
    bool NeedsActivation;
    bool On;
    bool PlayingSound;
    bool InUse;
    int Amount;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HOVERFAN_H */
