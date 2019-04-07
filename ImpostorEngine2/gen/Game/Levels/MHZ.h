#ifndef LEVEL_MHZ_H
#define LEVEL_MHZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_MHZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;

    Level_MHZ(IApp* app, IGraphics* g, int act);
    void LoadZoneSpecificSprites();
    void RestartStage(bool doActTransition, bool drawBackground);
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_MHZ_H */
