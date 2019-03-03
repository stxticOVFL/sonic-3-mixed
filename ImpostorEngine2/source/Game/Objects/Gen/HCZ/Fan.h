#ifndef FAN_H
#define FAN_H

class Fan;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Fan: public Object {
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
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FAN_H */
