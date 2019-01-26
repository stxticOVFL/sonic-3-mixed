#ifndef LEVEL_LBZ_H
#define LEVEL_LBZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

class ISprite;
class ISprite;

#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    ISprite* AIZ1Sprite = NULL;
    ISprite* AIZ2Sprite = NULL;

    Level_LBZ(IApp* app, IGraphics* g, int act);
    void RestartStage(bool doActTransition, bool drawBackground);
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_LBZ_H */