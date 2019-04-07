#ifndef LEVEL_FBZ_H
#define LEVEL_FBZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_FBZ : public LevelScene {
public:
    Level_FBZ(IApp* app, IGraphics* g, int act);
    void RestartStage(bool doActTransition, bool drawBackground);
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_FBZ_H */
