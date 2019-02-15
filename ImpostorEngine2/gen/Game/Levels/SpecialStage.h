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
    Uint8* LayoutAt(int ox, int oy);
    Uint8* LayoutBackupAt(int ox, int oy);
    Uint8* LayoutExtraAt(int ox, int oy);
    bool   HasAllNonBlueNeighbors(int ox, int oy);
    bool SphereCheckDirection(int ox, int oy, int dir);
    bool SphereCheckUp(int ox, int oy);
    bool SphereCheckDown(int ox, int oy);
    bool SphereCheckLeft(int ox, int oy);
    bool SphereCheckRight(int ox, int oy);
    int SomethingUsefulMaybe(int ox, int oy);
    bool CheckSurround();
    void EarlyUpdate();
    void Subupdate();
    void HandleCamera();
    void RenderEverything();
};

#endif /* LEVEL_SPECIALSTAGE_H */
