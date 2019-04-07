#ifndef LEVEL_DEZ_H
#define LEVEL_DEZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_DEZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;

    Level_DEZ(IApp* app, IGraphics* g, int act);
    void LoadZoneSpecificSprites();
    void RestartStage(bool doActTransition, bool drawBackground);
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_DEZ_H */
