#ifndef LEVEL_TSZ_H
#define LEVEL_TSZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;
class Level_TSZ;

#include <Game/LevelScene.h>

class Level_TSZ : public LevelScene {
public:
    bool OnBeach = false;
    bool SuperSonicMoving = true;
    int  CutsceneRoutineNumber = 0x00;
    int  Cutscene_SonicWaitTimer = 0;
    int  Cutscene_KnucklesBackForth = 0;
    ISprite* TSZObjectsSprite = NULL;
    ISprite* TSZBossSprite = NULL;
    Level_TSZ* Act2Preload = NULL; //

    Level_TSZ(IApp* app, IGraphics* g, int ACT);
    void RestartStage(bool doActTransition, bool drawBackground);
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void LoadData();
    void Subupdate();
    void HandleCamera();
    void FinishResults();
    void GoToNextAct();
    void Cleanup();
};

#endif /* LEVEL_TSZ_H */
