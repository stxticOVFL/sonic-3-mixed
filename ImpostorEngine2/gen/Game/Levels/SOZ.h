#ifndef LEVEL_SOZ_H
#define LEVEL_SOZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_SOZ : public LevelScene {
public:
    Level_SOZ(IApp* app, IGraphics* g, int act);
    void RestartStage(bool doActTransition, bool drawBackground);
    void LoadZoneSpecificSprites();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_SOZ_H */
