#ifndef LEVEL_LRZ_H
#define LEVEL_LRZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_LRZ : public LevelScene {
public:
    Level_LRZ(IApp* app, IGraphics* g, int act);
    void RestartStage(bool doActTransition, bool drawBackground);
    void LoadZoneSpecificSprites();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_LRZ_H */
