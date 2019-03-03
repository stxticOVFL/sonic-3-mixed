#ifndef BUBBLESBADNIK_H
#define BUBBLESBADNIK_H

class BubblesBadnik;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BubblesBadnik: public Enemy {
public:    
    
    int sinAngle;
    bool reversesin;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BUBBLESBADNIK_H */
