#ifndef AIZINTRO_H
#define AIZINTRO_H

class AIZIntro;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZIntro: public Object {
public:    
    
    ISprite* IntroSprite;
    ISprite* TileSpriteBackup;
    bool CutSceneKnux;
    bool OnBeach;
    bool SuperSonicMoving;
    int CutsceneRoutineNumber;
    int Cutscene_KnucklesBackForth;
    int Cutscene_SonicWaitTimer;
    int UpdateTimer;
    ISprite* IntroPlayersSprite;
    ISprite* IntroObjectsSprite;
    int InitialCamX;
    int InitialCamY;
    int TornadoX;
    int TornadoY;
    Object* Knux;
    int SonicFrame;
    int SonicFrameTimer;
    
    void Create();
    void Update();
    void SonicCutscene();
    void KnuxCutscene();
    void IntroFinish();
};

#endif /* AIZINTRO_H */
