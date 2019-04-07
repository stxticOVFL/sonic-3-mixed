#ifndef LEVEL_BONUSSTAGE_H
#define LEVEL_BONUSSTAGE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Game/LevelScene.h>

class Level_BonusStage : public LevelScene {
public:
    Level_BonusStage(IApp* app, IGraphics* g, int act);
    void LoadZoneSpecificSprites();
    void Init();
    void RestartStage(bool doActTransition, bool drawBackground);
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
    void DoCustomFadeAction();
    void RenderEverything();
};

#endif /* LEVEL_BONUSSTAGE_H */
