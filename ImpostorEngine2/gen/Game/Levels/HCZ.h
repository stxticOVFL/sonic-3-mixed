#ifndef LEVEL_HCZ_H
#define LEVEL_HCZ_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;

#include <Game/LevelScene.h>

class Level_HCZ : public LevelScene {
public:
    ISprite* WaterLine = NULL;
    int WallX = 0x4000000;
    int WallY = 0x600;
    int WallMoving = false;
    int WallStopped = false; //

    Level_HCZ(IApp* app, IGraphics* g, int act);
    void Init();
    void RestartStage(bool doActTransition, bool drawBackground);
    void FinishResults();
    void GoToNextAct();
    void AssignSpriteMapIDs();
    void LoadZoneSpecificSprites();
    void Cleanup();
    void RenderAboveBackground();
    void RenderAboveForeground();
    void RenderEverything();
    bool CollisionAt(int probeX, int probeY, int* angle, int anglemode, IPlayer* player);
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
};

#endif /* LEVEL_HCZ_H */
