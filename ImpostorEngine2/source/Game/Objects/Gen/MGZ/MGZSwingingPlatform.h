#ifndef MGZSWINGINGPLATFORM_H
#define MGZSWINGINGPLATFORM_H

class MGZSwingingPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZSwingingPlatform: public Object {
public:    
    
    int LastX;
    int LastY;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MGZSWINGINGPLATFORM_H */
