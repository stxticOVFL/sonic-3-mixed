#ifndef BUBBLER_H
#define BUBBLER_H

class Bubbler;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Bubbler: public Object {
public:    
    
    bool UnkFlag;
    int UnkValue;
    int SubTimer;
    int BubblesToMake;
    
    void Create();
    void Update();
};

#endif /* BUBBLER_H */
