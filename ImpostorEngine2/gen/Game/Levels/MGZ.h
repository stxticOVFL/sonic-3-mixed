#ifndef LEVEL_MGZ_H
#define LEVEL_MGZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;

#include <Game/LevelScene.h>

class Level_MGZ : public LevelScene {
public:
    ISprite* MGZObjectsSprite = NULL;
    int32_t FloorY = 0; //

    Level_MGZ(IApp* app, IGraphics* g, int act);
    void Init();
    void RestartStage(bool doActTransition, bool drawBackground);
    void FinishResults();
    void GoToNextAct();
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void RenderAboveBackground();
    void RenderAboveForeground();
    void RenderEverything();
    void EarlyUpdate();
    void Subupdate();
    void Cleanup();
    void HandleCamera();
};

#endif /* LEVEL_MGZ_H */
