#ifndef MONKEYDUDE_H
#define MONKEYDUDE_H

class MonkeyDude;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MonkeyDude: public Enemy {
public:    
    
    int Flip;
    int SubX;
    int frame_face;
    int frame_hand;
    int frame_arm;
    Object* Children;
    bool HasCoconut;
    
    CONSTRUCTER MonkeyDude();
    void Create();
    void Update();
    int OnLeaveScreen();
    int OnHit();
    void Render(int CamX, int CamY);
};

#endif /* MONKEYDUDE_H */
