#ifndef FLOATINGPLATFORM_H
#define FLOATINGPLATFORM_H

class FloatingPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class FloatingPlatform: public Object {
public:    
    
    int LastX;
    int LastY;
    int YS;
    int Vertical;
    int RisingType;
    int Rising;
    int Moving;
    int SizeIndex;
    int MoveType;
    int BackupX;
    int Amplitude;
    Object* Outliner;
    
    CONSTRUCTER FloatingPlatform();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FLOATINGPLATFORM_H */
