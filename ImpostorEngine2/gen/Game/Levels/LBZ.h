#ifndef LEVEL_LBZ_H
#define LEVEL_LBZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;

#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    ISprite* LBZObjectsSprite = NULL;
    ISprite* WaterLine = NULL;

    Level_LBZ(IApp* app, IGraphics* g, int act);
    void Init();
    void RestartStage(bool doActTransition, bool drawBackground);
    void LoadData();
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void FinishResults();
    void GoToNextAct();
    void RenderAboveBackground();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_LBZ_H */
