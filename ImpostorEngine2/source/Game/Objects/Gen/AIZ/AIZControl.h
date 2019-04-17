#ifndef AIZCONTROL_H
#define AIZCONTROL_H

class AIZControl;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZControl: public Object {
public:    
    
    int ActID;
    char ZoneLetters[128];
    bool LoadTileconfig;
    bool LoadStageconfig;
    bool LoadTiles;
    bool LoadAniTiles;
    int FireRiseValue;
    int FireRiseValue2;
    int Timerrrr;
    int TreeRevealRow;
    Layer* FireLayerBackup;
    int FireInd;
    ISprite* AIZShipTileSprite;
    ISprite* IntroSprite;
    ISprite* TileSpriteBackup;
    int CutsceneActTimer;
    Uint32 ShipTimer;
    int BombDelay;
    int BombIndex;
    
    void Create();
    void Update();
};

#endif /* AIZCONTROL_H */
