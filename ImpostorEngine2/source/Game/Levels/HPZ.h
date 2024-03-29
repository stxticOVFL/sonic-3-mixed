#ifndef LEVEL_HPZ_H
#define LEVEL_HPZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_HPZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;

    Level_HPZ(IApp* app, IGraphics* g, int act);
    void LoadZoneSpecificSprites();
    void Init();
    void RestartStage(bool doActTransition, bool drawBackground);
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_HPZ_H */
