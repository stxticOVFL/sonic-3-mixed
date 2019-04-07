#ifndef LEVEL_ICZ_H
#define LEVEL_ICZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;

#include <Game/LevelScene.h>

class Level_ICZ : public LevelScene {
public:
    ISprite* ICZObjectsSprite = NULL;

    Level_ICZ(IApp* app, IGraphics* g, int act);
    void RestartStage(bool doActTransition, bool drawBackground);
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void FinishResults();
    void GoToNextAct();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_ICZ_H */
