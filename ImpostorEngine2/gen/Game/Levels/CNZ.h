#ifndef LEVEL_CNZ_H
#define LEVEL_CNZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;

#include <Game/LevelScene.h>

class Level_CNZ : public LevelScene {
public:
    ISprite* CNZObjectsSprite = NULL;

    Level_CNZ(IApp* app, IGraphics* g, int act);
    void RestartStage(bool doActTransition, bool drawBackground);
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void FinishResults();
    void GoToNextAct();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_CNZ_H */
