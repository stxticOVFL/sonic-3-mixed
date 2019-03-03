#ifndef TENSIONBRIDGECHILD_H
#define TENSIONBRIDGECHILD_H

class TensionBridgeChild;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TensionBridgeChild: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* TENSIONBRIDGECHILD_H */
