#ifndef HOLLOWTREE_H
#define HOLLOWTREE_H

class HollowTree;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HollowTree: public Object {
public:    
    
    int Status;
    int PlayerStorage[8];
    
    void Create();
    void Update();
    void CheckPlayer(int id);
    void AIZTree_FallOff(int id);
    void AIZTree_SetPlayerPos(int id);
};

#endif /* HOLLOWTREE_H */
