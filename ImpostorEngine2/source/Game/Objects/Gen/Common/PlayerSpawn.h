#ifndef PLAYERSPAWN_H
#define PLAYERSPAWN_H

class PlayerSpawn;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class PlayerSpawn: public Object {
public:    
    
    IPlayer* Player;
    IPlayer* Players[7];
    
    void Create();
};

#endif /* PLAYERSPAWN_H */
