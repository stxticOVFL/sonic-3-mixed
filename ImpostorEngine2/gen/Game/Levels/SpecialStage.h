#ifndef LEVEL_SPECIALSTAGE_H
#define LEVEL_SPECIALSTAGE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;

#include <Game/LevelScene.h>

class Level_SpecialStage : public LevelScene {
public:
    ISprite* Globe = NULL;
    ISprite* GlobeSpin = NULL;
    ISprite* Horizon = NULL;
    ISprite* Objects = NULL;
    ISprite* Players = NULL;
    uint8_t* Layout = NULL;
    uint8_t* LayoutCopy = NULL;

    Level_SpecialStage(IApp* app, IGraphics* g);
    void Init();
    void RestartStage(bool doActTransition, bool drawBackground);
    bool CheckSurround(int startX, int startY, int lastX, int lastY, int nX, int nY, int chkFor);
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
    int GetPushDownY(int ScreenY, int X);
    void RenderEverything();
};

#endif /* LEVEL_SPECIALSTAGE_H */
