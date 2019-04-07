#ifndef LEVEL_AIZ_H
#define LEVEL_AIZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;
class Level_AIZ;

#include <Game/LevelScene.h>

class Level_AIZ : public LevelScene {
public:
    bool OnBeach = false;
    bool SuperSonicMoving = true;
    int  CutsceneRoutineNumber = 0x00;
    int  Cutscene_SonicWaitTimer = 0;
    int  Cutscene_KnucklesBackForth = 0;
    ISprite* AIZObjectsSprite = NULL;
    ISprite* AIZBossSprite = NULL;
    Level_AIZ* Act2Preload = NULL; //

    Level_AIZ(IApp* app, IGraphics* g, int ACT);
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

#endif /* LEVEL_AIZ_H */
